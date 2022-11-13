#include <parser.h>

int main(int argc, char *argv[]){

    #ifdef _WIN32
    char killlogCommand[300] = "findstr killed ";
    #elif
    char killlogCommand[300] = "grep killed ";
    #endif


    //Verifies whether it is a different log or a default one
    if(argc >= 2) {
        printf("Parsing %s file\n", argv[1]);
        strcat(killlogCommand, argv[1]);
        strcat(killlogCommand, " > killslog.txt");
    }
    else {
        printf("Parsing default log on quakelog.txt\n");
        strcat(killlogCommand, "quakelog.txt > killslog.txt");
    }

    #ifdef _WIN32
        popen(killlogCommand, "w");
    #elif __linux__
        popen(killlogCommand, "w");
    #endif

    printf("Processed log generated, press enter to parse!\n");
    parse();
    return 0;
}