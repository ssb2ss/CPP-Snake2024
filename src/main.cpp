#include <ncurses.h>
#include <thread>

#include "InputManager.h"
#include "GameScene.h"

void Update(GameScene *game)
{
    while (true)
    {
        clear();
        game->Update();
        game->Draw();

        if (game->IsGameOver()) // get returned by collide method if isGameover is false,
        {
            WINDOW *end;
            end = newwin(5, 21, 10, 15);
            box(end, 0, 0);
            mvwprintw(end, 2, 6, "Game Over");
            wrefresh(end);
            getch();
            break;
        }
        if (game->Stage_pass()) // if player finished all mission
        {
            WINDOW *stagepass;
            stagepass = newwin(5, 21, 10, 15);
            box(stagepass, 0, 0);
            mvwprintw(stagepass, 2, 6, "STAGE PASS");
            wrefresh(stagepass);
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
    // init
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    GameScene *game = new GameScene();

    // Multi-threading - Game Update / Input Key
    std::thread update(Update, game);
    std::thread input(Input);
    input.detach();
    update.join(); // Wait for Update() to return

    endwin();

    return 0;
}