#include "../headers/User.h"

//make bullet move
void User::makeBulletMove()
{
    if(this->bullet != nullptr)
    {
        //if it is between upper and bottom side of console buffer
        if(this->bullet->y > 1)
        {
            this->bullet->y -= 2;
        }
        //if it is on top side of console buffer
        else if(this->bullet->y < 1.5)
        {
            delete this->bullet;
            this->bullet = nullptr;
        }

    }
}
