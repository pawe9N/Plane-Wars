#include "headers/Shapes.h"
#include "headers/Bullet.h"
#include "headers/user.h"
#include "headers/Enemy.h"
#include "headers/Screen.h"
#include "headers/Game.h"
#include <ctime> //time( NULL )

int main(int argc, char *argv[])
{
    Game game(10036, 193);
    //while user won't click ESC
    while(game.pressedKey != KEY_ESCAPE)
    {
        //set the starting point for rand
        srand( time( NULL ) );
        game.resetObjects();

        //if user click ENTER
        if(game.gameStarted)
        {
            game.updateScreen(); //setting score
            game.showScreen();
        }

        Plane* activePlane = nullptr;

        //game logic
        while(game.gameStarted) //if user click ENTER
        {
            activePlane = &game.user;
            activePlane->makeBulletMove();
            game.checkBulletInEnemy();

            if(game.checkBulletInUser())
            {
                game.updateScreen();
                game.showScreen();
                break;
            }

            activePlane = &game.enemy;
            activePlane->makeBulletMove();

            if(game.checkEnemyAndUserCollision())
            {
                game.updateScreen();
                game.showScreen();
                break;
            }

            game.getEventsFromKeyboard();
            game.updateScreen();

            if(!game.movingEnemy())
            {
                break;
            }

            game.showScreen();

            Sleep(20);
            game.cls();
        }

        //if user lose the game
        if(game.gameOver == true)
        {
            //deleting user.bullet if exist
            if(game.user.bullet != nullptr)
            {
                delete game.user.bullet;
                game.user.bullet = nullptr;
            }

            game.showScreen();
            Sleep(500);
            if(game.score > game.hScore.getHighScoreInt())
            {
                game.hScore.setHighScoreInFile(game.score);
            }
            game.showGameOver();
        }
    };

    return 0;
}


