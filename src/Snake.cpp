#include "Snake.h"
#include "InputManager.h"

#include <cmath>

Snake::Snake(int x, int y, int length)
{
    position = Vector2(x, y);
    direction = Vector2(-1, 0);
    speed = 1;

    // TODO: tails' position from map
    for (int i = 1; i <= length; i++)
    {
        tails.push_back(Vector2(x + i, y));
    }
}

void Snake::Update()
{
    int key = InputManager::GetInstance().GetPressedKey();
    // printw("%d", key);
    switch (key)
    {
        case 258: // Key Down
            direction = Vector2(0, 1);
            break;
        case 259: // Key Up
            direction = Vector2(0, -1);
            break;
        case 260: // Key Left
            direction = Vector2(-1, 0);
            break;
        case 261: // Key Right
            direction = Vector2(1, 0);
            break;
    }
    InputManager::GetInstance().pressedKey = 0;

    for (int i = tails.size() - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            tails[i] = position;
        }
        else
        {
            tails[i] = tails[i - 1];
        }
    }
    // printw("%d %d, %d %d", tails[0].x, tails[0].y, tails[1].x, tails[1].y);
    position = position + direction;
    // printw("%d %d, %d %d", tails[0].x, tails[0].y, tails[1].x, tails[1].y);
}

void Snake::Draw(WINDOW *curscr)
{
    wattron(curscr, COLOR_PAIR(COLOR_SNAKE_HEAD));
    mvwprintw(curscr, position.y, position.x * 2, "  ");
    wattroff(curscr, COLOR_PAIR(COLOR_SNAKE_HEAD));
    wattron(curscr, COLOR_PAIR(COLOR_SNAKE_TAIL));
    for (int i = 0; i < tails.size(); i++)
    {
        mvwprintw(curscr, tails[i].y, tails[i].x * 2, "  ");
    }
    wattroff(curscr, COLOR_PAIR(COLOR_SNAKE_TAIL));
}

void Snake::PushTail()
{
    Vector2 tmp;
    tmp.x = tails.back().x;
    tmp.y = tails.back().y;
    tails.push_back(tmp);
}

void Snake::PopTail()
{
    tails.pop_back();
}

int Snake::GetTailSize()
{
    return tails.size();
}

void Snake::SetTailSize(int l)
{
    if (tails.size() == l)
    {
        return;
    }
    else if (tails.size() > l)
    {
        while (tails.size() > l)
        {
            PopTail();
        }
    }
    else if (tails.size() < l)
    {
        while (tails.size() < l)
        {
            PushTail();
        }
    }
}

bool Snake::IsCollidedSelf()
{
    for (int i = 0; i < tails.size(); i++)
    {
        if (position == tails[i])
        {
            return true;
        }
    }
    if (tails.size() < 3)
    {
        return true;
    }
    return false;
}

void Snake::IncreaseSpeed()
{
    // 현재 속도의 크기를 1 증가시킴
    speed += 1;
    if (speed > 10)
    {
        speed = 10;
    }
}

void Snake::DecreaseSpeed()
{
    // 현재 속도의 크기를 1 감소시킴
    speed -= 1;
    if (speed < 1)
    {
        speed = 1;
    }
}

int Snake::GetDelayFromSpeed()
{
    return int(DEFAULT_DELAY * pow(0.8, (speed - 1)));
}