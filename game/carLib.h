#ifndef CARLIB_H
#define CARLIB_H
#include <Speedway.h>
#include <Car.h>
#include <utils.h>
#include <string>

void moveUp(Speedway* pista, Car *carro);

void moveDown(Speedway* pista, Car carro);

void turnLeft(Car* carro);

void turnRight(Car* carro);

void accelerate(Car* carro);

void desacelerate(Car* carro);

void handleCarDirections(Car* carro, Speedway* pista);
#endif // CARLIB_H
