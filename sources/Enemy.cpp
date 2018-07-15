#include "../headers/Enemy.h"

//make enemy's bullet spawn randomly in time
void Enemy::makeBullet()
{
    if(!(std::rand() % 70))
    {
        if(this->bullet == nullptr)
        {
            this->bullet = new Bullet(this->x+(this->width/2), this->y+this->height);
        }
    }
}

//make enemy's bullet moving
void Enemy::makeBulletMove()
{
    this->makeBullet();
    if(this->bullet != nullptr)
    {
        //if it is between upper and bottom side of console buffer
        if(this->bullet->y <= 49)
        {
            this->bullet->y += 1;
        }
        //if it is on bottom side of console buffer
        else if(this->bullet->y > 49)
        {
            delete this->bullet;
            this->bullet = nullptr;
        }
    }
}

//spawn enemy with randomly position and direction of moving
void Enemy::spawn(int screenWidth)
{
    this->x = std::rand() % (screenWidth-this->width);
    this->y = ( std::rand() % 3 ) + 4;
    this->direction = std::rand() % 2;
}
