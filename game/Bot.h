#ifndef BOT_H
#define BOT_H
#include <Car.h>

struct Bot{
    float x;
    float y;
    SDL_Point rotation_axis;
    Car carro;
};

#endif // BOT_H
