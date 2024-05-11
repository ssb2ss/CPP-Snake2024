#include "Snake.h"

Snake::Snake(int x, int y, int length)
    :length(length)
{
    position = Position(x, y);
    speed = Position(-1, 0);

    //TODO: tails' position from map
    tails.push_back(Position(x + 1, y));
    tails.push_back(Position(x + 2, y));
}

void Snake::Update()
{
    for (int i = 0; i < tails.size(); i++)
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
    position += speed;
}

void Snake::Draw()
{

}


int Snake::GetTailSize()
{
    return tails.size();
}