#include <stdio.h>
#include <stdlib.h>
#include <parser.h>
#include <string.h>

int main(int argc, char *argv[]){

    int errnum;
    FILE *rawLog = NULL;

    //Verifies whether it is a different log or the default one
    if(argc > 1) {
        printf("Parsing %s file\n", argv[1]);
        rawLog = fopen(argv[1], "r");
    }
    else {
        printf("Parsing default log on logs/quakelog.txt\n");
        rawLog = fopen("../logs/quakelog.txt", "r");
    }

    //Verifies it the file was opened and if it is really a quake3 log (has at least 1 death)
    if(rawLog == NULL){
        errnum = errno;
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
        return 2;
    }


    /* TODO
    if(1){
        FILE *cmd = popen("grep InitGame qgames.txt", "r");
        if (cmd != NULL) {
            errnum = errno;
            printf("File is not an Quake3 log.\n");
            exit(3);
        }
        pclose(cmd);
    }
    */

    scanf(" ");
    return 2;
}