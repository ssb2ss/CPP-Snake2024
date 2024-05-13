#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "Snake.h"

class GameScene
{    
    int width, height;
    int** map;
    bool isGameOver;

    WINDOW* gamescr;

    Snake* snake;
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
};

#endif