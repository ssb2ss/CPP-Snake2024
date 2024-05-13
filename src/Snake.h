#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <ncurses.h>
#include <vector>

#include "Utilities.h"

class Snake
{
    Vector2 position;
    Vector2 speed;

    std::vector<Vector2> tails;
public:
    Snake(int x, int y, int length);
    void Update();
    void Draw(WINDOW* curscr);
    
    Vector2 GetPosition();
    int GetTailSize();
    void SetTailSize(int length);
    bool IsCollidedSelf();
};

#endif