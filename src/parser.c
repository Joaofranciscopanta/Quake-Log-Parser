#include <malloc.h>
#include "parser.h"
#define MAX_SPACES 2
#define MAX_MATCHES 5
#define MAX_PLAYERS 16
struct Game{
    struct Match *matches;
};

struct Match{
    struct Player *players;
    int minutes;
    int totalkills;
};

struct Player{
    char name[40];
    int kills;
    int deaths;
};

void parse(){
    FILE *logs = fopen("processedlog.txt","r+");
    char logLine[80];
    char **words;
    int counter;
    //Allocating an array of strings
    words = malloc(sizeof(char*)* (8 + (MAX_SPACES*2)));
    for(int index=0;index< 8 + (MAX_SPACES*2); index++)
        words[index]=malloc(sizeof(char)*60);

    //Game represents an array of matches.
    struct Game game;
    //Dynamically allocates an array of 10 matches.
    game.matches = malloc(sizeof(struct Match)*MAX_MATCHES);
    //Dynamically allocates memory for the maximum player capacity;
    game.matches->players = malloc(sizeof (struct Player)*MAX_PLAYERS);

    //Transforming the logLine string into array of strings(words)
    while(!feof(logs)){
        fgets(logLine, sizeof(logLine), logs);
        counter = 0;

        words[0] = strtok(logLine," ");
        for(counter = 1;counter<= 8 + (MAX_SPACES*2); counter++)
            words[counter] = strtok(NULL, " ");

        //proccessLine turns an array of strings(words) into information
        if(words[strlen((const char *) words) - 1] != NULL)
            proccessLine(words, &game);
    }


}
/* This block turns an array of words into score based on victims and kills
 * This score is then sent into processkills() which stores that information
 */
void proccessLine(char** words, struct Game *game) {
    char time[5];
    char timeAux[5];
    char *victim = malloc(sizeof(char)*40);
    char *killer = malloc(sizeof(char)*40);
    char *causeOfDeath = malloc(sizeof(char)* 40);



    for(int newPointer = 0; strcmp(words[newPointer], "killed") != 0; newPointer++ ){
        if (words[newPointer] == NULL || words[newPointer - 1] == NULL) continue;
        if (strcmp(words[newPointer], "Kill:") == 0) {
            newPointer += 4 ;
            strcpy(killer,words[newPointer]);
            continue;
        }
        strcat(killer," ");
        strcat(killer,words[newPointer]);
    }

    for(int newPointer = 0; strcmp(words[newPointer], "by") != 0; newPointer++ ){
        if (words[newPointer] == NULL || words[newPointer - 1] == NULL) continue;
        if (strcmp(words[newPointer], "killed") == 0) {
            newPointer += 1;
            strcpy(victim,words[newPointer]);
            continue;
        }
        strcat(victim," ");
        strcat(victim,words[newPointer]);
    }
    printf("%s matou %s \n", killer, victim);
}