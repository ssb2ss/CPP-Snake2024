#ifndef SNAKE
#define SNAKE

#include "Utilities.h"

class Snake
{
    Position position;
    int length;
    Position speed;
public:
    Snake(int x, int y, int length);
    void Update();
    void Draw();
};

#endif