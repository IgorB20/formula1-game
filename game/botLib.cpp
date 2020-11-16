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

     //CANTO SUPERIOR ESQUERDO
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
            cout << "direita" << endl;
            bot->carro.angle -= 5;
        }else{

            if(isSpeedwayColor(r_left, g_left, b_left)){
                cout << "esquerda" << endl;
                bot->carro.angle += 5;
                if(bot->carro.origem.x != 6){
                        bot->carro.origem.x -= bot->carro.origem.w;
                }

            }
        }



    }

      //accelerate(&bot->carro);
      bot->y -= bot->carro.speed * cos(degreesToRadians(bot->carro.angle));
      bot->x -= bot->carro.speed * sin(degreesToRadians(bot->carro.angle));
      bot->carro.destino.y = bot->y;
      bot->carro.destino.x = bot->x;

      updateCarCoordinates(&bot->carro, pista);
      cout << bot->carro.speed << endl;
      cout << endl;

    //cout << bot->carro.coordinates.x << ", " << bot->carro.coordinates.y << endl;
    //cout << endl;
/*
    cout << bot->carro.destino.x << ", " << bot->carro.destino.y << endl;
    cout << bot->carro.coordinates.x << ", " << bot->carro.coordinates.y << endl;
*/
    SDL_UnlockSurface(pista->surface);
};

void handleBotDirections(Bot* bot){
    if(bot->carro.direction.up){
        accelerate(&bot->carro);
    }else{
        desacelerate(&bot->carro);
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
    bot->rotation_axis.x = 0 - (bot->carro.destino.x - (player.carro.destino.x+player.carro.destino.w/2));
    bot->rotation_axis.y = 0 - (bot->carro.destino.y - (player.carro.destino.y+player.carro.destino.h/2));

    bot->y += player.carro.speed * cos(degreesToRadians(player.carro.angle));
    bot->x += player.carro.speed * sin(degreesToRadians(player.carro.angle));
    bot->carro.destino.y = bot->y;
    bot->carro.destino.x = bot->x;
}
