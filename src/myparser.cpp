#include <malloc.h>
#include "include/myparser.h"

#define MAX_SPACES 3

void parse() {
    ifstream logs("processedlog.txt");
    string words;
    bool inMatch = false;
    Game game;
    Match auxMatch;

    while (getline(logs, words)) {
        cout << "Processing line: " << words << endl;

        if (words.find("InitGame:") != string::npos) {
            if (inMatch) {
                endMatch(&game, &auxMatch);
            }
            inMatch = true;
            continue;
        }
        if (inMatch) {
            processLine(words, &game, &auxMatch);
        }
    }

    if (inMatch) {
        endMatch(&game, &auxMatch);
    }
    printReport(&game);
    printCausesOfDeath(&game);
}

void processLine(string sentence, Game *game, Match *auxMatch) {
    string victim;
    string killer;
    vector<string> wordVector;
    string auxWord;
    string causeOfDeath;
    int counter;

    stringstream ssSentence(sentence);
    while(ssSentence >> auxWord)
        wordVector.insert(wordVector.end(), auxWord);

    if(wordVector.at(1) == "InitGame:"){
        endMatch(game, auxMatch);
        return;
    }

    auxMatch->totalKills++;
    killer = detectKiller(wordVector);
    if(!auxMatch->isPlayerAdded(killer))
        auxMatch->addPlayer(killer);

    victim = detectVictim(wordVector);
    if(!auxMatch->isPlayerAdded(victim))
        auxMatch->addPlayer(victim);


    for(counter = 0; wordVector.at(counter)!= "by"; counter++);
    causeOfDeath = wordVector.at(counter+1);

    if(!auxMatch->isCauseAdded(causeOfDeath))
        auxMatch->addCause(causeOfDeath);

    for(counter = 0; counter< auxMatch->causes.size(); counter++) {
        if (auxMatch->causes.at(counter).name == causeOfDeath)
            auxMatch->causes.at(counter).kills++;
    }

    if(killer==victim) return;
    for(counter = 0; counter< auxMatch->players.size(); counter++) {
        if (auxMatch->players.at(counter).name == killer)
            auxMatch->players.at(counter).kills++;
    }
    if(killer=="<world>") {
        for (counter = 0; counter < auxMatch->players.size(); counter++)
            if (auxMatch->players.at(counter).name == victim && auxMatch->players.at(counter).kills > 0)
                auxMatch->players.at(counter).kills--;
    }
}
string detectCauseOfDeath(vector<string> words){
    int counter;
    for(counter = 0; words.at(counter)!= "by"; counter++);
    return words.at(counter+1);
}

std::string detectKiller(const std::vector<std::string>& words) {
    std::string killer;
    auto it = std::find(words.begin(), words.end(), "killed");

    if (it != words.end()) {
        int killedIndex = std::distance(words.begin(), it);
        int startIdx = -1;

        for (int i = killedIndex - 1; i >= 0; --i) {
            if (words[i] == "Kill:") {
                startIdx = i + 4; // Pular "Kill:" e os três números seguintes
                break;
            }
        }

        for (int j = startIdx; j < killedIndex; ++j) {
            if (!words[j].empty() && !std::all_of(words[j].begin(), words[j].end(), ::isdigit)) {
                if (!killer.empty()) {
                    killer += " "; // Adicionar espaço entre palavras
                }
                killer += words[j];
            }
        }
    }
    return killer;
}

std::string detectVictim(const std::vector<std::string>& words) {
    std::string victim;
    auto it = std::find(words.begin(), words.end(), "by");

    if (it != words.end()) {
        int byIndex = std::distance(words.begin(), it);
        int startIdx = -1;

        // Encontrar o índice de início do nome da vítima antes de "by"
        for (int i = byIndex - 1; i >= 0; --i) {
            if (words[i] == "killed") {
                startIdx = i + 1; // Pular "killed"
                break;
            }
        }

        // Construir o nome da vítima
        for (int j = startIdx; j < byIndex; ++j) {
            // Verifica se a palavra é um número ou uma string vazia
            if (!words[j].empty() && !std::all_of(words[j].begin(), words[j].end(), ::isdigit)) {
                if (!victim.empty()) {
                    victim += " "; // Adicionar espaço entre palavras
                }
                victim += words[j];
            }
        }
    }
    return victim;
}

void endMatch(Game *game, Match *match) {
    cout << "End of match number " << game->ongoingMatch << endl;
    cout << "Total kills: " << match->totalKills << endl;
    cout << "Players in this match: \n";
    for (Player p : match->rankPlayers()) {
        if (p.name == "<world>") continue;
        cout << p.name << " with " << p.kills << " kills\n";
    }
    cout << endl;

    cout << "Top causes of death: \n";
    for (CauseOfDeath c : match->rankCauseOfDeath()) {
        cout << c.name << " with " << c.kills << " kills\n";
    }
    cout << endl;

    // Adiciona a partida finalizada ao histórico
    game->matches.push_back(*match);

    // Incrementa o número da partida em andamento
    game->incrementOngoingMatch();

    // Reseta o estado da partida atual
    match->players.clear();
    match->totalKills = 0;
    for (auto &cause : match->causes) {
        cause.kills = 0;
    }
}