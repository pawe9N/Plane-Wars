#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED
#include <iostream>
#include <string>
#include <windows.h> //take handler of console
#include "User.h"
#include "Shapes.h"
#include "Enemy.h"

class Screen
{
public:
    void showScreen();

protected:
    int width;
    int numberOFfields;
    std::string fields;
    Shapes shapes;

    virtual void updateScreen() = 0;
    void addToScreen(std::string Sth, int numberOFRows, int x, int y);
    void showTitle();
    void clearingScreen();
};

#endif // SCREEN_H_INCLUDED
