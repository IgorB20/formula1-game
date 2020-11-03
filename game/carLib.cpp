#include <carLib.h>
#include <math.h>
#include <string>

void moveUp(Speedway* pista, Car *carro){
    //o parametro carro nao precisa ser um ponteiro nessa função!!
    pista->destino.y += carro->speed * cos(degreesToRadians(carro->angle));
    pista->destino.x += carro->speed * sin(degreesToRadians(carro->angle));
}

void turnLeft(Car* carro){
    if(carro->speed == 0) return;
    carro->angle += 3;
};

void turnRight(Car* carro){
     if(carro->speed == 0) return;
     carro->angle -= 3;
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
        accelerate(carro);
        moveUp(pista, carro);
    };

    if(carro->direction.left){
        turnLeft(carro);
        //carro.angle += 3;
    };
    if(carro->direction.right){
       turnRight(carro);
        //carro.angle -= 3;
    }


    desacelerate(carro);
    moveUp(pista, carro);

    /*if(carro.direction.down){
        pista.destino.y -= carro.speed * cos(degreesToRadians(carro.angle));
        pista.destino.x -= carro.speed * sin(degreesToRadians(carro.angle));
    }*/
}
