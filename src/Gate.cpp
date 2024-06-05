#include <cstdlib>
#include <ctime>

#include "Gate.h"

Gate::Gate(int **map, int width, int height)
    : map(map), width(width), height(height)
{
    for (int i = 0; i < 2;)
    {
        int x = std::rand() % width;
        int y = std::rand() % height;

        if (map[y][x] == 1)
        {
            if (i == 1 && gatePos[0] == Vector2(x, y))
            {
                continue;
            }
            gatePos[i] = Vector2(x, y);
            i++;
        }
    }
    enterTimer = 0;
}

void Gate::Update()
{
    enterTimer++;
}

void Gate::Draw(WINDOW *curscr)
{
    for (int i = 0; i < 2; i++)
    {
        mvwprintw(curscr, gatePos[i].y, gatePos[i].x * 2, "[]");
    }
}

Vector2 Gate::GetExitPosition(Vector2 enterPosition)
{
    if (gatePos[0] == enterPosition)
    {
        return gatePos[1];
    }
    else
    {
        return gatePos[0];
    }
    enterTimer = 0;
}

Vector2 Gate::GetExitDirection(Vector2 enterPosition, Vector2 enterDirection)
{
    int idx = 0;

    if (gatePos[0] == enterPosition)
    {
        idx = 1;
    }
    else if (gatePos[1] == enterPosition)
    {
        idx = 0;
    }

    int x = gatePos[idx].x;
    int y = gatePos[idx].y;

    Vector2 result(1, 0);

    // When there is only one way out
    int cnt = 0;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++)
    {
        if (IsValid(x + dx[i], y + dy[i]))
        {
            cnt++;
            result = Vector2(dx[i], dy[i]);
        }
    }
    if (cnt == 1)
    {
        return result;
    }

    // When there are two ways out
    if (cnt == 2)
    {
        // When the ways out are the left and right
        if (IsValid(x - 1, y) && IsValid(x + 1, y))
        {
            // When entering from the left or right
            if (enterDirection.y == 0)
            {
                return enterDirection;
            }
            // When entering from the up
            else if (enterDirection.y > 0)
            {
                return Vector2(1, 0);
            }
            // When entering from the down
            else
            {
                return Vector2(-1, 0);
            }
        }
        // When the ways out are the up and right
        else if (IsValid(x, y - 1) && IsValid(x, y + 1))
        {
            // When entering from the up or down
            if (enterDirection.x == 0)
            {
                return enterDirection;
            }
            // When entering from the left
            else if (enterDirection.x > 0)
            {
                return Vector2(0, 1);
            }
            // When entering from the right
            else
            {
                return Vector2(0, -1);
            }
        }
        // When the same way as the way in is valid
        else if (IsValid(Vector2(x, y) + enterDirection))
        {
            return enterDirection;
        }
        // Otherwise: reverse
        else
        {
            result.x = -enterDirection.x;
            result.y = -enterDirection.y;
            return result;
        }
    }

    // When there are three ways out
    if (cnt == 3)
    {
        // When the same way as the way in is valid
        if (IsValid(Vector2(x, y) + enterDirection))
        {
            return enterDirection;
        }
        // Otherwise: reverse
        else
        {
            result.x = -enterDirection.x;
            result.y = -enterDirection.y;
            return result;
        }
    }

    // When all the ways are valid
    return enterDirection;
}

bool Gate::IsCollided(Vector2 position)
{
    return (position == gatePos[0] || position == gatePos[1]);
}

bool Gate::IsValid(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return false;
    }

    if (map[y][x] == 1 || map[y][x] == 2)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool Gate::IsValid(Vector2 position)
{
    int x = position.x;
    int y = position.y;
    return IsValid(Vector2(x, y));
}

bool Gate::IsRemovable(int snakeLength)
{
    return enterTimer > snakeLength;
}