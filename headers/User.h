#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include "Plane.h"

class User: public Plane
{
public:

    virtual void makeBulletMove();

    User(): Plane(37, 12)
    {}
};

#endif // USER_H_INCLUDED
