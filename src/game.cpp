#include "game.h"
using namespace std;



//Match class functions

//Adds a player to the Player vector.
void Match::addPlayer(const string& name) {
    Player player = *new Player();
    player.name = name;
    players.insert(players.end(),player);
}

void Match::addCause(const string& name) {
    CauseOfDeath cause = *new CauseOfDeath();
    cause.name = name;
    causes.insert(causes.end(),cause);
}

//Verifies if player is already inserted into vector
bool Match::isPlayerAdded(const string& name) {
    for(Player p : players)
        if (p.name == name)
            return true;
    return false;
}
bool Match::isCauseAdded(const string& name) {
    for(CauseOfDeath c : causes)
        if (c.name == name)
            return true;
    return false;
}
vector<Player> Match::rankPlayers() const {
    vector<Player> auxList = players;
    std::sort(auxList.begin(),auxList.end());
    std::reverse(auxList.begin(),auxList.end());
    return auxList;
}
vector<CauseOfDeath> Match::rankCauseOfDeath() const {
    vector<CauseOfDeath> auxList = causes;
    std::sort(auxList.begin(),auxList.end());
    std::reverse(auxList.begin(),auxList.end());
    return auxList;
}


//Game class functions
void Game::incrementOngoingMatch() {
    ongoingMatch++;
}

