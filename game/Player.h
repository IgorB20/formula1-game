#ifndef PLAYER_H
#define PLAYER_H
#include <Car.h>
#include <Speedometer.h>

struct Player{
    Car carro;
    Speedometer speedometer;
    SDL_Point center;
};

#endif // PLAYER_H
