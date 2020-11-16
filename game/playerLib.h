#ifndef PLAYERLIB_H
#define PLAYERLIB_H
#include <Player.h>
#include <Speedway.h>

void handlePlayerDirections(Player *player, Speedway *pista);

void moveUp(Player *player, Speedway *pista);

void moveDown(Speedway* pista, Car *carro);

void updatePlayerCenterPoint(Player *player);

#endif // PLAYERLIB_H
