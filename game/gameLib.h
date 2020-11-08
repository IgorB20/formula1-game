#ifndef GAMELIB_H
#define GAMELIB_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Car.h>
#include <Speedway.h>
#include <Speedometer.h>
#include <carLib.h>
#include <utils.h>
#include <math.h>
#include <speedometerlib.h>


void init();

void handleEvents(bool &running, Car* carro);

#endif // GAMELIB_H
