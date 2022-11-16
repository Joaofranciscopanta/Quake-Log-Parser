#include <parser.h>
#include <ctime>
#include <limits>

int main(int argc, char *argv[]){

    clock_t start, end;
    clock_t startWait, endWait;
    start = clock();

    //Native call to filter lines
    #ifdef _WIN32
    char processRawLog[300] = "findstr \"killed InitGame:\" ";
    #elif
    char processRawLog[300] = "grep \"killed InitGame:\" ";
    #endif

    //Verifies whether it is a different log or a default one
    if(argc >= 2) {
        printf("Parsing %s file\n", argv[1]);
        strcat(processRawLog, argv[1]);
        strcat(processRawLog, " > processedlog.txt");
    }
    else {
        printf("Parsing default log this folder\n");
        strcat(processRawLog, "quakelog.txt > processedlog.txt");
    }

    #ifdef _WIN32
        popen(processRawLog, "w");
    #elif __linux__
        popen(processRawLog, "w");
    #endif

    //A "Press enter to continue" cin use
    printf("Processed log generated, press ENTER to start parsing...\n");
    startWait=clock();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    endWait=clock();

    parse();

    #ifdef _WIN32
        popen("del processedlog.txt", "w");
    #elif __linux__
        open("rm processedlog.txt", "w");
    #endif

    //Measuring time
    end = clock();
    double totalTime = double(end - start) / double (CLOCKS_PER_SEC);
    double waitTime = double(endWait - startWait) / double (CLOCKS_PER_SEC);
    cout << "Time taken to parse is : " << fixed
         << totalTime-waitTime << setprecision(5);
    cout << " seconds. " << endl;

    return 0;
}