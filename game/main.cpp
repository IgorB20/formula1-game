#include <QCoreApplication>
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

SDL_Texture* loadTexture(const char* imgPath, SDL_Renderer* renderer){
    SDL_Surface* surface = SDL_LoadBMP(imgPath);
    if(!surface) return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
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

    //SDL_Texture *field_texture = loadTexture("assets/tabuleiro.bmp", renderer);

    SDL_Texture *field_texture = IMG_LoadTexture(renderer, "assets/bola.png");
    cout << field_texture << endl;
    cout << SDL_GetError() << endl;

    bool running = true;


    SDL_Event event;
    while(running){

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, field_texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)){
            switch (event.type){
              case SDL_QUIT:
                 running = false;
                    break;
            }
        }
    }



    SDL_DestroyTexture(field_texture);
    SDL_DestroyWindow(window);

    SDL_Quit();



    return a.exec();
}
