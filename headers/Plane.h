#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED
#include "Bullet.h"

class Plane
{
public:
    double x;
    double y;
    int width;
    int height;
    Bullet *bullet;

    virtual void makeBulletMove() = 0;

    Plane(int width, int height): width(width), height(height), bullet(nullptr)
    {}

    ~Plane()
    {
        if(this->bullet != nullptr)
        {
            delete this->bullet;
            this->bullet = nullptr;
        }
    }
};

#endif // PLANE_H_INCLUDED
