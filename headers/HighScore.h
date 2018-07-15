#ifndef HIGHSCORE_H_INCLUDED
#define HIGHSCORE_H_INCLUDED
#include <fstream> //for getting best score from text

class HighScore
{
    std::string highScore;
    std::fstream file;

public:
    HighScore()
    {
        file.open("highscore.txt", std::ios::in);
        if(file.peek() == std::fstream::traits_type::eof())
        {
            highScore = "0";
        }
        else
        {
            file>>highScore;
        }
        file.close();
    }

    ~HighScore()
    {
        file.close();
    }

    std::string getHighScoreString();
    int getHighScoreInt();
    void setHighScoreInFile(int);
};

#endif // HIGHSCORE_H_INCLUDED
