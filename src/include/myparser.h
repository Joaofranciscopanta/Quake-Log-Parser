#ifndef MY_LOG_PARSER_PARSER_H
#define MY_LOG_PARSER_PARSER_H
#include <iostream>
#include <cstring>
#include <cstdio>
#include "game.h"
#include "report.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

void parse();
void processLine(string words, Game *game, Match *);
void endMatch(Game *, Match *);

string detectCauseOfDeath(vector<string> words);
string detectKiller(const vector<string>& words);
string detectVictim(const vector<string>& words);

#endif //MY_LOG_PARSER_PARSER_H
