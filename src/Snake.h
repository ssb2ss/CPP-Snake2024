#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <ncurses.h>
#include <vector>

#include "Utilities.h"

class Snake
{
    Position position;
    Position speed;

    std::vector<Position> tails;
public:
    Snake(int x, int y, int length);
    void Update();
    void Draw(WINDOW* curscr);
    
    Position GetPosition();
    int GetTailSize();
    void SetTailSize(int length);
    bool IsCollidedSelf();
};

#endif