#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <string>
#include <conio.h>//getch, kbhit
#include "Screen.h"
#include "HighScore.h"


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32
#define KEY_ESCAPE 27
#define KEY_ENTER 13

class Game : public Screen
{
public:
    char pressedKey;
    bool gameStarted;
    bool gameOver;
    int score;
    int difficulty;
    std::string scoreText;

    User user;
    Enemy enemy;
    HighScore hScore;

    Game(int numberOFfields, int width) : score(0), difficulty(1), scoreText("Score: ")
    {
        this->numberOFfields = numberOFfields;
        this->width = width;

        for(int i=0; i<numberOFfields; i++)
        {
            if(!(i%width))
                fields += '\n';
            else
                fields += ' ';
        }
        fullscreen();
        std::ios::sync_with_stdio(false); //make no synchronization with stream

        showTitle();
    }

    virtual void updateScreen();
    void resetObjects();
    void cls();
    void fullscreen();
    void checkBulletInEnemy();
    bool checkBulletInUser();
    void getEventsFromKeyboard();
    bool movingEnemy();
    bool checkEnemyAndUserCollision();
    void showGameOver();
};

#endif // GAME_H_INCLUDED
