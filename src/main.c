#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

    #ifdef _WIN32
    char command[300] = "findstr killed ";
    #elif
    char command[300] = "grep killed ";
    #endif
    //Verifies whether it is a different log or a default one
    if(argc >= 2) {
        printf("Parsing %s file\n", argv[1]);
        strcat(command, argv[1]);
        strcat(command, " > processedlog.txt");
    }
    else {
        printf("Parsing default log on quakelog.txt\n");
        strcat(command, "quakelog.txt > processedlog.txt");
    }
    printf("%s\n", command);

    #ifdef _WIN32
        popen(command, "w");
    #elif __linux__
        popen(command, "w");
    #endif
    scanf(" ");
    printf("Processed log generated, press Enter...\n");
    return 0;
}