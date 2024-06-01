#include "Snake.h"
#include "InputManager.h"

Snake::Snake(int x, int y, int length)
{
    position = Vector2(x, y);
    speed = Vector2(-1, 0);

    //TODO: tails' position from map
    for (int i = 0; i < length; i++)
    {
        tails.push_back(Vector2(x + i, y));
    }
}

void Snake::Update()
{
    int key = InputManager::GetInstance().GetPressedKey();
    //printw("%d", key);
    switch (key)
    {
        case 258: // Key Down
            speed = Vector2(0, 1);
            break;
        case 259: // Key Up
            speed = Vector2(0, -1);
            break;
        case 260: // Key Left
            speed = Vector2(-1, 0);
            break;
        case 261: // Key Right
            speed = Vector2(1, 0);
            break;
    }

    // 머리의 이전 위치를 저장
    Vector2 previousPosition = position;
    // 변경된 속도를 사용하여 머리의 위치를 업데이트
    position = position + speed;

    // 머리 이후의 꼬리들을 이전 꼬리의 위치를 따라 이동
    for (int i = tails.size() - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            tails[i] = previousPosition;
        }
        else
        {
            tails[i] = tails[i - 1];
        }
    }
    //printw("%d %d, %d %d", tails[0].x, tails[0].y, tails[1].x, tails[1].y);
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


Vector2 Snake::GetPosition()
{
    return position;
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
    return false;
}
void Snake::IncreaseSpeed()
{
    // 현재 속도의 크기를 2 증가시킴
    speed.x += 2;
    speed.y += 2;
}

void Snake::DecreaseSpeed()
{
    // 현재 속도의 크기를 2 감소시킴
    speed.x -= 2;
    speed.y -= 2;
}