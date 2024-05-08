#ifndef GAME_SCENE
#define GAME_SCENE

#include "Snake.h"

class GameScene
{
    int width, height;
    int** map;
    Snake* snake;
public:
    GameScene();
    ~GameScene();
    void Update();
    void Draw();
};

#endif