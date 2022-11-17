#ifndef PARSER_C_GAME_H
#define PARSER_C_GAME_H
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;
enum meansOfDeath_t{
    MOD_UNKNOWN,
    MOD_SHOTGUN,
    MOD_GAUNTLET,
    MOD_MACHINEGUN,
    MOD_GRENADE,
    MOD_GRENADE_SPLASH,
    MOD_ROCKET,
    MOD_ROCKET_SPLASH,
    MOD_PLASMA,
    MOD_PLASMA_SPLASH,
    MOD_RAILGUN,
    MOD_LIGHTNING,
    MOD_BFG,
    MOD_BFG_SPLASH,
    MOD_WATER,
    MOD_SLIME,
    MOD_LAVA,
    MOD_CRUSH,
    MOD_TELEFRAG,
    MOD_FALLING,
    MOD_SUICIDE,
    MOD_TARGET_LASER,
    MOD_TRIGGER_HURT,
    MOD_NAIL,
    MOD_CHAINGUN,
    MOD_PROXIMITY_MINE,
    MOD_KAMIKAZE,
    MOD_JUICED,
    MOD_GRAPPLE
};

class CauseOfDeath{
public:
    string name;
    int kills;

    bool operator< (const CauseOfDeath &other) const{
        return kills < other.kills;
    }
    CauseOfDeath(){
        name ="nullMOD";
        kills = 0;
    }
};

class Player{
public:
    string name;
    int kills;

    bool operator< (const Player &other) const{
        return kills < other.kills;
    }

    Player(){
        name ="nullPlayer";
        kills = 0;
    }
};

class Match{
public:
    int totalKills;
    vector<Player> players;
    vector<CauseOfDeath> causes;

    //IMPLEMENT TEMPLATES
    void addPlayer(const string& name);
    void addCause(const string& name);
    bool isPlayerAdded(const string& name);
    bool isCauseAdded(const string& name);
    vector<Player> rankPlayers() const;
    vector<CauseOfDeath> rankCauseOfDeath() const;

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
