#ifndef MY_LOG_PARSER_PARSER_H
#define MY_LOG_PARSER_PARSER_H
#include <iostream>
#include <cstring>
#include <cstdio>
#include <game.h>
void parse();
void processLine(char **words, Game *game, Match *);
#endif //MY_LOG_PARSER_PARSER_H
