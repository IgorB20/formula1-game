#include <botLib.h>
#include <utils.h>
#include <math.h>
#include <iostream>

using namespace std;

void adjustBotPosition(Car* bot, Car player, Speedway){
    if(player.speed < 0) return;
    bot->destino.y += player.speed * cos(degreesToRadians(player.angle));
    bot->destino.x += player.speed * sin(degreesToRadians(player.angle));

    cout << bot->destino.x << ", " << bot->destino.y << endl;

}
