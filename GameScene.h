#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "Snake.h"
#include "Item.h"
#include <vector>
#include <chrono>

class GameScene
{    
    int width, height;
    int** map;
    bool isGameOver;

    WINDOW* gamescr;

    Snake* snake;
    std::vector<Item> items;
    std::chrono::time_point<std::chrono::steady_clock> lastItemTime; // 마지막 아이템 생성 시간
public:
    GameScene();
    ~GameScene();
    void Update();
    void Draw();

    void CheckCollide();
    bool IsGameOver();

private:
    void InitScreen();
    void InitMap();
    void GenerateRandomItem();
    void CheckItemCollision();
};

#endif