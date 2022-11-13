#include <malloc.h>
#include "parser.h"

#define MAX_SPACES 2
#define MAX_MATCHES 5
#define MAX_PLAYERS 16

struct Game{
    struct Match *matches;
};

struct Match{
    int number;
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
    words = malloc(sizeof(char*)* (9 + (MAX_SPACES*2)));
    for(int index=0;index< 9 + (MAX_SPACES*2); index++)
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
        for(counter = 1;counter<= 9 + (MAX_SPACES*2); counter++)
            words[counter] = strtok(NULL, " ");

        //proccessLine turns an array of strings(words) into information
        if(words[strlen( words) - 1] != NULL)
            proccessLine(words, &game);
    }


}
/* This block turns an array of words into score based on victims and kills
 * This score is then sent into generateInfo() which stores that information
 */
void proccessLine(char** words, struct Game *game) {
    char time[5];
    char timeAux[5];
    char *victim = malloc(sizeof(char)*60);
    char *killer = malloc(sizeof(char)*60);
    char *causeOfDeath = malloc(sizeof(char)* 40);
    int counter;

    //looping around words[] to find the killer
    for(counter = 0; strcmp(words[counter], "killed") != 0; counter++ ){
        if (words[counter] == NULL || words[counter - 1] == NULL) continue;
        if (strcmp(words[counter], "Kill:") == 0) {
            counter += 4 ;
            strcpy(killer,words[counter]);
            continue;
        }
        strcat(killer," ");
        strcat(killer,words[counter]);
    }

    //Looping around words[] to find the victim
    for(counter = 0; strcmp(words[counter], "by") != 0; counter++ ){
        if (words[counter] == NULL || words[counter - 1] == NULL) continue;
        if (strcmp(words[counter], "killed") == 0) {
            counter += 1;
            strcpy(victim,words[counter]);
            continue;
        }
        strcat(victim," ");
        strcat(victim,words[counter]);

    }
    //Finding cause of death by adding 1 to the counter since the victim loop stops at "by"
    causeOfDeath = words[counter+1];

    //Removing \r at the end of causeOfDeath
    int len= strlen(causeOfDeath);
    causeOfDeath[len-1] = 0;

    //printf("%s matou %s com %s no jogo %d \n", killer, victim, causeOfDeath, game.match);
    printf("%s matou %s com %s\n", killer, victim, causeOfDeath);
    //Generate Info
}