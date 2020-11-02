#ifndef SPEED_H
#define SPEED_H

#include <string>

float speed(float speed, float max_speed, float acceleration, std::string direction){


    if(speed <= max_speed)
    {
        if(direction == "UP")
        {
            speed += acceleration;
        }
        if (direction == "RIGHT" || direction == "LEFT" )
        {
            //Parte Incompleta
        }
        if (direction == "DOWN")
        {
            speed -= 5;
        }
        if (direction == "NULL")
        {
            if (speed > 0)
            {
                speed -= 0.00025;
            }
            if (speed < 0)
            {
                speed = 0;
            }
        }

    } else
    {
        speed = max_speed;
    }

    return speed;
}

#endif // SPEED_H
