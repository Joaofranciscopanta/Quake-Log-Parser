#include <malloc.h>
#include "parser.h"

#define MAX_SPACES 3

void parse(){
    FILE *logs = fopen("processedlog.txt","r");
    char logLine[500];
    char **words;
    int counter;

    if(logs == nullptr){
        exit(2001);
    }

    //Game is the main data structure for this parser, encapsulates an array of matches and a match counter
    Game game = *new Game();
    Match auxMatch = *new Match();

    //Allocating an array of strings
    words =(char**) malloc(sizeof(char*)* (9 + (MAX_SPACES*2)));
    for(int index=0;index< 9 + (MAX_SPACES*2); index++)
        words[index]=(char*) malloc(sizeof(char)*600);

    //Transforming the logLine string into array of strings(words)
    while(!feof(logs)){
        fgets(logLine, sizeof(logLine), logs);
        counter = 0;

        //Separate logLine string into word substrings
        words[0] = strtok(logLine," ");
        for(counter = 1;counter<= 9 + (MAX_SPACES*2); counter++) {
            words[counter] = strtok(nullptr, " ");
        }

        //processLine turns an array of strings(words) into information
        if(words[strlen((const char *) words) - 1] != nullptr) {
            processLine(words, &game, &auxMatch);
        }
    }
    fclose(logs);
}

/* This block turns an array of words into score based on victims and kills
 * This score is then sent into generateInfo() which stores that information
 */
void processLine(char **words, Game *game, Match *auxMatch) {
    char *victim =(char*) malloc(sizeof(char)*40);
    char *killer =(char*) malloc(sizeof(char)*40);
    char *causeOfDeath;
    int counter;

    //Increments match counter and stores a match on Game's matches vector
    if(strcmp(words[1],"InitGame:") == 0) {

        //Printing a report
        cout << "End of match number " << game->ongoingMatch << " \n";
        cout << "Total kills: " << auxMatch->totalKills << "\n";
        cout << "Players on this match: \n";
        for(Player p: auxMatch->players ) cout << p.name << " with " << p.kills <<" kills\n";
        cout <<"\n\n\n";

        //Create definiteMatch to store in Game's matches vector
        Match definiteMatch = *new Match();
        definiteMatch.players = auxMatch->players;
        definiteMatch.totalKills = auxMatch->totalKills;
        game->matches.insert(game->matches.end(),definiteMatch);
        //Incrementing the matchcounter
        game->incrementOngoingMatch();

        //Resetting auxMatch
        auxMatch->players.clear();
        auxMatch->totalKills = 0;
        return;
    }
    auxMatch->totalKills++;
    //looping around words[] to find the killer
    for(counter = 0; strcmp(words[counter], "killed") != 0; counter++ ){
        if (words[counter] == nullptr || words[counter - 1] == nullptr) continue;
        if (strcmp(words[counter], "Kill:") == 0) {
            counter += 4 ;
            strcpy(killer,words[counter]);
            continue;
        }
        strcat(killer," ");
        strcat(killer,words[counter]);
    }
    if(!auxMatch->isPlayerAdded(killer))
        auxMatch->addPlayer(killer);

    //Looping around words[] to find the victim
    for(counter = 0; strcmp(words[counter], "by") != 0; counter++ ){
        if (words[counter] == nullptr || words[counter - 1] == nullptr) continue;
        if (strcmp(words[counter], "killed") == 0) {
            counter += 1;
            strcpy(victim,words[counter]);
            continue;
        }
        strcat(victim," ");
        strcat(victim,words[counter]);
    }
    if(!auxMatch->isPlayerAdded(victim) && victim != killer) {
        auxMatch->addPlayer(victim);
    }

    //Finding cause of death by adding 1 to the counter since the victim loop above stops at "by"
    causeOfDeath = words[counter+1];
    //cout << killer <<  " killed " << victim << " on game " << game->ongoingMatch << "\n";

    //Removing \r at the end of causeOfDeath
    int len=(int) strlen(causeOfDeath);
    causeOfDeath[len-1] = 0;

    //Removing suicides by splash damage
    if(strcmp(killer,victim)==0) return;

    for(counter = 0; counter< auxMatch->players.size(); counter++){
        if(auxMatch->players.at(counter).name == killer){
            auxMatch->players.at(counter).kills++;
        }
    }

}
