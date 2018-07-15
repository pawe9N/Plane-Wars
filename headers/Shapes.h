#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED
#include <string>
#include <fstream> //ifstream

class Shapes
{
public:
    std::string planeShape;
    std::string enemyShape;
    std::string bulletShape;
    std::string title;
    std::string gameOver;
    std::string frame;

    Shapes()
    {
        std::ifstream  Reader(".\\shapes\\plane.txt");
        this->planeShape = getFileContents(Reader);
        Reader.close();

        Reader.open(".\\shapes\\enemy.txt");
        this->enemyShape = getFileContents(Reader);
        Reader.close();

        this->bulletShape = "O";

        Reader.open(".\\shapes\\title.txt");
        title = getFileContents(Reader);
        Reader.close();

        Reader.open(".\\shapes\\gameOver.txt");
        gameOver = getFileContents(Reader);
        Reader.close();

        Reader.open(".\\shapes\\frame.txt");
        frame = getFileContents(Reader);
        Reader.close();
    }

private:
    std::string getFileContents (std::ifstream&);
};

#endif // SHAPES_H_INCLUDED
