#include <gameLib.h>
#include <iostream>
#include <vector>

using namespace std;


Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;

    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}





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

    Speedway pista;
    SDL_Surface* surface = IMG_Load("assets/images/speedway.png");
    pista.texture = SDL_CreateTextureFromSurface(renderer, surface);


    SDL_LockSurface(surface);
     //cout << SDL_GetError() << endl;
    Uint32 pixelData = getpixel(surface, 131, 132);
    cout << ((pixelData >> 16) & 255) << endl;
    cout << ((pixelData >> 8) & 255) << endl;
    cout << (pixelData & 255) << endl;
    //cout << SDL_GetError() << endl;
    //cout << pixelData << endl;


    Car carro;
    carro.speed = 10;
    carro.acceleration = 0.0125;
    carro.max_speed = 7;
    carro.texture = IMG_LoadTexture(renderer, "assets/images/carro.png");
    carro.destino = {.x= 265, .y= 410, .w= 37*2, .h= 54*2,};
    carro.angle = 0;
    carro.coordinates.x = (carro.destino.x) + (pista.destino.x*-1);
    carro.coordinates.y = (carro.destino.y) + (pista.destino.y*-1);


    while(running){

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, pista.texture, NULL, &pista.destino);
        SDL_RenderCopyEx(renderer, carro.texture, NULL, &carro.destino, carro.angle*-1, NULL, SDL_FLIP_NONE);


        //menu lateral para mostra informações (velocidade atual, volta atual, tempo)
        //SDL_SetRenderDrawColor(renderer, 82, 79, 79, 0);
        //SDL_Rect lateralViewer = {.x = 450, .y=10, .w=175, .h=540};
        //SDL_RenderFillRect(renderer, &pista.hitboxes[0]);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);

        handleEvents(running, &carro);
        handleCarDirections(&carro, &pista);

        //cout << carro.speed << endl;

        SDL_Delay(1000/60);//60 FPS
    }

    SDL_DestroyTexture(pista.texture);
    SDL_DestroyTexture(carro.texture);
    SDL_FreeSurface(surface);
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

