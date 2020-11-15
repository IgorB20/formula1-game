#ifndef SPEEDWAY_H
#define SPEEDWAY_H
#include <SDL2/SDL.h>
#include <vector>

struct Speedway{

    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Rect destino;
    float x = -3000;
    float y = -1400;

};

#endif // SPEEDWAY_H
