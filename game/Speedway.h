#ifndef SPEEDWAY_H
#define SPEEDWAY_H
#include <SDL2/SDL.h>

struct Speedway{
    SDL_Texture* texture = nullptr;
    SDL_Rect destino = {.x= -3000, .y= -1400, .w=static_cast<int>(1024*3.5), .h= static_cast<int>(1024*3.5),};
};

#endif // SPEEDWAY_H
