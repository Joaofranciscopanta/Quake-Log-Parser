#ifndef MY_LOG_PARSER_PARSER_H
#define MY_LOG_PARSER_PARSER_H
#include <stdio.h>
#include <string.h>
struct Match;
struct Game;
struct Player;
void parse();
void proccessLine(char**, struct Game*);
#endif //MY_LOG_PARSER_PARSER_H
