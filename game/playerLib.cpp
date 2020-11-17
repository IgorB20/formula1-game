#include <playerLib.h>
#include <carLib.h>
#include <math.h>
#include <speedometerlib.h>
#include <iostream>


void moveUp(Player *player, Speedway *pista){
    if(player->carro.speed == 0) return;

    pista->y += player->carro.speed * cos(degreesToRadians(player->carro.angle));
    pista->x += player->carro.speed * sin(degreesToRadians(player->carro.angle));

    pista->destino.y = pista->y;
    pista->destino.x = pista->x;

    updateCarCoordinates(&player->carro, pista);
    removeLapIncrementBlock(&player->carro);
        //updatePlayerCenterPoint(player);


    //SDL_LockSurface(pista->surface);
    // cout << SDL_GetError() << endl;
    //int testex = carro->coordinates.x/3.5;
    //int testey = carro->coordinates.y/3.5;
    //cout << testex << ", " << testey << endl;


/*
    Uint32 pixelData = getpixel(pista->surface, testex, testey);
    //cout << pixelData << endl;
    int red = (pixelData & 255);
    int green = ((pixelData >> 8) & 255);
    int blue = ((pixelData >> 16) & 255);
    SDL_UnlockSurface(pista->surface);
    //cout << red << ", " << green << ", " << ", " <<  blue << endl;

    //DEIXA O CARRO MAIS LENTO NA GRAMA
    if((red == 24 && green == 165 && blue == 41) ||
            (red == 16 && green == 148 && blue == 33) ||
                (red == 41 && green == 181 && blue == 57)
            ){

            carro->isOnGrass = true;

    }else{
        carro->isOnGrass = false;
    }*/

    //carro->speed = 2;
    //cout << carro->coordinates.x << ", " << carro->coordinates.y << endl;

    //cout << testex  << ", " << testey << endl;
    //cout << carro->speed << endl;

    //int testex = (carro->coordinates.x) - 3000;
    //int testey = (carro->coordinates.y) - 1400;


    //int red = (pixelData & 255);
    //int green = ((pixelData >> 8) & 255);
    //int blue = ((pixelData >> 16) & 255);

    //cout << red << ", " << green << ", " << ", " <<  blue << endl;

    //if(carro->direction.up){

    //}


     //SDL_UnlockSurface(pista->surface);
};

void moveDown(Speedway* pista, Car *carro){
    carro->speed = -2;
    pista->destino.y += carro->speed * cos(degreesToRadians(carro->angle));
    pista->destino.x += carro->speed * sin(degreesToRadians(carro->angle));
}


/*
void updatePlayerCenterPoint(Player *player){
    player->center.x = player->carro.coordinates.x + (player->carro.destino.w/2);
    player->center.y = player->carro.coordinates.y + (player->carro.destino.h/2);
};*/


void handlePlayerDirections(Player *player, Speedway *pista){
    if(player->carro.direction.up){
        accelerate(&player->carro);
        ArrowAngleAcc(&player->speedometer);
    }else{
         desacelerate(&player->carro);
         ArrowAngleDes(&player->speedometer);
    }

    if(player->carro.direction.left){
        turnLeft(&player->carro);
    };

    if(player->carro.direction.right) turnRight(&player->carro);

    if(!player->carro.direction.right && !player->carro.direction.left) player->carro.origem.x = 503;

   if(player->carro.direction.down){

       if(player->carro.speed == 0){

            moveDown(pista, &player->carro);
       }else{
           //freiar
           brake(&player->carro);
           ArrowAngleBrake(&player->speedometer);
       }
    }

    moveUp(player, pista);
};
