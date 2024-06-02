#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Item.h"
#include "InputManager.h"
#include "GameScene.h"

GameScene::GameScene()
{
    isGameOver = false;

    InitMap();
    InitScreen();

    snake = new Snake(width / 2, height / 2, 3);

    srand(time(0));
    lastItemTime = std::chrono::steady_clock::now(); // 마지막 아이템 생성 시간 초기화
}

GameScene::~GameScene()
{
    for (int i = 0; i < height; i++)
    {
        delete[] map[i];
    }
    delete[] map;

    delwin(gamescr);

    delete snake;
}

void GameScene::Update()
{
    snake->Update();
    CheckCollide();
    GenerateRandomItem(); // 새로운 아이템 생성
    CheckItemCollision(); // 뱀이 아이템과 충돌했는지 검사
}

void GameScene::Draw()
{
    gamescr = newwin(height, width * 2, 2, 4);
    refresh();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == 1 || map[i][j] == 2) // Wall
            {
                mvwprintw(gamescr, i, j * 2, "##");
            }
        }
    }

    for (auto& item : items)
    {
        if (item.type == ITEM_GROW)
            mvwprintw(gamescr, item.position.y, item.position.x * 2, "+");
        else if (item.type == ITEM_SHRINK)
            mvwprintw(gamescr, item.position.y, item.position.x * 2, "-");
        else if (item.type == ITEM_SPEED_UP)
            mvwprintw(gamescr, item.position.y, item.position.x * 2, "U"); // Speed Up 아이템 표시
        else if (item.type == ITEM_SPEED_DOWN)
            mvwprintw(gamescr, item.position.y, item.position.x * 2, "D"); // Speed Down 아이템 표시
    }

    snake->Draw(gamescr);
    wrefresh(gamescr);
}

void GameScene::InitScreen()
{
    start_color();

    init_pair(COLOR_BACKGROUND, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_GAME_BACKGROUND, COLOR_BLACK, COLOR_BLUE);
    init_pair(COLOR_SNAKE, COLOR_GREEN, COLOR_YELLOW);
}

void GameScene::InitMap()
{
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

void GameScene::CheckCollide()
{
    if (snake->IsCollidedSelf())
    {
        isGameOver = true;
        return;
    }
    Vector2 p = snake->GetPosition();
    if (map[p.y][p.x] == 1 || map[p.y][p.x] == 2)
    {
        isGameOver = true;
        return;
    }

    // 뱀의 길이가 3보다 작아지면 게임 오버 처리
    if (snake->GetTailSize() < 3)
    {
        isGameOver = true;
        return;
    }
}

bool GameScene::IsGameOver()
{
    return isGameOver;
}

void GameScene::GenerateRandomItem()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> seconds = now - lastItemTime;

    if (seconds.count() >= 3.0) // 3초마다 아이템 생성
    {
        int x = rand() % width;
        int y = rand() % height;

        if (map[y][x] == 0)
        {
            ItemType type;
            int itemType = rand() % 4; // 0부터 3까지의 랜덤한 숫자 생성

            switch (itemType)
            {
                case 0:
                    type = ITEM_GROW; // 뱀의 길이가 늘어나는 아이템
                    break;
                case 1:
                    type = ITEM_SHRINK; // 뱀의 길이가 줄어드는 아이템
                    break;
                case 2:
                    type = ITEM_SPEED_UP; // 빠르게 이동하는 아이템
                    break;
                case 3:
                    type = ITEM_SPEED_DOWN; // 느리게 이동하는 아이템
                    break;
                default:
                    break;
            }

            // 아이템 생성 및 맵에 표시
            items.push_back(Item(Vector2(x, y), type));
            map[y][x] = 3; // 아이템을 나타내는 값으로 맵 업데이트
        }

        lastItemTime = now; // 마지막 아이템 생성 시간 업데이트
    }
}

void GameScene::CheckItemCollision()
{
    Vector2 p = snake->GetPosition();
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        if (p == it->position)
        {
            if (it->type == ITEM_GROW)
                snake->SetTailSize(snake->GetTailSize() + 1);
            else if (it->type == ITEM_SHRINK)
                snake->SetTailSize(snake->GetTailSize() - 1);
            else if (it->type == ITEM_SPEED_UP)
                snake->IncreaseSpeed();
            else if (it->type == ITEM_SPEED_DOWN)
                snake->DecreaseSpeed();
            
            items.erase(it);
            break;
        }
    }
}
