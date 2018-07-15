#include "../headers/Game.h"

//update screen with shapes
void Game::updateScreen()
{
    //make screen clear
    this->clearingScreen();
    //add shapes of objects
    this->addToScreen(this->shapes.planeShape, user.height, user.x, user.y);
    this->addToScreen(this->shapes.enemyShape, enemy.height, enemy.x, enemy.y);
    //add score, title and how to exit message
    this->addToScreen(std::to_string(score), 1, 1, 1);
    this->addToScreen("Plane Wars", 1, 87, 1);
    this->addToScreen("Click ESC to exit program!", 1, 165, 1);

    //show user's bullet
    if(user.bullet != nullptr)
    {
        this->addToScreen(this->shapes.bulletShape, 1, user.bullet->x, user.bullet->y);
    }

    //show enemy's bullet
    if(enemy.bullet != nullptr)
    {
        this->addToScreen(this->shapes.bulletShape, 1, enemy.bullet->x, enemy.bullet->y);
    }
}

//reset objects
void Game::resetObjects()
{
    //initial values
    gameOver = false;
    score = 0;
    difficulty = 1;
    pressedKey = getch();
    gameStarted = (pressedKey == KEY_ENTER);

    //setting user positions
    user.x = 75;
    user.y = 36;

    //setting initial enemy value for speed and spawn Enemy shape on screen
    enemy.speed = 0.5;
    enemy.spawn(width);
}

//make console cursor go to top left corner
void Game::cls()
{
   HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //take handle of console
   COORD topLeft = {0, 0}; //top left coords
   std::cout.flush(); //flush console buffer
   SetConsoleCursorPosition(hOut, topLeft);
}

//make game fullscreen and set the buffer
void Game::fullscreen()
{
    //VK_MENU is ALT
    //VK_RETURN is ENTER
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);

    //make fullscreen
    system("MODE CON COLS=192 LINES=54");

    //make console cursor invisible
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //get handler
    CONSOLE_CURSOR_INFO  cursorInfo; //make cursor variable
    GetConsoleCursorInfo(hOut, &cursorInfo); //get cursor with visibility
    cursorInfo.bVisible = false; //make cursor invisible
    SetConsoleCursorInfo(hOut, &cursorInfo); //set cursor without visibility

}

//check if user's bullet is in enemy
void Game::checkBulletInEnemy()
{
    if(user.bullet != nullptr)
    {
        if(user.bullet->y+5 <= enemy.y+enemy.height &&
            user.bullet->y+5 >= enemy.y &&
            user.bullet->x >= enemy.x &&
            user.bullet->x <=enemy.x + enemy.width)
        {
            delete user.bullet;
            user.bullet = nullptr;
            delete enemy.bullet;
            enemy.bullet = nullptr;

            //if user obtain certain score, make game harder
            if(!(score % 50*difficulty))
            {
                enemy.speed += 0.3; //make next enemy faster
                difficulty *= 2; //increase difficulty
            }
            //spawn new enemy
            enemy.spawn(width);

            //increase score
            score+=10;

            Sleep(500);
        }
    }
}

//check if enemy's bullet is in user
bool Game::checkBulletInUser()
{
    if(enemy.bullet != nullptr)
    {
        if(enemy.bullet->y <= user.y+6 &&
            enemy.bullet->y >= user.y+3 &&
            enemy.bullet->x >= user.x &&
            enemy.bullet->x <=user.x + user.width)
        {
            delete enemy.bullet;
            enemy.bullet = nullptr;

            //if yes, user will lose
            this->gameOver = true;
            return true;
        }
    }
    return false;
}

//take events from keyboard
void Game::getEventsFromKeyboard()
{
    this->pressedKey = 0;
    if (kbhit()) //check keyboard buffer
    {
        this->pressedKey = getch(); //take key from keyboard
        switch(this->pressedKey) {
            case KEY_UP:
                if(user.y > 3)
                {
                    user.y--;
                }
                break;
            case KEY_DOWN:
                if(user.y < numberOFfields/width-user.height-1)
                {
                    user.y++;
                }
                break;
            case KEY_LEFT:
                if(user.x >= 4)
                {
                    user.x-=4;
                }
                break;
            case KEY_RIGHT:
                if(user.x <= width-user.width-4)
                {
                    user.x+=4;
                }
                break;
            case KEY_ESCAPE: //if escape -> exit game
                {
                    this->gameStarted = false;
                }
                break;
            case KEY_SPACE: //if space -> make bullet
                if(user.bullet == nullptr)
                {
                    user.bullet = new Bullet(user.x+(user.width/2+1),user.y);
                }
                break;
        }
    }
}

//moving enemy logic
bool Game::movingEnemy()
{
    //if it is between left side and right side of buffer
    if(enemy.x <= (width-enemy.width) && enemy.x > 1*enemy.speed+1)
    {
        //make horizontal moving
        if(enemy.direction == 1) //if enemy direction is 1 it will go only to right
        {
           enemy.x += 0.5*enemy.speed;
        }
        else //if enemy direction is 0 it will go only to left
        {
           enemy.x -= 0.5*enemy.speed;
        }

        //if it is between upper side and bottom side of buffer
        if(enemy.y < (numberOFfields/width)-enemy.height)
        {
            enemy.y += 0.1*enemy.speed;
        }
        else
        {
            //if enemy is in bottom of buffer, user lose
            gameOver = true;
            return false;
        }
    }
    //if it will go too close
    else if(enemy.x <= 1*enemy.speed+1)
    {
        enemy.x = (width-enemy.width);
    }
    //if it will go too far
    else
    {
        enemy.x = 1*enemy.speed+1.1;
    }
    return true;
}

//if user and enemy have collisions then game over
bool Game::checkEnemyAndUserCollision()
{
    if((enemy.x <= user.x && enemy.x+20 >= user.x && enemy.y <= user.y && enemy.y+4 >= user.y) ||
      (enemy.x >= user.x && enemy.x <= user.x+user.width && enemy.y <= user.y && enemy.y+4 >= user.y))
    {
        gameOver = true;
        return true;
    }

    return false;
}

//show game over screen
void Game::showGameOver()
{
    std::string sscore;

    this->clearingScreen();
    std::cout<<"\n\n\n";
    this->addToScreen("Game Over!!! Click Enter to Continue!", 1, 78, 1);
    this->addToScreen(this->shapes.gameOver, 18, 62, 10);
    this->addToScreen(this->shapes.frame, 16, 60, 32);
    sscore += "Score: " + std::to_string(score);
    this->addToScreen(sscore, 1, 92, 39);
    sscore = "HighScore: " + hScore.getHighScoreString();
    this->addToScreen(sscore, 1, 92-hScore.getHighScoreString().length(), 41);

    //take console handler
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    this->cls();

    //set console color 12 - lightred
    SetConsoleTextAttribute(hConsole, 12);
    std::cout<<this->fields.substr(0, width*30);
    //set console color 10 - lighgreen
    SetConsoleTextAttribute(hConsole, 10);
    std::cout<<this->fields.substr(width*30)<<"\n";
}
