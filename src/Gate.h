
#ifndef _GATE_H_
#define _GATE_H_

#include "Utilities.h"

#include <ncurses.h>

class Gate
{
    int **map;
    int width, height;
    Vector2 gatePos[2];
    int enterTimer;     // count time after the snake enters

public:
    Gate(int **map, int width, int height);
    void Update();
    void Draw(WINDOW *curscr);

    Vector2 GetExitPosition(Vector2 enterPosition);
    Vector2 GetExitDirection(Vector2 enterPosition, Vector2 enterDirection);
    bool IsCollided(Vector2 position);
    bool IsRemovable(int snakeLength);

private:
    bool IsValid(int x, int y);
    bool IsValid(Vector2 position);
};

#endif
