#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H
#include <SDL2/SDL.h>

struct Speedometer {
    SDL_Texture* textureArrow = nullptr;
    SDL_Rect destinoArrow;
    SDL_Texture* textureSpeedometer = nullptr;
    SDL_Rect destinoSpeedometer;
    float angle;
    SDL_Point* center;
};



#endif // SPEEDOMETER_H
