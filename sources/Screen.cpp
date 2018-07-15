#include "../headers/Screen.h"

//make console screen clear
void Screen::clearingScreen()
{
    int czyMenu = 0;
    for(int i=0; i<this->numberOFfields; i++)
    {
        if(!((i+1)%this->width))
        {
            this->fields[i] = '\n';
            czyMenu++;
        }
        else if(czyMenu>2 || czyMenu == 1)
            this->fields[i] = ' ';
        else
            this->fields[i] = '#';
    }
}

void Screen::showScreen()
{
    //take console handler
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //set console color 13 - pink
    SetConsoleTextAttribute(hConsole, 13);
    std::cout<<this->fields.substr(0, width*3);
    //set console color 15 - white foreground
    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<this->fields.substr(width*3, width*51);
    SetConsoleTextAttribute(hConsole, 1);
}

//add shape to screen
void Screen::addToScreen(std::string Sth, int numberOFRows, int x, int y)
{
    for(int i=0, j=y; i<numberOFRows; i++, j++)
    {
        this->fields.replace(j*this->width+x, Sth.length()/numberOFRows, Sth.substr(i*(Sth.length()/numberOFRows),Sth.length()/numberOFRows));
    }
}

//show title screen
void Screen::showTitle()
{
    this->addToScreen(this->shapes.title, 24, 38, 10);

    //take console handler
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //set console color 1 - lightcyan
    SetConsoleTextAttribute(hConsole, 11);
    std::cout<<this->fields;
}
