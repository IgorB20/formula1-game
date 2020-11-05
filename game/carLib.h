#ifndef CARLIB_H
#define CARLIB_H
#include <Speedway.h>
#include <Car.h>
#include <utils.h>
#include <string>

using namespace std;

void moveUp(Speedway* pista, Car *carro);

void moveDown(Speedway* pista, Car carro);

void turnLeft(Car* carro);

void turnRight(Car* carro);

void accelerate(Car* carro);

void desacelerate(Car* carro);

void updateCarCoordinates(Car* carro, string direction);

void handleCarDirections(Car* carro, Speedway* pista);
#endif // CARLIB_H
