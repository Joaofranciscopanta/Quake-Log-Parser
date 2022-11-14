#ifndef PARSER_C_GAME_H
#define PARSER_C_GAME_H
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Player{
public:
    string name;
    int kills;

    void incrementKills();
    void decrementKills();

    Player(){
        name ="nullPlayer";
        kills = 0;
    }
};

class Match{
public:
    int totalKills;
    vector<Player> players;

    void addPlayer(const string& name);
    bool isPlayerAdded(const string& name);

    Match(){
        totalKills = 0;
    }

};
class Game{
public:
    int ongoingMatch;
    vector<Match> matches;
    void incrementOngoingMatch();
    Game(){
        ongoingMatch = 0;
    };
};

#endif //PARSER_C_GAME_H
