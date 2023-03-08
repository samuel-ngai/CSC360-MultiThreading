#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <limits.h>



void process_file(char* arg) {
    //FILE* file = fopen(arg[1],"r");
    //char const* const fileName = arg[1];
    char  const* const fileName = arg;
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        printf("Error\n");
        exit(0);
    }

    char line[500];
    float data[2];
    // data[0] = 0;
    // data[1] = 0;
    float maxTemp = -1000;
    float minTemp = 1000;
    int entryCount = 0;
    float averageTemp = 0;

    if(file == NULL) {
        return;
    }
    while(fgets(line, sizeof(line), file)) {
        sscanf(line, "%f %f", &data[0], &data[1]);
        // printf("data[0] is %f\n", data[0]);
        // printf("maxTemp is %f\n", maxTemp);
        // printf("data[1] is %f\n", data[1]);
        // printf("minTemp is %f\n", minTemp);
        if(data[0] > maxTemp) {
            //printf("new max fround: %f\n", data[0]);
            //printf("%f is greater than %f\n", data[0], maxTemp);            
            maxTemp = data[0];
        }
        if(data[1] < minTemp) {
            //printf("new min fround: %f\n", data[1]);
            minTemp = data[1];
        }
        averageTemp += data[0] + data[1];
        entryCount++;
    }
    entryCount -= 1; //offset because of the first starting label
    printf("\n");
    printf("===file is %s===\n", fileName);
    printf("max temp is %f\n", maxTemp);
    printf("min temp is %f\n", minTemp);
    printf("average is %f\n", averageTemp/entryCount);
    printf("entry  count is %d\n", entryCount);
    fclose(file);
}


int
main(int argc, char* argv[])
{

    char* filePath[10];
    filePath[0] = "data_files/Charlottetown.dat";
    filePath[1] = "data_files/Edmonton.dat";
    filePath[2] = "data_files/Halifax.dat";
    filePath[3] = "data_files/Montreal.dat";
    filePath[4] = "data_files/Ottawa.dat";
    filePath[5] = "data_files/Quebec.dat";
    filePath[6] = "data_files/Toronto.dat";
    filePath[7] = "data_files/Vancouver.dat";
    filePath[8] = "data_files/Victoria.dat";
    filePath[9] = "data_files/Winnipeg.dat";
    

    if(argc == 2) {
        char* isMultiThreading = "";
        isMultiThreading = argv[1];
        if(strcmp(isMultiThreading, "-m")== 0) {
            //do multithreding
            printf("chose multithreading\n");
            printf("jokes multithreading doesn't do anything\n");
            return 0;
        }
    }
    //printf("filechoice is %d\n", fileChoice);
    printf("chose: %s\n", filePath[0]);
    process_file(filePath[0]);
    process_file(filePath[1]);
    process_file(filePath[2]);
    process_file(filePath[3]);
    process_file(filePath[4]);
    process_file(filePath[5]);

    printf("here\n");
    //process_file(argv);

	return 0;
}
