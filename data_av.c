#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <limits.h>


void process_file(char** arg) {
    FILE *file = fopen(arg[1],"r");

    if(file == NULL) {
        printf("Error\n");
        exit(0);
    }

    printf("%s\n", arg[1]);
    //printf("%s", *file);
    // ssize_t read;
    // char* data = NULL;
    // char* line = NULL;
    // printf("here\n");
    // while((read = getline(&line, 0, file)) != EOF) {
    //     printf("%s\n", line);
    //     data = strtok(line, " ");
    //     break;
    // }
    // while(data != NULL) {
    //     printf("%s\n", data);
    //     data = strtok(NULL, " ");
    // }

    fseek(file, 0, SEEK_END);
    int size  = ftell(file);
    fseek(file, 0, SEEK_SET);


    int lines  = 0;
    while(!feof(file)) {
        char ch = fgetc(file);
        if(ch == '\n'){
            lines++;
        }
    }
    file = fopen(arg[1], "r");
    //unsigned char buf[sizeof(char)*lines+lines];
    
    size = size * sizeof(char);
    unsigned char buf[size];
    printf("size  is %d\n", size);
    printf("buff size is %d\n", sizeof(buf));

    int data[size];

    int i =  0;
    printf("here\n");
    if(buf){
        fread(buf, sizeof(buf), 1, file);
        //printf("%s\n", buf);
        printf("size of buf is %d\n", sizeof(buf));
    }
    char* str = strtok(buf, "\n");
    char* copyStr = str;
    printf("%s\n", copyStr);
    char* bingStr = strtok(copyStr, " ");
    printf("bingStr is %s\n", bingStr);
    printf("here\n");
    double minTemp = 1000000;
    double maxTemp = -1000000;
    char subStr[5];
    while(str != NULL) {
        //printf("token is %s\n", str);
        //printf("str length is %d\n", sizeof(str));
        memcpy(subStr, str, 4);
        subStr[4]  = '\0';
        //printf("substr is %s\n", subStr);

        if((double)(*subStr) > maxTemp) {
            printf("substr in double is %d\n", (double)(*subStr));
            maxTemp  = (double)(*subStr);
        }

        // char* copyStr = str;
        // char* subStr = strtok(copyStr, "\n");
        //printf("substr is %s\n", subStr);
        //subStr = strtok(NULL, "\n");
        str = strtok(NULL, "\n");   //should go line  by line
    }

    printf("\n");
    printf("max temp is %f\n", maxTemp);
    printf("min temp is %f\n", minTemp);
    printf("lines is %d\n", lines);
    fclose(file);
}


int
main(int argc, char* argv[])
{
    
    process_file(argv);
	return 0;
}
