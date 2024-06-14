#ifndef _BOX_H_
#define _BOX_H_

#include "Utilities.h"
#include <vector>
#include <string>
#include <curses.h>

class Box
{
    int box_width = 20;
    int box_height = 10;

    int **box;

    std::vector<std::string> list_name = {"B ", "Gain Growth Items ", "Gain Poison Items ", "Gain Speed Up Item", "Gain Speed Down Item", "Times Of using Gate "};
    std::vector<int> Score_count = {4, 0, 0, 0, 0, 0};

    std::vector<int> Mission_score = {0, 0, 0, 0, 0, 0};                     // 0 is default value. this value changes when start Game means Stage
    std::vector<std::string> Mission_check = {"X", "X", "X", "X", "X", "X"}; // dealut is "X"

public:
    int get_list_name_size()
    {
        return list_name.size();
    }
    std::vector<std::string> get_list_name()
    {
        return list_name;
    }
    std::vector<int> get_Mission_score()
    {
        return Mission_score;
    }
    std::vector<int> get_Score_count()
    {
        return Score_count;
    }
    std::vector<std::string> get_missionchk()
    {
        return Mission_check;
    }
    int get_height()
    {
        return box_height;
    }
    int get_width()
    {
        return box_width;
    }
    void plusScore(int i)
    {
        Score_count[i]++;
    }
    void MinusSize()
    {
        Score_count[0]--;
    }
    void SetCheck(int i)
    {
        Mission_check[i] = "V";
    }
    void Make_Random_Score()
    { // making different Score for each Stage.
        for (int i = 0; i < Mission_score.size(); i++)
        {
            if (i == 0)
            {
                int t_random = 4 + rand() % 6;
                Mission_score[i] = t_random;
                continue;
            }
            int random = 1 + rand() % 9; // from 1 to 9 make random number
            //int random = 1;
            Mission_score[i] = random;
        }
    }
};

#endif