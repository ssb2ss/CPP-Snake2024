#ifndef SNAKE
#define SNAKE

#include <vector>

#include "Utilities.h"

class Snake
{
    Position position;
    Position speed;
    int length;

    std::vector<Position> tails;
public:
    Snake(int x, int y, int length);
    void Update();
    void Draw();
    
    int GetTailSize();
};

#endif