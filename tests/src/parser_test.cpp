#include "gtest/gtest.h"
#include "../../src/include/myparser.h"

TEST(NameDetecSuite, killerNameTest_I){
    string sentence = "21:42 Kill: 1022 2 22: <world> killed Isgalamido by MOD_TRIGGER_HURT";
    stringstream ssSentence(sentence);
    vector<string> wordVector;
    string word;
    while(ssSentence >> word) wordVector.insert(wordVector.end(), word);
    string killer = detectKiller(wordVector);
    ASSERT_TRUE("<world>" == killer);
}

TEST(NameDetecSuite, killerNameTest_II){
    string sentence = "  7:12 Kill: 2 5 7: Dono da Bola killed Assasinu Credi by MOD_ROCKET_SPLASH";
    stringstream ssSentence(sentence);
    vector<string> wordVector;
    string word;
    while(ssSentence >> word) wordVector.insert(wordVector.end(), word);
    string killer = detectKiller(wordVector);
    ASSERT_TRUE("Dono da Bola" == killer);
}

TEST(NameDetecSuite, victimNameTest_I){
    string sentence = "21:42 Kill: 1022 2 22: <world> killed Isgalamido by MOD_TRIGGER_HURT";
    stringstream ssSentence(sentence);
    vector<string> wordVector;
    string word;
    while(ssSentence >> word) wordVector.insert(wordVector.end(), word);
    string victim = detectVictim(wordVector);
    ASSERT_TRUE("Isgalamido" == victim);
}

TEST(NameDetecSuite, victimNameTest_II){
    string sentence = "  7:12 Kill: 2 5 7: Dono da Bola killed Assasinu Credi by MOD_ROCKET_SPLASH";
    stringstream ssSentence(sentence);
    vector<string> wordVector;
    string word;
    while(ssSentence >> word) wordVector.insert(wordVector.end(), word);
    string victim = detectVictim(wordVector);
    ASSERT_TRUE("Assasinu Credi" == victim);
}

TEST(NameDetecSuite, causeDetecTest){
    string sentence = "21:42 Kill: 1022 2 22: <world> killed Isgalamido by MOD_TRIGGER_HURT";
    stringstream ssSentence(sentence);
    vector<string> wordVector;
    string word;
    while(ssSentence >> word) wordVector.insert(wordVector.end(), word);
    string killer = detectCauseOfDeath(wordVector);
    ASSERT_TRUE("MOD_TRIGGER_HURT" == killer);
}

TEST(ProcessSuite, processLineTest){
    Game game = *new Game();
    Match match = *new Match();
    ASSERT_TRUE(match.players.empty());
    ASSERT_TRUE(game.matches.empty());
    ASSERT_TRUE(match.totalKills==0);
    ASSERT_TRUE(match.causes.empty());

    string sentence = "  7:12 Kill: 2 5 7: Dono da Bola killed Assasinu Credi by MOD_ROCKET_SPLASH";
    processLine(sentence,&game,&match);

    ASSERT_TRUE(match.totalKills==1);
    ASSERT_TRUE(match.players.at(0).name == "Dono da Bola");
    ASSERT_TRUE(match.players.size()==2);
    ASSERT_FALSE(match.causes.empty());

    sentence = "  6:35 Kill: 2 4 6: Dono da Bola killed Zeh by MOD_ROCKET";
    processLine(sentence, &game, &match);

    ASSERT_TRUE(match.totalKills==2);
    ASSERT_TRUE(match.players.at(0).name == "Dono da Bola");
    ASSERT_TRUE(match.players.size()==3);
    ASSERT_TRUE(match.causes.size()==2);

    sentence = R"(1:47 InitGame: \sv_floodProtect\1\sv_maxPing\0\sv_minPing\0\sv_maxRate\10000\sv_minRate\0\sv_hostname\Code Miner)";
    processLine(sentence, &game, &match);

    ASSERT_TRUE(game.ongoingMatch==1);
    ASSERT_TRUE(game.matches.size()==1);
    ASSERT_TRUE(match.players.empty());
    ASSERT_FALSE(match.players.size()==2);
    ASSERT_ANY_THROW(match.players.at(0).name);

}

TEST(ProcessSuite, failTests){
    Game game = *new Game();
    Match match = *new Match();

    string sentence = "  6:35 Kill: 2 4 6: Dono Kill: Bola killed Zeh by MOD_ROCKET";
    ASSERT_ANY_THROW(processLine(sentence, &game, &match));

    sentence = "  6:35 Kill: 2 4 6: Dono da Bola killed killed by MOD_ROCKET";
    ASSERT_ANY_THROW(processLine(sentence, &game, &match));
    stringstream ssSentence(sentence);
    vector<string> wordVector;
    string word;
    while(ssSentence >> word) wordVector.insert(wordVector.end(), word);
    ASSERT_ANY_THROW(string killer = detectKiller(wordVector));

    sentence = "  6:35 Kill: 2 4 6: D o n o da B o l a killed Zeh by MOD_ROCKET";
    ASSERT_ANY_THROW(processLine(sentence, &game, &match));
}


int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


