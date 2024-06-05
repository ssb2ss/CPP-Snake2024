#include <ncurses.h>
#include <random>
#include <ctime>

#include "InputManager.h"
#include "GameScene.h"
#include "Box.h"
#include "Gate.h"

GameScene::GameScene()
{
    isGameOver = false;

    InitMap();
    InitScreen();

    snake = new Snake(width / 2, height / 2, 3); // make smake at the center
    // and deafult length become 3 in same row.
    // gate = new Gate(map, width, height);
    gate = nullptr;
    gateTimer = 0;
    t_box = new Box();
    t_box->Make_Random_Score();
    srand(time(0));
    lastItemTime = std::chrono::steady_clock::now(); // 마지막 아이템 생성 시간 초기화
    starttime = std::chrono::steady_clock::now();
    std::srand(static_cast<unsigned int>(std::time(0)));
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
    if (gate != nullptr)
    {
        delete gate;
    }
    delete t_box;
}

void GameScene::Update()
{
    snake->Update();
    UpdateGate();
    CheckCollide();
    GenerateRandomItem(); // 새로운 아이템 생성
    CheckItemCollision(); // 뱀이 아이템과 충돌했는지 검사

    Updating_Box();
}

void GameScene::Draw()
{
    // TODO: Draw Screen With Colors
    gamescr = newwin(height, width * 2, 2, 4);

    refresh();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == 1 || map[i][j] == 2) // Wall
            {
                //attron(COLOR_PAIR(COLOR_WALL));
                mvwprintw(gamescr, i, j * 2, "##");
                //attroff(COLOR_PAIR(COLOR_WALL));
            }
        }
    }

    snake->Draw(gamescr);
    if (gate != nullptr)
    {
        gate->Draw(gamescr);
    }
    for (auto &item : items)
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
    Updating_Box();
    wrefresh(gamescr);
}

void GameScene::InitScreen()
{
    start_color();

    init_pair(COLOR_BACKGROUND, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_GAME_BACKGROUND, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_SNAKE, COLOR_GREEN, COLOR_YELLOW);
    init_pair(COLOR_WALL, COLOR_RED, COLOR_BLACK);
}

void GameScene::InitMap()
{
    width = 21;
    height = 21;
    map = new int *[height];
    for (int i = 0; i < height; i++)
    {
        map[i] = new int[width];
        // for (int j = 0; j < width; j++)
        // {
        //     if ((i == 0 && j == 0) ||
        //         (i == 0 && j == width - 1) ||
        //         (i == height - 1 && j == 0) ||
        //         (i == height - 1 && j == width - 1))
        //     {
        //         map[i][j] = 2;
        //     }
        //     else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
        //     {
        //         map[i][j] = 1;
        //     }
        //     else
        //     {
        //         map[i][j] = 0;
        //     }
        // }
    }
    LoadMap("src/map.txt");
}

void GameScene::CheckCollide() // when snake hit wall or collideself is game over
{
    if (snake->IsCollidedSelf())
    {
        isGameOver = true;
        return;
    }
    Vector2 p = snake->GetPosition();
    if (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height)
    {
        isGameOver = true;
        return;
    }
    else if (map[p.y][p.x] == 1 || map[p.y][p.x] == 2)
    {
        if (gate != nullptr && gate->IsCollided(p)) // 여기서 새로운 인자값 하나 받아서 true로 만들기
        {
            Vector2 d = snake->GetDirection();
            snake->SetDirection(gate->GetExitDirection(p, d));
            snake->SetPosition(gate->GetExitPosition(p));
            passingGate = true;
        }
        else
        {
            isGameOver = true;
            return;
        }
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
            {
                snake->SetTailSize(snake->GetTailSize() + 1);
                getItem = 1;
            }
            else if (it->type == ITEM_SHRINK)
            {
                snake->SetTailSize(snake->GetTailSize() - 1);
                getItem = 2;
            }
            else if (it->type == ITEM_SPEED_UP)
            {
                snake->IncreaseSpeed();
                getItem = 3;
            }
            else if (it->type == ITEM_SPEED_DOWN)
            {
                snake->DecreaseSpeed();
                getItem = 4;
            }
            items.erase(it);
            map[p.y][p.x] = 0;
            break;
        }
    }
}

void GameScene::Making_box()
{
    std::vector<std::string> temp_list_name = t_box->get_list_name();
    std::vector<int> mission_scr = t_box->get_Mission_score();
    std::vector<int> score_cnt = t_box->get_Score_count();

    for (size_t i = 0; i < temp_list_name.size(); i++)
    {
        if (i == 0)
        {
            mvwprintw(ScoreBox, 3 + i, 1, "%s : %d / %d", temp_list_name[i].c_str(), snake->GetTailSize(), mission_scr[i]);
        }
        mvwprintw(ScoreBox, 3 + i, 1, "%s : %d", temp_list_name[i].c_str(), score_cnt[i]);
    }

    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - starttime;
    int seconds = static_cast<int>(elapsed_seconds.count());
    mvwprintw(ScoreBox, 9, 1, "PLAY TIME : %d seconds ", seconds);

    std::vector<std::string> mission_chk = t_box->get_missionchk();
    for (size_t i = 0; i < temp_list_name.size(); i++)
    {
        mvwprintw(MissionBOX, 3 + i, 1, "%s : %d ( %s )", temp_list_name[i].c_str(), mission_scr[i], mission_chk[i].c_str());
    }

    wrefresh(ScoreBox);
    wrefresh(MissionBOX);
}

void GameScene::Updating_Box()
{
    if (ScoreBox != nullptr)
    {
        delwin(ScoreBox);
    }
    if (MissionBOX != nullptr)
    {
        delwin(MissionBOX);
    }

    ScoreBox = newwin(t_box->get_height() + 2, t_box->get_width() * 2, 2, 47);
    MissionBOX = newwin(t_box->get_height(), t_box->get_width() * 2, 14, 47);
    box(ScoreBox, 0, 0);
    box(MissionBOX, 0, 0);

    mvwprintw(ScoreBox, 1, 14, "SCORE BOX");
    mvwprintw(ScoreBox, 2, 12, "<  STAGE  %d  >", current_stage + 1);
    mvwprintw(MissionBOX, 1, 14, "MISSION BOX");
    Updating_Score();
    Checking_Mission();
    Making_box();
    wrefresh(ScoreBox);
    wrefresh(MissionBOX);
}
void GameScene::Updating_Score()
{ // changing score for each list
    if (passingGate)
    {
        t_box->plusScore(5);
        passingGate = false;
    }
    switch (getItem)
    {
    case 1:
        t_box->plusScore(1);
        t_box->plusScore(0);

        getItem = 0;
        break;
    case 2:
        t_box->plusScore(2);
        t_box->MinusSize();
        getItem = 0;
        break;
    case 3:
        t_box->plusScore(3);
        getItem = 0;
        break;
    case 4:
        t_box->plusScore(4);
        getItem = 0;
        break;
    }
}
void GameScene::Checking_Mission()
{ // if score equals to mssion score "X" change to "V"
    std::vector<int> score_cnt = t_box->get_Score_count();
    std::vector<int> mission_scr = t_box->get_Mission_score();
    for (int i = 0; i < 6; i++)
    {
        if (score_cnt[i] == mission_scr[i])
        {
            t_box->SetCheck(i);
        }
    }
}
bool GameScene::Stage_pass()
{ // checking all misiions
    std::vector<std::string> Mission_check = t_box->get_missionchk();
    for (auto it : Mission_check)
    {
        if (it != "V")
        {
            return false;
        }
    }
    return true;
}

void GameScene::SaveMap(const std::string& filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                file << map[i][j] << " ";
            }
            file << "\n";
        }
    }
    file.close();
}

void GameScene::LoadMap(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                file >> map[i][j];
            }
        }
    }
    else
    {
        isGameOver = true;
    }
    file.close();
}

int GameScene::GetDelay()
{
    return snake->GetDelayFromSpeed();
}

void GameScene::UpdateGate()
{
    gateTimer++;
    if (gate != nullptr)
    {
        gate->Update();
        if (gateTimer > 20 && gate->IsRemovable(snake->GetTailSize()))
        {
            delete gate;
            gate = nullptr;
            gateTimer = 0;
        }
    }
    else
    {
        if (gateTimer > 10)
        {
            gate = new Gate(map, width, height);
            gateTimer = 0;
        }
    }
}