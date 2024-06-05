
#ifndef _GATE_H_
#define _GATE_H_

#include "Utilities.h"

#include <ncurses.h>

class Gate
{
    int **map;
    int width, height;
    Vector2 gatePos[2];

public:
    Gate(int **map, int width, int height);
    void Draw(WINDOW *curscr);

    Vector2 GetExitPosition(Vector2 enterPosition);
    Vector2 GetExitDirection(Vector2 enterPosition, Vector2 enterDirection);
    bool IsCollided(Vector2 position);

private:
    bool IsValid(int x, int y);
    bool IsValid(Vector2 position);
};

#endif
