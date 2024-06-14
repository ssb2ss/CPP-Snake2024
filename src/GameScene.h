#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include <vector>
#include <chrono>
#include <fstream>
#include "Snake.h"
#include "Item.h"
#include "Gate.h"
#include "Box.h"

class GameScene
{
    int width, height;
    int **map;
    bool isGameOver;

    WINDOW *gamescr;
    Gate *gate;
    Snake *snake;
    Box *t_box; // make instance for box
    std::vector<Item> items;

    WINDOW *ScoreBox; // make new WINDOW for Two Boxes.
    WINDOW *MissionBOX;

    std::chrono::time_point<std::chrono::steady_clock> lastItemTime; // 마지막 아이템 생성 시간
    std::chrono::time_point<std::chrono::steady_clock> starttime;    // for the Play time in Score Box
    int gateTimer;

    bool passingGate;
    int getItem;
    int currentStage;

public:
    GameScene(int currentStage);
    ~GameScene();
    void Update();
    void Draw();

    void CheckCollide();
    bool IsGameOver();
    void Making_box();       // Make the box
    void Updating_Box();     // Updating the Boxes cause of the Changed Score and Mission check list
    void Updating_Score();   // Updating Score dynamically
    void Checking_Mission(); // Checking "V" the Mission
    bool Stage_pass();       // if stage pass make new box on the game window
    void SaveMap(const std::string& filename);
    void LoadMap(const std::string& filename);
    int GetDelay();

private:
    void InitScreen();
    void InitMap();
    void GenerateRandomItem();
    void CheckItemCollision();
    void UpdateGate();
};

#endif