#include <gameLib.h>
#include <iostream>
#include <vector>
#include <botLib.h>
#include <Bot.h>
#include <Player.h>
#include <playerLib.h>
#include <math.h>

using namespace std;


void menu( SDL_Renderer * renderer ){
    bool menuAtivo = true;

    SDL_RenderCopy(renderer, IMG_LoadTexture(renderer,"assets/images/menucom.bmp"), NULL, NULL);
    Mix_Music* musicMenu = Mix_LoadMUS("assets/sounds/Music Menu.mp3");
    Mix_Music* music = Mix_LoadMUS("assets/sounds/Music.mp3");
    Mix_PlayMusic(musicMenu, -1);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 60); // 60 fps
    while (menuAtivo) {
        SDL_Event evento;

        SDL_PollEvent(&evento);
        if(evento.type == SDL_QUIT){

            SDL_Quit();
        }

        if (evento.type == SDL_KEYDOWN) {
            if (evento.key.keysym.sym == SDLK_KP_ENTER || evento.key.keysym.sym == SDLK_RETURN) {
                menuAtivo = false;
                Mix_PlayMusic(music,-1);
                Mix_FreeMusic(musicMenu);
                Mix_VolumeMusic(50);
            }
        }
    }
}

void checkPosition(Car *playerCar, Car* botCar){
    int maiorX = playerCar->coordinates.x;
    int maiorY = playerCar->coordinates.y;
    int menorX = botCar->coordinates.x;
    int menorY = botCar->coordinates.y;
    if(menorX > maiorX){
        maiorX = botCar->coordinates.x;
        menorX = playerCar->coordinates.x;
    }
    if(menorY > maiorY){
        maiorY = botCar->coordinates.y;
        menorY = playerCar->coordinates.y;
    }

    //cout << maiorX << ", " << maiorY << endl;
    if((maiorX - menorX) <= 150 && (maiorY - menorY <= 170)){
        cout << "TAO PERTO!!" << endl;

        float distancia = sqrt(pow((maiorX - menorX), 2) + pow((maiorY - menorY), 2));
        cout << distancia << endl;
        /*
        cout << playerCar->speed * cos(degreesToRadians(playerCar->angle)) << ", ";
        cout << playerCar->speed * sin(degreesToRadians(playerCar->angle)) << endl;

        cout << botCar->speed * cos(degreesToRadians(botCar->angle)) << ", ";
        cout << botCar->speed * sin(degreesToRadians(botCar->angle)) << endl;
        */
}



}

void init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << SDL_GetError() << endl;

      Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2, 6096);

    SDL_Window* window = SDL_CreateWindow("Minha janela em SDL",
                                             SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             611, 575,
                                             0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    bool running = true;




    Speedway pista;
    pista.destino = {.x= -3000, .y= -1660, .w=static_cast<int>(1024*3.5), .h= static_cast<int>(1024*3.5),};
    pista.x = pista.destino.x;
    pista.y = pista.destino.y;
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

    Player player;
    player.carro.pilot_name = "You";
    player.carro.race_position = 3;
    player.carro.speed = 0;
    player.carro.acceleration = 0.15;
    player.carro.max_speed = 12.5;
    player.carro.texture = IMG_LoadTexture(renderer, "assets/images/carro-sprites.png");
    player.carro.destino = {.x= 280, .y= 415, .w= 50, .h= 85,};
    player.carro.origem = {.x= 503, .y= 99, .w= 281, .h= 477,};
    player.carro.coordinates.x = (player.carro.destino.x) + (pista.destino.x*-1);
    player.carro.coordinates.y = (player.carro.destino.y) + (pista.destino.y*-1);

    /*player.center.x = player.carro.coordinates.x + (player.carro.destino.w/2);
    player.center.y = player.carro.coordinates.y + (player.carro.destino.h/2);
*/
    player.speedometer.angle = 0;
    player.speedometer.rotation_axis.x = 113;
    player.speedometer.rotation_axis.y = 10;
    player.speedometer.textureArrow = IMG_LoadTexture(renderer, "assets/images/arrow.png");
    player.speedometer.destinoArrow = {.x= 20, .y= 540, .w= 113, .h= 20,};
    player.speedometer.textureSpeedometer = IMG_LoadTexture(renderer, "assets/images/speedometer.png");
    player.speedometer.destinoSpeedometer = {.x= 0, .y= 400, .w= 266, .h= 202,};
    player.carro.Sound = Mix_LoadWAV("assets/sounds/Car Engine.wav");
    player.carro.Sound2 = Mix_LoadWAV("assets/sounds/Car Engine 2.wav");

    Bot bot1;
    bot1.carro.pilot_name = "Airton Senna";
    bot1.carro.race_position = 2;
    bot1.carro.direction.up = true;
    bot1.carro.speed = 0;
    bot1.carro.acceleration = 0.1;
    bot1.carro.max_speed = 12;
    bot1.carro.texture = IMG_LoadTexture(renderer, "assets/images/bot1.png");
    bot1.carro.destino = {.x= 380, .y= 265, .w= 75, .h= 100,};
    bot1.x = bot1.carro.destino.x;
    bot1.y = bot1.carro.destino.y;
    bot1.carro.coordinates.x = (bot1.carro.destino.x) + (pista.destino.x*-1);
    bot1.carro.coordinates.y = (bot1.carro.destino.y) + (pista.destino.y*-1);
    /*
    bot.rotation_axis.x = 0 - (bot.carro.destino.x - player.carro.destino.x);
    bot.rotation_axis.y = 0 - (bot.carro.destino.y - player.carro.destino.y);
*/
    Bot bot2;
    bot2.carro.pilot_name = "Felipe massa";
    bot2.carro.race_position = 1;
    bot2.carro.direction.up = true;
    bot2.carro.speed = 0;
    bot2.carro.acceleration = 0.14;
    bot2.carro.max_speed = 11.94;
    bot2.carro.texture = IMG_LoadTexture(renderer, "assets/images/bot2.png");
    bot2.carro.destino = {.x= 265, .y= 155, .w= 75, .h= 100,};
    bot2.x = bot2.carro.destino.x;
    bot2.y = bot2.carro.destino.y;
    bot2.carro.coordinates.x = (bot2.carro.destino.x) + (pista.destino.x*-1);
    bot2.carro.coordinates.y = (bot2.carro.destino.y) + (pista.destino.y*-1);






    SDL_Texture* lapText = IMG_LoadTexture(renderer, "assets/images/letters.png");
    //L
    SDL_Rect L_destino = {.x= 470, .y= 10, .w= 20, .h= 35};
    SDL_Rect L_origem = {.x= 111, .y= 89, .w= 49, .h= 79};

    //A
    SDL_Rect A_destino = {.x= 495, .y= 10, .w= 20, .h= 35};
    SDL_Rect A_origem = {.x= 9, .y= 3, .w= 49, .h= 79};

    //P
    SDL_Rect P_destino = {.x= 520, .y= 10, .w= 20, .h= 35};
    SDL_Rect P_origem = {.x= 316, .y= 89, .w= 49, .h= 79};


    SDL_Texture* lapNumber = IMG_LoadTexture(renderer, "assets/images/numbers.png");
    SDL_Rect lapNumberDestino = {.x= 555, .y= 9, .w= 25, .h= 35};
    SDL_Rect lapNumberOrigem = {.x= 122, .y= 18, .w= 90, .h= 144};

    menu(renderer);

    //int maxLaps = 1;
    vector<Bot*> bots;
    bots.push_back(&bot1);
    bots.push_back(&bot2);

    while(running){

        SDL_RenderClear(renderer);
        //SDL_RenderCopyEx(renderer, pista.texture, NULL, &pista.destino, player.carro.angle, &player.center, SDL_FLIP_NONE);
        SDL_RenderCopy(renderer, pista.texture, NULL, &pista.destino);
        for(Bot* bot : bots){
            SDL_RenderCopyEx(renderer, bot->carro.texture, NULL, &bot->carro.destino, bot->carro.angle*-1, NULL, SDL_FLIP_NONE);
        }


         SDL_RenderCopy(renderer, player.speedometer.textureSpeedometer, NULL, &player.speedometer.destinoSpeedometer);
         SDL_RenderCopyEx(renderer, player.speedometer.textureArrow, NULL, &player.speedometer.destinoArrow, player.speedometer.angle, &player.speedometer.rotation_axis, SDL_FLIP_NONE);

        SDL_RenderCopy(renderer, lapText, &L_origem, &L_destino);
        SDL_RenderCopy(renderer, lapText, &A_origem, &A_destino);
        SDL_RenderCopy(renderer, lapText, &P_origem, &P_destino);

        SDL_RenderCopy(renderer, lapNumber, &lapNumberOrigem, &lapNumberDestino);


        //SDL_RenderCopy(renderer, player.carro.texture, &player.carro.origem, &player.carro.destino);
        SDL_RenderCopyEx(renderer, player.carro.texture, &player.carro.origem, &player.carro.destino, player.carro.angle*-1, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);

        handleEvents(running, &player.carro);
        handlePlayerDirections(&player, &pista);

        for(Bot *bot : bots){
            handleBotDirections(bot);
            adjustBotPosition(player, bot);
            move(bot, &pista);
        }


        if(isNewLap(&player.carro)){

            incrementCurrentLap(&player.carro, &lapNumberOrigem);
        };

        /*
        if(isNewLap(&bot.carro)){
               if(bot.carro.current_lap == maxLaps){
                  bot.carro.direction.up = false;
                  bot.carro.direction.down = true;

               }else{
                   bot.carro.current_lap++;
                   bot.carro.block_lap_increment = true;
               }
        }*/

        //checkPosition(&player.carro, &bot.carro);

/*
        cout <<"you: " << player.carro.race_position << " " <<player.carro.coordinates.x <<", "<< player.carro.coordinates.y << endl;
        cout << bot.carro.race_position << " " << bot.carro.coordinates.x <<", "<< bot.carro.coordinates.y << endl;
        cout << endl;
*/




        SDL_Delay(1000/60);//60 FPS
    }

    Mix_FreeChunk(player.carro.Sound);
    Mix_CloseAudio();

    SDL_DestroyTexture(pista.texture);
    SDL_DestroyTexture(player.carro.texture);

    SDL_FreeSurface(pista.surface);

    SDL_DestroyTexture(speedometer.textureArrow);
    SDL_DestroyTexture(speedometer.textureSpeedometer);


    SDL_DestroyTexture(player.speedometer.textureArrow);
    SDL_DestroyTexture(player.speedometer.textureSpeedometer);
    for(Bot *bot : bots){
          SDL_DestroyTexture(bot->carro.texture);
    }

    SDL_DestroyWindow(window);

        cout << SDL_GetError() << endl;

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
