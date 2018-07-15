#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include <cstdlib> //rand
#include "Plane.h"
#include "Bullet.h"

class Enemy: public Plane
{
public:
    double speed;
    int direction;

    Enemy() : Plane(30, 8), speed(0.5)
    {}

    void makeBulletMove();
    void spawn(int screenWidth);

private:
    void makeBullet();
};

#endif // ENEMY_H_INCLUDED
