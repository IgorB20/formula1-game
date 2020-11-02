#ifndef CAR_H
#define CAR_H
#include <SDL2/SDL.h>
#include <Direction.h>

struct Car {
    int speed;
    int max_speed;
    float acceleration;
    int race_position;
    int lap_time;
    int total_time;
    int current_lap;
    float angle;
    Direction direction;
    SDL_Texture* texture = nullptr;
    SDL_Rect destino;
};


#endif // CAR_H
