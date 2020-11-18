#include <carLib.h>
#include <speedometerlib.h>
#include <math.h>
#include <string>
#include <iostream>


using namespace std;

void incrementCurrentLap(Car* carro, SDL_Rect* lapNumberOrigem){
   carro->current_lap++;
   carro->block_lap_increment = true;
   lapNumberOrigem->x += lapNumberOrigem->w;
};

bool isNewLap(Car *carro){

    // CHECA SE O CARRO PASSOU DA LARGADA
    if(carro->coordinates.x <= 3458 && carro->coordinates.x >= 3258 &&
            carro->coordinates.y <= 1760 && carro->coordinates.y >= 1711){
        if(!carro->block_lap_increment){
            return true;
        }

    }
    return false;
}


void removeLapIncrementBlock(Car *carro){

    if(carro->coordinates.x <= 444 && carro->coordinates.x >= 56 &&
            carro->coordinates.y <= 1823 && carro->coordinates.y >= 1785){

        carro->block_lap_increment = false;

    }

}

void updateCarCoordinates(Car* carro, Speedway* pista){

    carro->coordinates.x = (carro->destino.x) + (pista->destino.x*-1);
    carro->coordinates.y = (carro->destino.y) + (pista->destino.y*-1);

};

void turnLeft(Car* carro){
    carro->origem.x = 81;
    carro->angle += 2;
};

void turnRight(Car* carro){
     carro->origem.x = 935;
     carro->angle -= 2;
};


void desacelerate(Car* carro){
    if (carro->speed < 0){
        carro->speed = 0;
        return;
    }

        if (carro->speed > 0)
        {
            if(carro->isOnGrass){
                carro->speed -= 0.2;
            }else{
                carro->speed -= 0.04;
            }
            Mix_PlayChannel(0,carro->Sound2,0);
        }
}



void accelerate(Car* carro){


    if(carro->isOnGrass) carro->max_speed = 5;
    else carro->max_speed = 12;

    if(carro->speed >= carro->max_speed){
        carro->speed = carro->max_speed;
        Mix_PlayChannel(0,carro->Sound,0);
        return;
    }
   carro->speed += carro->acceleration;
   Mix_PlayChannel(0,carro->Sound,0);
   //ArrowAngleAcc(speedometer);

};

void brake(Car* carro){
    if (carro->speed < 0){
        carro->speed = 0;
        return;
    }
    carro->speed -= 0.09;
}


