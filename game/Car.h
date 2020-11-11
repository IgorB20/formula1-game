#ifndef CAR_H
#define CAR_H
#include <SDL2/SDL.h>
#include <Direction.h>

struct Car {
    float speed;
    float max_speed;
    float acceleration;
    int race_position;
    int lap_time;
    int total_time;
    int current_lap = 1;
    float angle;
    bool block_lap_increment = true; //não deixa ficar atualizando infinitamente o lap atual
    SDL_Point coordinates;
    Direction direction;
    SDL_Texture* texture = nullptr;
    SDL_Rect destino;
    SDL_Rect origem;
};


#endif // CAR_H
