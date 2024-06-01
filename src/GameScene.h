#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include <ncurses.h>
#include <string>
#include <fstream>
#include "Snake.h"
#include "Utilities.h"

class GameScene {
private:
    int width, height;
    int** map;
    WINDOW* gamescr;
    Snake* snake;
    bool isGameOver;

    void InitScreen();
    void InitMap();
    void CheckCollide();

public:
    GameScene();
    ~GameScene();
    void Update();
    void Draw();
    bool IsGameOver();
    void SaveMap(const std::string& filename);
    void LoadMap(const std::string& filename);
};

#endif
