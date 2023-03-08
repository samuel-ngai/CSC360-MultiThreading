#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <limits.h>


void process_file(char** arg) {
    //FILE* file = fopen(arg[1],"r");

    char const* const fileName = arg[1];
    FILE *file = fopen(fileName, "r");

    if(file == NULL) {
        printf("Error\n");
        exit(0);
    }

    printf("%s\n", arg[1]);

    fseek(file, 0, SEEK_END);
    int size  = ftell(file);
    fseek(file, 0, SEEK_SET);


    // int lines  = 0;
    // while(!feof(file)) {
    //     char ch = fgetc(file);
    //     if(ch == '\n'){
    //         lines++;
    //     }
    // }

    size = size * sizeof(char);
    unsigned char buf[size];
    // printf("size  is %d\n", size);
    // printf("buff size is %d\n", sizeof(buf));

    // int data[size];

    // int i =  0;
    // printf("here\n");
    // if(buf){
    //     fread(buf, sizeof(buf), 1, file);
    //     //printf("%s\n", buf);
    //     printf("size of buf is %d\n", sizeof(buf));
    // }
    // char* str = strtok(buf, "\n");
    // char* copyStr = str;
    // printf("%s\n", copyStr);
    // char* bingStr = strtok(copyStr, " ");
    // printf("bingStr is %s\n", bingStr);
    // printf("here\n");
    // double minTemp = 1000000;
    // double maxTemp = -1000000;
    // char subStr[5];
    // while(str != NULL) {
    //     //printf("token is %s\n", str);
    //     //printf("str length is %d\n", sizeof(str));
    //     memcpy(subStr, str, 4);
    //     subStr[4]  = '\0';
    //     //printf("substr is %s\n", subStr);

    //     if((double)(*subStr) > maxTemp) {
    //         printf("substr in double is %d\n", (double)(*subStr));
    //         maxTemp  = (double)(*subStr);
    //     }

    //     // char* copyStr = str;
    //     // char* subStr = strtok(copyStr, "\n");
    //     //printf("substr is %s\n", subStr);
    //     //subStr = strtok(NULL, "\n");
    //     str = strtok(NULL, "\n");   //should go line  by line
    // }

    char line[500];
    float data[2];

    float maxTemp = -10000000;
    float minTemp = 10000000;
    int entryCount = 0;
    float averageTemp = 0;
    printf("Size is %d\n", size);
    if(file == NULL) {
        return;
    }
    while(fgets(line, sizeof(line), file)) {
        sscanf(line, "%f %f", &data[0], &data[1]);
        if(data[0] > maxTemp) {
            maxTemp  = data[0];
        }
        if(data[1] < minTemp) {
            minTemp = data[1];
        }
        averageTemp += data[0] + data[1];
        entryCount++;
        //printf("%s", line);
    }

    printf("\n");
    printf("max temp is %f\n", maxTemp);
    printf("min temp is %f\n", minTemp);
    printf("average is %f\n", averageTemp/entryCount);
    printf("entry  count is %d\n", entryCount);
    //printf("lines is %d\n", lines);
    fclose(file);
}


int
main(int argc, char* argv[])
{
    
    process_file(argv);
	return 0;
}
