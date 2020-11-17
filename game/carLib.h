#ifndef CARLIB_H
#define CARLIB_H
#include <Speedway.h>
#include <Car.h>
#include <Speedometer.h>
#include <utils.h>
#include <string>

using namespace std;

//void moveUp(Speedway* pista, Car *carro);

//void moveDown(Speedway* pista, Car carro);

void turnLeft(Car* carro);

void turnRight(Car* carro);

void accelerate(Car* carro);

void desacelerate(Car* carro);

void brake(Car* carro);

void updateCarCoordinates(Car* carro, Speedway* pista);

//void handleCarDirections(Car* carro, Speedway* pista, Speedometer* speedometer);

void incrementCurrentLap(Car* carro, SDL_Rect* lapNumberOrigem);

bool isNewLap(Car *carro);

void removeLapIncrementBlock(Car *carro);

#endif // CARLIB_H
