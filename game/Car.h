#ifndef CAR_H
#define CAR_H
#include <SDL2/SDL.h>

struct Car {
    int speed;
    int max_speed;
    float acceleration;
    int position;
    int lap_time;
    int total_time;
    int current_lap;
    SDL_Texture* texture = nullptr;
    SDL_Rect destino;
};


#endif // CAR_H
