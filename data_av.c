#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>

struct totalMax {
    char* fileName;
    float temp;
};
struct totalMin {
    char* fileName;
    float temp;
};
struct totalMax tMax;
struct totalMin tMin;
char line[500];
float data[2];
float maxTemp;
float minTemp;
int totalEntries;
int entryCount;
float averageTemp;
pthread_mutex_t mutex;

/**
 * Function to print out errors when the user submits an unprogrammed input when executing ./data_av
 */ 
void inputError() {
    printf("\n");
    printf("Improper command. Please only input the following commands:\n");
    printf("    ./data_av       -> Regular mode\n");
    printf("    ./data_av -m    -> Multi-threaded mode\n");
    printf("\n");
}

/**
 * Function that prints out our file name, temperature variables, and number of entries.
 */
void printData(char* fileName, float maximumTemp,  float minimumTemp, int entries, float averageTemp) {
    printf("===================================================\n");
    printf("Data for: %s\n", fileName);
    printf("Maximum temperature: %0.1f degrees Celsius\n", maximumTemp);
    printf("Minimum temperature: %0.1f degrees Celsius\n", minimumTemp);
    printf("Average temperature: %0.2f degrees Celsius\n", averageTemp/entries);
    printf("Total values processed (Max & Min): %d\n", entries);
    printf("\n");
}

/**
 * Given a fileName, we open and parse the file, calculating the maximum, minimum, 
 * and average temperatures along with number of entries.
 * This function is our 'critical section'.
 */ 
void process_file(char* fileName) {
    FILE* file = fopen(fileName, "r");
    if(file == NULL) {
        printf("Error\n");
        exit(0);
    }
    maxTemp = -1000;
    minTemp = 1000;
    entryCount = 0;
    averageTemp = 0;
    if(file == NULL) {
        return;
    }
    while(fgets(line, sizeof(line), file)) {
        sscanf(line, "%f %f", &data[0], &data[1]);

        if(data[0] > maxTemp) {
            maxTemp = data[0];
        }
        if(data[1] < minTemp) {
            minTemp = data[1];
        }
        averageTemp += data[0] + data[1];
        entryCount++;
    }
    entryCount -= 1;
    entryCount *= 2;
    totalEntries += entryCount;
    if(maxTemp > tMax.temp) {
        tMax.temp = maxTemp;
        tMax.fileName = fileName;
    }
    if(minTemp < tMin.temp) {
        tMin.temp = minTemp;
        tMin.fileName = fileName;
    }
    printData(fileName,maxTemp,minTemp,entryCount,averageTemp);
    fclose(file);
}

/**
 * A buffer function for threading, utilizing mutexes to create a critical
 * section so that no two threads can be parsing, editing, and printing our 
 * global variables at the same time.
 */
void* threadBuffer(void* arg) {
    pthread_mutex_lock(&mutex);
    process_file((char*) arg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

/**
 * Main function
 * Checks for user imput for multithreaded  mode, "-m".
 * Creates threads for single and multithreaded purposes, which call our process_file 
 * function and passing an appropriate filepath as parameter input.
 * Also calculates and prints out our total elapsed time.
 */ 
int
main(int argc, char* argv[])
{
    clock_t start_t;
    clock_t end_t;
    double total_t;
    clock_t elapsed_t;
    char* filePath[10] = {
        "data_files/Charlottetown.dat",
        "data_files/Edmonton.dat",
        "data_files/Halifax.dat",
        "data_files/Montreal.dat",
        "data_files/Ottawa.dat",
        "data_files/Quebec.dat",
        "data_files/Toronto.dat",
        "data_files/Vancouver.dat",
        "data_files/Victoria.dat",
        "data_files/Winnipeg.dat"
    };
    pthread_mutex_init(&mutex,NULL);
    start_t = clock();
    if(argc > 2)  {
        inputError();
        return 1;
    }
    //Multithreading mode
    if(argc == 2) {
        pthread_t tid[10];
        char* isMultiThreading = argv[1];
        if(strcmp(isMultiThreading, "-m") == 0) {
            for(int i = 0; i<10; i++) {
                int createThread = pthread_create(&tid[i], NULL, threadBuffer, filePath[i]);
                if(createThread) {
                    printf("Error in creating threads.\n");
                    return 1;
                }
            }
            for(int i = 0; i<10; i++) {
                int joinThread = pthread_join(tid[i], NULL);
                if(joinThread) {
                    printf("Error in joining multiple threads.\n");
                    return 1;
                }
            }
            end_t = clock();
            total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC;
            elapsed_t = end_t-start_t;

            printf("Total values processed of all files: %d\n", totalEntries);
            printf("Lowest overall temperature: %0.1f degrees Celsius, reported in %s\n", tMin.temp, tMin.fileName);
            printf("Highest overall temperature: %0.1f degrees Celsius, reported in %s\n",  tMax.temp, tMax.fileName);
            printf("Elapsed time: %ld clocks\n", elapsed_t);
            printf("Total Multithreading time is %0.3f\n", total_t);
            printf("\n");
            return 0;
        } else {
            inputError();
            return 1;
        }
    }
    //Regular mode
    for(int i = 0; i<10; i++) {
        process_file(filePath[i]);
        usleep((useconds_t)0.0001);
    }
    end_t = clock();
    total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC;
    elapsed_t = end_t-start_t;
   
    printf("Total values processed of all files: %d\n", totalEntries);
    printf("Lowest overall temperature: %0.1f degrees Celsius, reported in %s\n", tMin.temp, tMin.fileName);
    printf("Highest overall temperature: %0.1f degrees Celsius, reported in %s\n",  tMax.temp, tMax.fileName);
    printf("Elapsed time: %ld clocks\n", elapsed_t);
    printf("Total time is %0.3f\n", total_t);
    printf("\n");
	return 0;
}
