#ifndef CARLIB_H
#define CARLIB_H
#include <Speedway.h>
#include <Car.h>
#include <Speedometer.h>
#include <utils.h>
#include <string>

using namespace std;

void moveUp(Speedway* pista, Car *carro);

void moveDown(Speedway* pista, Car carro);

void turnLeft(Car* carro);

void turnRight(Car* carro);

void accelerate(Car* carro, Speedometer* speedometer);

void desacelerate(Car* carro, Speedometer* speedometer);

void brake(Car* carro);

void updateCarCoordinates(Car* carro, Speedway* pista);

void handleCarDirections(Car* carro, Speedway* pista, Speedometer* speedometer);

void incrementCurrentLap(Car* carro, SDL_Rect* lapNumberOrigem);

bool isNewLap(Speedway* pista, Car *carro);

void removeLapIncrementBlock(Speedway* pista, Car *carro);

#endif // CARLIB_H
