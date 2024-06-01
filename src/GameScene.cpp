#include "GameScene.h"

GameScene::GameScene() {
    InitScreen();
    InitMap();
    snake = new Snake(10, 10, 3); // Initial snake position and length
    isGameOver = false;
}

GameScene::~GameScene() {
    for (int i = 0; i < height; i++) {
        delete[] map[i];
    }
    delete[] map;
    delwin(gamescr);
    delete snake;
}

void GameScene::Update() {
    snake->Update();
    CheckCollide();
}

void GameScene::Draw() {
    clear();
    gamescr = newwin(height, width * 2, 2, 4);
    refresh();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == 1) { // Wall
                mvwprintw(gamescr, i, j * 2, "##");
            } else if (map[i][j] == 2) { // Immune Wall
                mvwprintw(gamescr, i, j * 2, "XX");
            }
        }
    }
    snake->Draw(gamescr);
    wrefresh(gamescr);
}

void GameScene::InitScreen() {
    start_color();
    init_pair(COLOR_BACKGROUND, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_GAME_BACKGROUND, COLOR_BLACK, COLOR_BLUE);
    init_pair(COLOR_SNAKE, COLOR_GREEN, COLOR_YELLOW);
}

void GameScene::InitMap() {
    width = 21;
    height = 21;
    map = new int*[height];
    for (int i = 0; i < height; i++) {
        map[i] = new int[width];
        for (int j = 0; j < width; j++) {
            if ((i == 0 && j == 0) || (i == 0 && j == width - 1) ||
                (i == height - 1 && j == 0) || (i == height - 1 && j == width - 1)) {
                map[i][j] = 2; // Immune Wall
            } else if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                map[i][j] = 1; // Wall
            } else {
                map[i][j] = 0; // Empty space
            }
        }
    }
}

void GameScene::CheckCollide() {
    if (snake->IsCollidedSelf()) {
        isGameOver = true;
        return;
    }
    Vector2 p = snake->GetPosition();
    if (map[p.y][p.x] == 1 || map[p.y][p.x] == 2) {
        isGameOver = true;
        return;
    }
}

bool GameScene::IsGameOver() {
    return isGameOver;
}

void GameScene::SaveMap(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; ++j < width; ++j) {
                file << map[i][j] << " ";
            }
            file << "\n";
        }
        file.close();
    }
}

void GameScene::LoadMap(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                file >> map[i][j];
            }
        }
        file.close();
    }
}
