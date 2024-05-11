#include <ncurses.h>

#include "InputManager.h"
#include "GameScene.h"

GameScene::GameScene()
{
    InitMap();
    InitColor();

    snake = new Snake(width / 2, height / 2, 3);
}

GameScene::~GameScene()
{
    for (int i = 0; i < height; i++)
    {
        delete[] map[i];
    }
    delete[] map;

    delete snake;
}

void GameScene::Update()
{
    snake->Update();
}

void GameScene::Draw()
{
    //TODO: Draw Screen

    refresh();
}


void GameScene::InitMap()
{
    //TODO: Add Flexibility on Map system
    width = 21;
    height = 21;
    map = new int*[height];
    for (int i = 0; i < height; i++)
    {
        map[i] = new int[width];
        for (int j = 0; j < width; j++)
        {
            if ((i == 0 && j == 0) ||
                (i == 0 && j == width - 1) ||
                (i == height - 1 && j == 0) ||
                (i == height - 1 && j == width - 1))
            {
                map[i][j] = 2;
            }
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                map[i][j] = 1;
            }
            else
            {
                map[i][j] = 0;
            }
        }
    }
}

void GameScene::InitColor()
{
    start_color();

    init_pair(COLOR_BACKGROUND, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_GAME_BACKGROUND, COLOR_BLACK, COLOR_BLUE);
    init_pair(COLOR_SNAKE, COLOR_GREEN, COLOR_YELLOW);
}