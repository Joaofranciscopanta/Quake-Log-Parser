#include <report.h>
#define PLAYERVECTOR game->matches[matchCounter].players
#define MATCHESVECTOR game->matches[matchCounter]
#define RANKEDPLAYERS game->matches[matchCounter].rankPlayers()

void printReport(Game * game){

    ofstream output;
    output.open("../output/output.json");
    for(int matchCounter = 0; matchCounter <= game->ongoingMatch; matchCounter++){
        output <<"\"game_"  << matchCounter << "\": {\n";
        output << "\"total_kills\":" << MATCHESVECTOR.totalKills << ",\n";
        output << "\"players\": [";
        for(int playerCounter = 0; playerCounter < PLAYERVECTOR.size(); playerCounter++){
            if(PLAYERVECTOR[playerCounter].name == "<world>") continue;
            output << "\"" << PLAYERVECTOR[playerCounter].name << "\"";
            if(playerCounter != PLAYERVECTOR.size()-1) output << ", ";
        }
        output << "],\n";
        output << "\"kills\": {\n";
        for(int playerCounter = 0; playerCounter < PLAYERVECTOR.size(); playerCounter++){
            if(RANKEDPLAYERS[playerCounter].name == "<world>") continue;
            output << "  \"" << RANKEDPLAYERS[playerCounter].name << "\": " << RANKEDPLAYERS[playerCounter].kills <<",\n";
        }
        output << "  }\n" << "}\n\n" ;
    }
}