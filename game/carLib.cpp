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

bool isNewLap(Speedway* pista, Car *carro){
    // CHECA SE O CARRO PASSOU DA LARGADA

    //usando coordenadas da pista por enquanto (tem q fazer uma função pra pegar as coordenadas do carrinho na textura dda pista)
    if(pista->destino.x <= -2970 && pista->destino.x >= -3210 &&
            pista->destino.y <= -1326 && pista->destino.y >= -1335){

        if(!carro->block_lap_increment){
            return true;
        }

    }
    return false;
}


void removeLapIncrementBlock(Speedway* pista, Car *carro){
    //tira o bloqueio de incrementar o lap
    if(pista->destino.x <= 215 && pista->destino.x >= -117 &&
            pista->destino.y <= -1326 && pista->destino.y >= -1335){

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
        }
}



void accelerate(Car* carro){

    if(carro->speed >= carro->max_speed){
        carro->speed = carro->max_speed;
        return;
    }
    /*
    if(carro->isOnGrass) carro->max_speed = 5;
    else carro->max_speed = 12;*/
   carro->speed += carro->acceleration;
   //ArrowAngleAcc(speedometer);

};

void brake(Car* carro){
    if (carro->speed < 0){
        carro->speed = 0;
        return;
    }
    carro->speed -= 0.09;
}


