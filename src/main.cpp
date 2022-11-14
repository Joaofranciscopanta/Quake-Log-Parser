#include <parser.h>

int main(int argc, char *argv[]){

    #ifdef _WIN32
    char processRawLog[300] = "findstr \"killed InitGame:\" ";
    #elif
    char processRawLog[300] = "grep killed ";
    #endif

    //Verifies whether it is a different log or a default one
    if(argc >= 2) {
        printf("Parsing %s file\n", argv[1]);
        strcat(processRawLog, argv[1]);
        strcat(processRawLog, " > processedlog.txt");
    }
    else {
        printf("Parsing default log on quakelog.txt\n");
        strcat(processRawLog, "quakelog.txt > processedlog.txt");
    }
    #ifdef _WIN32
        popen(processRawLog, "w");
    #elif __linux__
        popen(processRawLog, "w");
    #endif

    printf("Processed log generated, parsing...\n");
    //A "Press enter to continue" cin use
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    parse();
    return 0;
}