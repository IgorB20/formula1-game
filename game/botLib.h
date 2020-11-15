#ifndef BOTLIB_H
#define BOTLIB_H
#include <Car.h>
#include <Speedway.h>
#include <Bot.h>
#include <Player.h>


void move(Bot* bot, Speedway* pista);

void adjustBotPosition(Player player, Bot* bot);

bool isSpeedwayColor(int red, int green, int blue);

void handleBotDirections(Bot* bot);

#endif // BOTLIB_H
