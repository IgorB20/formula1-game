#include <botLib.h>
#include <utils.h>
#include <math.h>
#include <iostream>
#include <carLib.h>
#include <utils.h>

using namespace std;

void move(Bot* bot, Speedway* pista){

    SDL_LockSurface(pista->surface);

    int testex = bot->carro.coordinates.x/3.5;
    int testey = bot->carro.coordinates.y/3.5;
    //cout << testex << ", " << testey << endl;

    int next_x = testex - bot->carro.speed * sin(degreesToRadians(bot->carro.angle))*8;
    int next_y = testey - bot->carro.speed * cos(degreesToRadians(bot->carro.angle))*8;

    Uint32 pixelData = getpixel(pista->surface, next_x, next_y);

    int red = (pixelData & 255);
    int green = ((pixelData >> 8) & 255);
    int blue = ((pixelData >> 16) & 255);

    if(!isSpeedwayColor(red, green, blue) ){

        float anguloToLeft = bot->carro.angle + 20;

        int x_left = testex - bot->carro.speed * sin(degreesToRadians(anguloToLeft))*8;
        int y_left = testey - bot->carro.speed * cos(degreesToRadians(anguloToLeft))*8;

        Uint32 pixelDataLeft = getpixel(pista->surface, x_left, y_left);
        int r_left = (pixelDataLeft & 255);
        int g_left = ((pixelDataLeft >> 8) & 255);
        int b_left = ((pixelDataLeft >> 16) & 255);

        float anguloToRight = bot->carro.angle - 20;
        int x_right = testex - bot->carro.speed * sin(degreesToRadians(anguloToRight))*8;
        int y_right = testey - bot->carro.speed * cos(degreesToRadians(anguloToRight))*8;
        Uint32 pixelDataRight = getpixel(pista->surface, x_right, y_right);
        int r_right = (pixelDataRight & 255);
        int g_right = ((pixelDataRight >> 8) & 255);
        int b_right = ((pixelDataRight >> 16) & 255);
        //cout << r_left << ", " << g_left << ", " << b_left << endl;

        if(isSpeedwayColor(r_right, g_right, b_right)){
            //cout << "direita" << endl;
            bot->carro.angle -= 5;
        }else{

            if(isSpeedwayColor(r_left, g_left, b_left)){
                //cout << "esquerda" << endl;
                bot->carro.angle += 5;


            }
        }


        SDL_Point superior_esquerdo = {.x = testex, .y=testey};
        Uint32 pixelData1 = getpixel(pista->surface, superior_esquerdo.x, superior_esquerdo.y);
        int r_1 = (pixelData1 & 255);
        int g_1 = ((pixelData1 >> 8) & 255);
        int b_1 = ((pixelData1 >> 16) & 255);


        SDL_Point superior_direito = {.x = (testex + bot->carro.destino.w), .y=testey};
        Uint32 pixelData2 = getpixel(pista->surface, superior_direito.x, superior_direito.y);
        int r_2 = (pixelData2 & 255);
        int g_2 = ((pixelData2 >> 8) & 255);
        int b_2 = ((pixelData2 >> 16) & 255);

        /*
        SDL_Point inferior_esquerdo = {.x = testex, .y=(testey + bot->carro.destino.h)};
        Uint32 pixelData3 = getpixel(pista->surface, inferior_esquerdo.x, inferior_esquerdo.y);
        int r_3 = (pixelData3 & 255);
        int g_3 = ((pixelData3 >> 8) & 255);
        int b_3 = ((pixelData3 >> 16) & 255);

        SDL_Point inferior_direito  = {.x = (testex + bot->carro.destino.w), .y=(testey + bot->carro.destino.h)};
        Uint32 pixelData4 = getpixel(pista->surface, inferior_direito.x, inferior_direito.y);
        int r_4 = (pixelData4 & 255);
        int g_4 = ((pixelData4 >> 8) & 255);
        int b_4 = ((pixelData4 >> 16) & 255);
*/
          if(!isSpeedwayColor(r_1, g_1, b_1)) bot->carro.angle -= 3;
           if(!isSpeedwayColor(r_2, g_2, b_2)) bot->carro.angle += 3;

    }

      //accelerate(&bot->carro);
      bot->y -= bot->carro.speed * cos(degreesToRadians(bot->carro.angle));
      bot->x -= bot->carro.speed * sin(degreesToRadians(bot->carro.angle));
      bot->carro.destino.y = bot->y;
      bot->carro.destino.x = bot->x;

      updateCarCoordinates(&bot->carro, pista);
      removeLapIncrementBlock(&bot->carro);
      //cout << bot->carro.speed << endl;


    SDL_UnlockSurface(pista->surface);
};

void handleBotDirections(Bot* bot){
    if(bot->carro.direction.up){
        accelerate(&bot->carro);
    }else{
        desacelerate(&bot->carro);
   }

    if(bot->carro.direction.down){
        brake(&bot->carro);
    }

};

bool isSpeedwayColor(int red, int green, int blue){
    if((red == 115 && green == 123 && blue == 132) ||
       (red == 115 && green == 115 && blue == 123) ||
        (red == 107 && green == 115 && blue == 123) ||
            (red == 115 && green == 123 && blue == 133)){
          return true;
    }else{
        return false;
    }
};


void adjustBotPosition(Player player, Bot* bot){

    //eixo de rotação do bot sempre é o player
    /*
    bot->rotation_axis.x = 0 - (bot->carro.destino.x - (player.carro.destino.x+player.carro.destino.w/2));
    bot->rotation_axis.y = 0 - (bot->carro.destino.y - (player.carro.destino.y+player.carro.destino.h/2));
    */
    bot->y += player.carro.speed * cos(degreesToRadians(player.carro.angle));
    bot->x += player.carro.speed * sin(degreesToRadians(player.carro.angle));
    bot->carro.destino.y = bot->y;
    bot->carro.destino.x = bot->x;
}
