#include "include/report.h"
#define MATCHESVECTOR game->matches[matchCounter]
#define RANKEDPLAYERS game->matches[matchCounter].rankPlayers()

void printReport(Game * game){
    ofstream output;
    output.open("../output/matchresults.json");
    for(int matchCounter = 0; matchCounter <= game->ongoingMatch; matchCounter++){
        output <<"\"game_"  << matchCounter << "\": {\n";
        output << "\"total_kills\":" << MATCHESVECTOR.totalKills << ",\n";
        output << "\"players\": [";
        for(int playerCounter = 0; playerCounter < MATCHESVECTOR.players.size(); playerCounter++){
            if(MATCHESVECTOR.players[playerCounter].name == "<world>") continue;
            output << "\"" << MATCHESVECTOR.players[playerCounter].name << "\"";
            if(playerCounter != MATCHESVECTOR.players.size()-1) output << ", ";
        }
        output << "],\n";
        output << "\"kills\": {\n";
        for(int playerCounter = 0; playerCounter < MATCHESVECTOR.players.size(); playerCounter++){
            if(RANKEDPLAYERS[playerCounter].name == "<world>") continue;
            output << "  \"" << RANKEDPLAYERS[playerCounter].name << "\": " << RANKEDPLAYERS[playerCounter].kills <<",\n";
        }
        output << "  }\n" << "}\n\n" ;
    }
}
void printCausesOfDeath(Game * game){
    ofstream output;
    output.open("../output/causesofdeath.json");
    for(int matchCounter = 0; matchCounter <= game->ongoingMatch; matchCounter++){
        output <<"\"game_"  << matchCounter << "\": {\n";
        output << "  \"kills_by_means\": {\n";
        for(int causesCounter = 0; causesCounter < MATCHESVECTOR.causes.size(); causesCounter++){
            if(MATCHESVECTOR.rankCauseOfDeath()[causesCounter].name == "<world>") continue;
            output << "  \"" << MATCHESVECTOR.rankCauseOfDeath()[causesCounter].name << "\": " << MATCHESVECTOR.rankCauseOfDeath()[causesCounter].kills << ",\n";
        }
        output << "  }\n" << "}\n\n" ;
    }
}