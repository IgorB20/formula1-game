#include <carLib.h>
#include <speedometerlib.h>
#include <math.h>
#include <string>
#include <iostream>

using namespace std;

void moveUp(Speedway* pista, Car *carro){

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

    //o parametro carro nao precisa ser um ponteiro nessa função!!
    pista->destino.y += carro->speed * cos(degreesToRadians(carro->angle));
    pista->destino.x += carro->speed * sin(degreesToRadians(carro->angle));


    updateCarCoordinates(carro, "UP");


    //cout << testex  << ", " << testey << endl;
    cout << carro->speed << endl;

    //A VERIFICAÇÃO DE COLISÃO COM AS PAREDES TEM Q SER FEITA QUANDO OC ARRO ESTIVER DANDO RÉ TAMBÉM!!

    //down
    //if(carro->coordinates.y - carro->speed * cos(degreesToRadians(carro->angle)) >= (3584 - carro->destino.h)) return;

    //up -> DANDO ERRADO
    //if(carro->coordinates.y - carro->speed * cos(degreesToRadians(carro->angle)) <= (0 - carro->destino.h)) return;

    //right
    //if(carro->coordinates.x - carro->speed * sin(degreesToRadians(carro->angle)) >= (3584 - carro->destino.w)) return;

    //left ->DANDO ERRADO
    //if(carro->coordinates.x - carro->speed * sin(degreesToRadians(carro->angle)) <= (0 + carro->destino.w)) return;

}

void moveDown(Speedway* pista, Car *carro){
    pista->destino.y -= carro->speed * cos(degreesToRadians(carro->angle));
    pista->destino.x -= carro->speed * sin(degreesToRadians(carro->angle));

    updateCarCoordinates(carro, "DOWN");
}

void updateCarCoordinates(Car* carro, string direction){

    if(direction == "DOWN"){
        carro->coordinates.y += carro->speed * cos(degreesToRadians(carro->angle));
        carro->coordinates.x += carro->speed * sin(degreesToRadians(carro->angle));
     }

     if(direction == "UP"){
        carro->coordinates.y -= carro->speed * cos(degreesToRadians(carro->angle));
        carro->coordinates.x -= carro->speed * sin(degreesToRadians(carro->angle));
     }
};

void turnLeft(Car* carro){
    //if(carro->speed <= 1) return;
    carro->angle += 2;
};

void turnRight(Car* carro){
     //if(carro->speed <= 1) return;
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
