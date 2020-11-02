#include <QCoreApplication>
#include <iostream>
#include <math.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Car.h>
#include <Speedway.h>


using namespace std;

SDL_Texture* loadTexture(const char* imgPath, SDL_Renderer* renderer){
    SDL_Surface* surface = SDL_LoadBMP(imgPath);
    if(!surface) return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

float degreesToRadians(float angleDegrees) {
   return (angleDegrees * 3.1415 / 180.0);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << SDL_GetError() << endl;

    SDL_Window* window = SDL_CreateWindow("Minha janela em SDL",
                                             SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             611, 575,
                                             0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    bool running = true;

    Car carro;
    carro.speed = 10;
    carro.texture = IMG_LoadTexture(renderer, "assets/images/carro.png");
    carro.destino = {.x= 265, .y= 410, .w= 37*2, .h= 54*2,};
    carro.angle = 0;

    Speedway pista;
    pista.texture = IMG_LoadTexture(renderer, "assets/images/speedway.png");


    SDL_Event event;

    while(running){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, pista.texture, NULL, &pista.destino);
        SDL_RenderCopyEx(renderer, carro.texture, NULL, &carro.destino, carro.angle*-1, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)){
            switch (event.type){
              case SDL_QUIT:
                 running = false;
                 break;
              case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_UP)  carro.direction.up = true;
                if (event.key.keysym.sym == SDLK_RIGHT) carro.direction.right = true;
                if (event.key.keysym.sym == SDLK_LEFT) carro.direction.left = true;
                if (event.key.keysym.sym == SDLK_DOWN) carro.direction.down = true;
                break;

            case SDL_KEYUP:
              if (event.key.keysym.sym == SDLK_UP) carro.direction.up = false;
              if (event.key.keysym.sym == SDLK_LEFT) carro.direction.left = false;
              if (event.key.keysym.sym == SDLK_RIGHT) carro.direction.right = false;
              if (event.key.keysym.sym == SDLK_DOWN) carro.direction.down = false;
            }
        }


        if(carro.direction.up){

            pista.destino.y += carro.speed * cos(degreesToRadians(carro.angle));
            pista.destino.x += carro.speed * sin(degreesToRadians(carro.angle));

        };

        if(carro.direction.down){
            pista.destino.y -= carro.speed * cos(degreesToRadians(carro.angle));
            pista.destino.x -= carro.speed * sin(degreesToRadians(carro.angle));
        }
        if(carro.direction.left){
            carro.angle += 2;
        };
        if(carro.direction.right){
            carro.angle -= 2;
        }

        SDL_Delay(1000/60);//60 FPS

    }



    SDL_DestroyTexture(pista.texture);
    SDL_DestroyTexture(carro.texture);
    SDL_DestroyWindow(window);

    SDL_Quit();



    return a.exec();
}
