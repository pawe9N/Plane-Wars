#include "../headers/HighScore.h"

std::string HighScore::getHighScoreString()
{
    return highScore;
}

int HighScore::getHighScoreInt()
{
    return atoi(highScore.c_str());
}

void HighScore::setHighScoreInFile(int score)
{
    highScore = std::to_string(score);
    file.open("highscore.txt", std::ios::out | std::ios::trunc);
    file<<highScore;
}
