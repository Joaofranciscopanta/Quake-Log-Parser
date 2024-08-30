#include "include/report.h"
#include <iomanip>  // Para std::fixed e std::setprecision

void printReport(Game * game){
    ofstream output;
    output.open("output/matchresults.json");
    output << std::fixed << std::setprecision(2); // Formatação de números

    for(int matchCounter = 0; matchCounter <= game->ongoingMatch; matchCounter++){
        if (matchCounter >= game->matches.size()) {
            cerr << "Warning: matchCounter " << matchCounter << " exceeds the size of matches vector." << endl;
            continue;
        }

        auto& match = game->matches[matchCounter];
        output <<"\"game_"  << matchCounter << "\": {\n";
        output << "  \"total_kills\": " << match.totalKills << ",\n";
        output << "  \"players\": [";
        for(size_t playerCounter = 0; playerCounter < match.players.size(); playerCounter++){
            if(match.players[playerCounter].name == "<world>") continue;
            output << "\"" << match.players[playerCounter].name << "\"";
            if(playerCounter != match.players.size() - 1) output << ", ";
        }
        output << "],\n";
        output << "  \"kills\": {\n";
        for(size_t playerCounter = 0; playerCounter < match.players.size(); playerCounter++){
            if(match.rankPlayers()[playerCounter].name == "<world>") continue;
            output << "    \"" << match.rankPlayers()[playerCounter].name << "\": " << match.rankPlayers()[playerCounter].kills;
            if (playerCounter != match.players.size() - 1) output << ",\n";
        }
        output << "\n  }\n}\n\n";
    }

    output.close();
}

void printCausesOfDeath(Game * game){
    ofstream output;
    output.open("output/causesofdeath.json");
    output << std::fixed << std::setprecision(2); // Formatação de números

    for(int matchCounter = 0; matchCounter <= game->ongoingMatch; matchCounter++){
        if (matchCounter >= game->matches.size()) {
            cerr << "Warning: matchCounter " << matchCounter << " exceeds the size of matches vector." << endl;
            continue;
        }

        auto& match = game->matches[matchCounter];
        output <<"\"game_"  << matchCounter << "\": {\n";
        output << "  \"kills_by_means\": {\n";
        for(size_t causesCounter = 0; causesCounter < match.causes.size(); causesCounter++){
            if(match.rankCauseOfDeath()[causesCounter].name == "<world>") continue;
            output << "    \"" << match.rankCauseOfDeath()[causesCounter].name << "\": " << match.rankCauseOfDeath()[causesCounter].kills;
            if (causesCounter != match.causes.size() - 1) output << ",\n";
        }
        output << "\n  }\n}\n\n";
    }

    output.close();
}