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

void updateCarCoordinates(Car* carro, string direction);

void handleCarDirections(Car* carro, Speedway* pista, Speedometer* speedometer );
#endif // CARLIB_H
