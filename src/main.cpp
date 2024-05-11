#include <ncurses.h>
#include <thread>

#include "InputManager.h"
#include "GameScene.h"

void Update(GameScene* game)
{
    while (true)
    {
        clear();
        game->Update();
        game->Draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Input()
{
    while (true)
    {
        InputManager::GetInstance().pressedKey = getch();
    }
}

int main()
{
    // init
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    GameScene* game = new GameScene();

    // Multi-threading - Game Update / Input Key
    std::thread update(Update, game);
    std::thread input(Input);
    input.detach();
    update.join(); // Wait for Update() to return

    endwin();

    return 0;
}