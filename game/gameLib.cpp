#include <gameLib.h>
#include <iostream>

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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    bool running = true;

    Car carro;
    carro.speed = 0;
    carro.acceleration = 0.0125;
    carro.max_speed = 7;
    carro.texture = IMG_LoadTexture(renderer, "assets/images/carro.png");
    carro.destino = {.x= 265, .y= 410, .w= 37*2, .h= 54*2,};
    carro.angle = 0;

    Speedway pista;
    pista.texture = IMG_LoadTexture(renderer, "assets/images/speedway.png");

    while(running){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, pista.texture, NULL, &pista.destino);
        SDL_RenderCopyEx(renderer, carro.texture, NULL, &carro.destino, carro.angle*-1, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);

        handleEvents(running, &carro);
        handleCarDirections(&carro, &pista);

        cout << carro.speed << endl;

        SDL_Delay(1000/60);//60 FPS
    }

    SDL_DestroyTexture(pista.texture);
    SDL_DestroyTexture(carro.texture);
    SDL_DestroyWindow(window);

    SDL_Quit();

}

void handleEvents(bool &running, Car* carro){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
          case SDL_QUIT:
             running = false;
             break;
          case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_UP)  carro->direction.up = true;
            if (event.key.keysym.sym == SDLK_RIGHT) carro->direction.right = true;
            if (event.key.keysym.sym == SDLK_LEFT) carro->direction.left = true;
            if (event.key.keysym.sym == SDLK_DOWN) carro->direction.down = true;
            break;

        case SDL_KEYUP:
          if (event.key.keysym.sym == SDLK_UP) carro->direction.up = false;
          if (event.key.keysym.sym == SDLK_LEFT) carro->direction.left = false;
          if (event.key.keysym.sym == SDLK_RIGHT) carro->direction.right = false;
          if (event.key.keysym.sym == SDLK_DOWN) carro->direction.down = false;
          break;
        }
    }
}

