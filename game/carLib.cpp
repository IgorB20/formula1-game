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

void moveUp(Speedway* pista, Car *carro){



    //o parametro carro nao precisa ser um ponteiro nessa função!!
    pista->destino.y += carro->speed * cos(degreesToRadians(carro->angle));
    pista->destino.x += carro->speed * sin(degreesToRadians(carro->angle));


    updateCarCoordinates(carro, pista);
    removeLapIncrementBlock(pista, carro);

    cout << carro->coordinates.x << ", " << carro->coordinates.y << endl;

    //cout << testex  << ", " << testey << endl;
    //cout << carro->speed << endl;

    //int testex = (carro->coordinates.x) - 3000;
    //int testey = (carro->coordinates.y) - 1400;

    //SDL_LockSurface(pista->surface);
    //cout << SDL_GetError() << endl;
    //Uint32 pixelData = getpixel(pista->surface, testex, testey);

    //int red = (pixelData & 255);
    //int green = ((pixelData >> 8) & 255);
    //int blue = ((pixelData >> 16) & 255);

    //cout << red << ", " << green << ", " << ", " <<  blue << endl;

    //if(carro->direction.up){

    //}


     //SDL_UnlockSurface(pista->surface);
}



void moveDown(Speedway* pista, Car *carro){
    pista->destino.y -= carro->speed * cos(degreesToRadians(carro->angle));
    pista->destino.x -= carro->speed * sin(degreesToRadians(carro->angle));

    //updateCarCoordinates(carro, "DOWN");
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
    if(carro->speed == 0) return;
    carro->angle += 2;
};

void turnRight(Car* carro){
     if(carro->speed == 0) return;
     carro->angle -= 2;
};


void desacelerate(Car* carro, Speedometer* speedometer){
    if (carro->speed < 0){
        carro->speed = 0;
        return;
    }

        if (carro->speed > 0)
        {
            carro->speed -= 0.04;
            ArrowAngleDes(speedometer);
        }

     //cout << carro->speed << endl;
}



void accelerate(Car* carro, Speedometer* speedometer){
    if(carro->speed >= carro->max_speed){
        carro->speed = carro->max_speed;
        return;
    }

   carro->speed += carro->acceleration;
   ArrowAngleAcc(speedometer);

};

void brake(Car* carro){
    if (carro->speed < 0){
        carro->speed = 0;
        return;
    }
    carro->speed -= 0.09;
}


void handleCarDirections(Car* carro, Speedway* pista, Speedometer* speedometer){
    if(carro->direction.up){
        accelerate(carro, speedometer);
    }else{
         desacelerate(carro, speedometer);
    }

    if(carro->direction.left) turnLeft(carro);

    if(carro->direction.right) turnRight(carro);


   if(carro->direction.down){
       //FAZER FUNÇÃO DE FREIO!!
       //desacelerate(carro);
       if(carro->speed == 0){
            moveDown(pista, carro);
       }else{
           //freiar
           brake(carro);
           ArrowAngleBrake(speedometer);
       }
    }

    moveUp(pista, carro);

}
