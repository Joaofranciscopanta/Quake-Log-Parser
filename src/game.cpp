#include "game.h"
using namespace std;

typedef enum {
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
} meansOfDeath_t;

//Player class functions
void Player::incrementKills() {
    this->kills++;
}

void Player::decrementKills() {
    kills--;
}

//Match class functions

//Adds a player to the Player vector.
void Match::addPlayer(const string& name) {
    Player player = *new Player();
    player.name = name;
    players.insert(players.end(),player);
}

//Verifies if player is already inserted into vector
bool Match::isPlayerAdded(const string& name) {
    for(Player p : players)
        if (p.name == name)
            return true;
    return false;
}

vector<Player> Match::rankPlayers() const {
    vector<Player> auxList = players;
    std::sort(auxList.begin(),auxList.end());
    std::reverse(auxList.begin(),auxList.end());
    return auxList;
}


//Game class functions
void Game::incrementOngoingMatch() {
    ongoingMatch++;
}

