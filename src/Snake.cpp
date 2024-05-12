#include "Snake.h"
#include "InputManager.h"

Snake::Snake(int x, int y, int length)
{
    position = Position(x, y);
    speed = Position(-1, 0);

    //TODO: tails' position from map
    for (int i = 1; i < length; i++)
    {
        tails.push_back(Position(x + i, y));
    }
}

void Snake::Update()
{
    int key = InputManager::GetInstance().GetPressedKey();
    //printw("%d", key);
    switch (key)
    {
        case 258: // Key Down
            speed = Position(0, 1);
            break;
        case 259: // Key Up
            speed = Position(0, -1);
            break;
        case 260: // Key Left
            speed = Position(-1, 0);
            break;
        case 261: // Key Right
            speed = Position(1, 0);
            break;
    }

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
    //printw("%d %d, %d %d", tails[0].x, tails[0].y, tails[1].x, tails[1].y);
    position = position + speed;
}

void Snake::Draw(WINDOW* curscr)
{
    attron(COLOR_PAIR(COLOR_SNAKE));
    mvwprintw(curscr, position.y, position.x * 2, "O");
    for (int i = 0; i < tails.size(); i++)
    {
        mvwprintw(curscr, tails[i].y, tails[i].x * 2, "X");
    }
    attroff(COLOR_PAIR(COLOR_SNAKE));
}


Position Snake::GetPosition()
{
    return position;
}

int Snake::GetTailSize()
{
    return tails.size();
}

void Snake::SetTailSize(int l)
{
    l--;
    if (tails.size() == l)
    {
        return;
    }
    else if (tails.size() > l)
    {
        while (tails.size() > l)
        {
            tails.pop_back();
        }
    }
    else if (tails.size() < l)
    {
        while (tails.size() < l)
        {
            Position tmp;
            tmp.x = tails.back().x;
            tmp.y = tails.back().y;
            tails.push_back(tmp);
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
    return false;
}