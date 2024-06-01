#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#define DEFAULT_DELAY 500

enum Color
{
    COLOR_BACKGROUND = 1,
    COLOR_GAME_BACKGROUND,
    COLOR_SNAKE
};

struct Vector2
{
    int x, y;
    Vector2() : x(0), y(0) {}
    Vector2(int x, int y) : x(x), y(y) {}
    Vector2 operator+(const Vector2 p)
    {
        Vector2 result;
        result.x = x + p.x;
        result.y = y + p.y;
        return result;
    }
    bool operator==(const Vector2 p)
    {
        return (x == p.x) && (y == p.y);
    }
};


#endif