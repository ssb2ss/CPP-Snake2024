#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <ncurses.h>
#include <vector>

#include "Utilities.h"

class Snake
{
    Vector2 position;
    Vector2 direction;
    int speed;
    std::vector<Vector2> tails;

public:
    Snake(int x, int y, int length);
    void Update();
    void Draw(WINDOW *curscr);

    Vector2 GetPosition() { return position; }
    void SetPosition(Vector2 position) { this->position = position; }
    Vector2 GetDirection() { return direction; }
    void SetDirection(Vector2 direction) { this->direction = direction; }

    void PushTail();
    void PopTail();
    int GetTailSize();
    void SetTailSize(int length);
    bool IsCollidedSelf();
    void IncreaseSpeed();
    void DecreaseSpeed();
};

#endif