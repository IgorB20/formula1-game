#include <Speedometer.h>
#include <utils.h>
#include <iostream>

using namespace std;
void ArrowAngleDes(Speedometer* speedometer) {
    speedometer->angle -= 0.6;
    if (speedometer->angle < 0){
        speedometer->angle = 0;
    }
};

void ArrowAngleBrake(Speedometer* speedometer) {
    speedometer->angle -= 1.5;
    if (speedometer->angle < 0){
        speedometer->angle = 0;
    }
};

void ArrowAngleAcc(Speedometer* speedometer) {
    speedometer->angle += 0.3*5;
    if (speedometer->angle > 180){
        speedometer->angle = 180;
    }
};
