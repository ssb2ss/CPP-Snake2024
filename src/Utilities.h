#ifndef UTILITIES
#define UTILITIES

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
    Position operator=(const Position p)
    {
        return Position(p.x, p.y);
    }
    Position operator+(const Position p)
    {
        return Position(x + p.x, y + p.y);
    }
    Position operator+=(const Position p)
    {
        return Position(x + p.x, y + p.y);
    }
};

#endif