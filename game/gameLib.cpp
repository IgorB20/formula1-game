#include <gameLib.h>
#include <iostream>
#include <vector>

using namespace std;



void init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << SDL_GetError() << endl;

    SDL_Window* window = SDL_CreateWindow("Minha janela em SDL",
                                             SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             611, 575,
                                             0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    bool running = true;

    Speedway pista;
    pista.surface = IMG_Load("assets/images/speedway.png");
    pista.texture = SDL_CreateTextureFromSurface(renderer, pista.surface);
    //pista.texture = IMG_LoadTexture(renderer, "assets/images/speedway.png");


    Car carro;

    carro.speed = 0;
    carro.acceleration = 0.1;
    carro.max_speed = 12;
    carro.texture = IMG_LoadTexture(renderer, "assets/images/carro.png");
    carro.destino = {.x= 265, .y= 410, .w= 37*2, .h= 54*2,};
    carro.angle = 0;
    carro.coordinates.x = (carro.destino.x) + (pista.destino.x*-1);
    carro.coordinates.y = (carro.destino.y) + (pista.destino.y*-1);


    Speedometer speedometer;
    speedometer.angle = 0;
    speedometer.rotation_axis.x = 113;
    speedometer.rotation_axis.y = 10;
    speedometer.textureArrow = IMG_LoadTexture(renderer, "assets/images/arrow.png");
    speedometer.destinoArrow = {.x= 20, .y= 540, .w= 113, .h= 20,};
    speedometer.textureSpeedometer = IMG_LoadTexture(renderer, "assets/images/speedometer.png");
    speedometer.destinoSpeedometer = {.x= 0, .y= 400, .w= 266, .h= 202,};


    while(running){

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, pista.texture, NULL, &pista.destino);
        SDL_RenderCopy(renderer, speedometer.textureSpeedometer, NULL, &speedometer.destinoSpeedometer);
        SDL_RenderCopyEx(renderer, speedometer.textureArrow, NULL, &speedometer.destinoArrow, speedometer.angle, &speedometer.rotation_axis, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, carro.texture, NULL, &carro.destino, carro.angle*-1, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);

        handleEvents(running, &carro);
        handleCarDirections(&carro, &pista, &speedometer);

        SDL_Delay(1000/60);//60 FPS
    }

    SDL_DestroyTexture(pista.texture);
    SDL_DestroyTexture(carro.texture);

    SDL_FreeSurface(pista.surface);

    SDL_DestroyTexture(speedometer.textureArrow);
    SDL_DestroyTexture(speedometer.textureSpeedometer);

    SDL_DestroyWindow(window);

    SDL_Quit();

}
void handleEvents(bool &running, Car* carro ){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT) running = false;

        bool tipoEvento = event.type == SDL_KEYDOWN;
        switch (event.key.keysym.sym) {
              case SDLK_UP:
                carro->direction.up = tipoEvento;
                  break;
              case SDLK_RIGHT:
                carro->direction.right = tipoEvento;
                  break;
              case SDLK_LEFT:
                carro->direction.left = tipoEvento;
                  break;
              case SDLK_DOWN:
                carro->direction.down = tipoEvento;
                  break;
              case SDLK_ESCAPE:
                running = false;
                break;

        }


    }
}
