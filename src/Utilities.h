#ifndef _UTILITIES_H_
#define _UTILITIES_H_

enum Color
{
    COLOR_BACKGROUND = 1,
    COLOR_GAME_BACKGROUND,
    COLOR_SNAKE
};

struct Position
{
    int x, y;
    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}
    Position operator+(const Position p)
    {
        Position result;
        result.x = x + p.x;
        result.y = y + p.y;
        return result;
    }
    bool operator==(const Position p)
    {
        return (x == p.x) && (y == p.y);
    }
};

#endif