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

        if (game->IsGameOver())
        {
            mvprintw(20, 50, "Game Over");
            getch();
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(DEFAULT_DELAY));
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

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    GameScene* game = new GameScene();


    std::thread update(Update, game);
    std::thread input(Input);
    input.detach();
    update.join(); 

    endwin();

    return 0;
}