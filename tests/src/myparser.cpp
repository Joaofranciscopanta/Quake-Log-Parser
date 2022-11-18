#include <malloc.h>
#include "include/myparser.h"

#define MAX_SPACES 3

void parse(){
    ifstream logs("processedlog.txt");
    string words;
    int counter;

    //Game is the main data structure for this parser, encapsulates an array of matches and a match counter
    Game game = *new Game();
    Match auxMatch = *new Match();

    //Transforming the logLine string into array of strings(words)
    while(getline(logs,words)){
        processLine(words, &game, &auxMatch);
    }
    endMatch(&game,&auxMatch);
    printReport(&game);
    printCausesOfDeath(&game);
}

/* This block turns an array of words into score based on victims and kills
 * This score is then sent into generateInfo() which stores that information
 */
void processLine(string sentence, Game *game, Match *auxMatch) {
    string victim;
    string killer;
    vector<string> wordVector;
    string auxWord;
    string causeOfDeath;
    int counter;

    //Tokenize string
    stringstream ssSentence(sentence);
    while(ssSentence >> auxWord)
        wordVector.insert(wordVector.end(), auxWord);

    //Increments match counter and stores a match on Game's matches vector
    if(wordVector.at(1) == "InitGame:"){
        endMatch(game, auxMatch);
        return;
    }

    //Detects killers and victims of each line
    auxMatch->totalKills++;
    killer = detectKiller(wordVector);
    if(!auxMatch->isPlayerAdded(killer))
        auxMatch->addPlayer(killer);

    victim = detectVictim(wordVector);
    if(!auxMatch->isPlayerAdded(victim))
        auxMatch->addPlayer(victim);


    for(counter = 0; wordVector.at(counter)!= "by"; counter++);
    //Finding cause of death by adding 1 to the counter since the victim loop above stops at "by"
    causeOfDeath = wordVector.at(counter+1);

    //int len=(int) strlen(causeOfDeath);
    //causeOfDeath[len-1] = 0;
    if(!auxMatch->isCauseAdded(causeOfDeath))
        auxMatch->addCause(causeOfDeath);

    //Counts causes of death
    for(counter = 0; counter< auxMatch->causes.size(); counter++) {
        if (auxMatch->causes.at(counter).name == causeOfDeath)
            auxMatch->causes.at(counter).kills++;
    }

    if(killer==victim) return;
    //Count playerkills and treats <world> kills
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

string detectKiller(vector<string> words) {
    string killer;
    for(int counter = 0; words.at(counter)!=("killed"); counter++ ){
        if (words.at(counter)== "Kill:") {
            counter += 4 ;
            killer=words[counter];
            continue;
        }
        killer.append(" ");
        killer.append(words[counter]);
    }
    return killer;
}

string detectVictim(vector<string> words){
    string victim;
    for(int counter = 0; words.at(counter) != "by"; counter++ ){
        if (words.at(counter) == "killed") {
            counter += 1;
            victim = words[counter];
            continue;
        }
        victim.append(" ");
        victim.append(words[counter]);
    }
    return victim;
}

void endMatch(Game *game, Match *match){

    //Printing a match report
    /*
    cout << "End of match number " << game->ongoingMatch << endl;
    cout << "Total kills: " << match->totalKills << endl;
    cout << "Players on this match: \n";
    for(Player p: match->rankPlayers() ) {
        if(p.name == "<world>") continue;
        cout << p.name << " with " << p.kills << " kills\n";
    }
    cout <<endl;
    */
    /*
    cout << "Top means of death: \n";
    for(CauseOfDeath c: match->rankCauseOfDeath() ) {
        cout << c.name << " with " << c.kills << " kills\n";
    }
    cout <<endl;
    */

    //Create definiteMatch to store in Game's matches vector
    Match definiteMatch = *new Match();
    definiteMatch.players = match->players;
    definiteMatch.causes = match->causes;
    definiteMatch.totalKills = match->totalKills;

    //Inserts definite
    game->matches.insert(game->matches.end(),definiteMatch);

    //Increment the matchcounter
    game->incrementOngoingMatch();

    //Resets auxMatch
    match->players.clear();
    match->totalKills = 0;
    for(auto & cause : match->causes){
        cause.kills=0;
    }
}