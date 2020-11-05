#include <carLib.h>
#include <math.h>
#include <string>
#include <iostream>

using namespace std;

void moveUp(Speedway* pista, Car *carro){

    //A VERIFICAÇÃO DE COLISÃO COM AS PAREDES TEM Q SER FEITA QUANDO OC ARRO ESTIVER DANDO RÉ TAMBÉM!!

    //down
    if(carro->coordinates.y - carro->speed * cos(degreesToRadians(carro->angle)) >= (3584 - carro->destino.h)) return;

    //up -> DANDO ERRADO
    //if(carro->coordinates.y - carro->speed * cos(degreesToRadians(carro->angle)) <= (0 - carro->destino.h)) return;

    //right
    if(carro->coordinates.x - carro->speed * sin(degreesToRadians(carro->angle)) >= (3584 - carro->destino.w)) return;

    //left ->DANDO ERRADO
    //if(carro->coordinates.x - carro->speed * sin(degreesToRadians(carro->angle)) <= (0 + carro->destino.w)) return;

    //o parametro carro nao precisa ser um ponteiro nessa função!!
    pista->destino.y += carro->speed * cos(degreesToRadians(carro->angle));
    pista->destino.x += carro->speed * sin(degreesToRadians(carro->angle));

    updateCarCoordinates(carro, "UP");

    cout << carro->coordinates.x << ", " << carro->coordinates.y << endl;

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
    if(carro->speed == 0) return;
    carro->angle += 2;
};

void turnRight(Car* carro){
     if(carro->speed == 0) return;
     carro->angle -= 2;
};


void desacelerate(Car* carro){
    if (carro->speed < 0){
        carro->speed = 0;
        return;
    }

        if (carro->speed > 0)
        {
            carro->speed -= 0.00125;
        }

}



void accelerate(Car* carro){
    if(carro->speed >= carro->max_speed){
        carro->speed = carro->max_speed;
        return;
    }

   carro->speed += carro->acceleration*5;
};


void handleCarDirections(Car* carro, Speedway* pista){
    if(carro->direction.up){
        //accelerate(carro);
        moveUp(pista, carro);
    };

    if(carro->direction.left) turnLeft(carro);

    if(carro->direction.right) turnRight(carro);


   if(carro->direction.down){
        moveDown(pista, carro);
    }


    //desacelerate(carro);
    //moveUp(pista, carro);

}
