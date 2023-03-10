#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>

float maxTemp;
float minTemp;
int entryCount;
float averageTemp;

char line[500];
float data[2];
// float maxTemp = -1000;
// float minTemp = 1000;
// int entryCount = 0;
// float averageTemp = 0;

pthread_mutex_t mutex;

/**
 * 
 */
void printData(char* fileName, float maximumTemp,  float minimumTemp, int entries, float averageTemp) {
    printf("===file is %s===\n", fileName);
    printf("max temp is %0.1f\n", maximumTemp);
    printf("min temp is %0.1f\n", minimumTemp);
    printf("average is %0.1f\n", averageTemp/entries);
    printf("entry  count is %d\n", entries);
}

/**
 * 
 */ 
void* process_file(char* fileName) {
    FILE* file = fopen(fileName, "r");
    if(file == NULL) {
        printf("Error\n");
        exit(0);
    }

    // char line[500];
    // float data[2];
    pthread_mutex_lock(&mutex);
    maxTemp = -1000;
    minTemp = 1000;
    entryCount = 0;
    averageTemp = 0;

    if(file == NULL) {
        return 0;
    }
    //pthread_mutex_lock(&mutex);
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
    printf("\n");
    printData(fileName,maxTemp,minTemp,entryCount,averageTemp);
    fclose(file);
    pthread_mutex_unlock(&mutex);
}

/**
 * 
 */ 
int
main(int argc, char* argv[])
{
    clock_t start_t;
    clock_t end_t;
    double total_t;
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
    if(argc == 2) {
        pthread_t tid[10];
        char* isMultiThreading = "";
        isMultiThreading = argv[1];
        if(strcmp(isMultiThreading, "-m") == 0) {
            for(int i = 0; i<10; i++) {
                int result = pthread_create(&tid[i], NULL, process_file, filePath[i]);
                if(result != 0) {
                    printf("sucks to be you\n");
                    return 1;
                }
            }
            for(int i = 0; i<10; i++) {
                int result  = pthread_join(tid[i], NULL);
                if(result) {
                    printf("sucks to be you joining threads\n");
                    return 1;
                }
            }
            end_t = clock();
            printf("multithread start_t is %ld\n", start_t);
            printf("multithread end_t is %ld\n", end_t);
            total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC;
            printf("total Multithreading time is %f\n", total_t);
            return 0;
        }
    }
    pthread_t tid;
    int choices[10] = {0,1,2,3,4,5,6,7,8,9};
    int result;
    for(int i = 0; i<10; i++) {
        result = pthread_create(&tid, NULL, process_file, filePath[choices[i]]);
        if(result != 0) {
            printf("single threading failed\n");
            return 1;
        }
        wait(1);
    }
    result = pthread_join(tid, NULL);
    if(result != 0) {
        printf("error in joining\n");
        return 1;
    }
    end_t = clock();
    printf("singlethread start_t is %ld\n", start_t);
    printf("singlethread end_t is %ld\n", end_t);
    total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC;
    printf("total singlethreading time is %f\n", total_t);
	return 0;
}
