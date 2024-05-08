#include "Snake.h"

Snake::Snake(int x, int y, int length)
    :length(length)
{
    position.x = x;
    position.y = y;
    speed.x = -1;
    speed.y = 0;
}