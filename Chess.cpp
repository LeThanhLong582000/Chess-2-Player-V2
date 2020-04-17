#include "Chess.h"

using namespace std;

int res = 0;

vector<vector<Chess_Box>> Make_Play_Ground()
{
    vector<vector<Chess_Box>> Play_Ground(10);
    for(int i = 0; i < (int) Play_Ground.size(); ++i)
    {
        Play_Ground[i].resize(10);
    }
    for(int i = 1; i <= 8; ++i)
    {
        for(int j = 1; j <= 8; ++j)
        {
            Play_Ground[i][j].Set_Pos(55 + 113 * (j - 1), 50 + 114 * (i - 1));
        }
    }

    for(int i = 1; i <= 8; ++i)
    {
        Play_Ground[2][i].Set_Unit("Pawn", "Red");
        Play_Ground[7][i].Set_Unit("Pawn", "White");
    }

    Play_Ground[1][1].Set_Unit("Rock", "Red");
    Play_Ground[1][8].Set_Unit("Rock", "Red");
    Play_Ground[8][1].Set_Unit("Rock", "White");
    Play_Ground[8][8].Set_Unit("Rock", "White");

    Play_Ground[1][2].Set_Unit("Knight", "Red");
    Play_Ground[1][7].Set_Unit("Knight", "Red");
    Play_Ground[8][2].Set_Unit("Knight", "White");
    Play_Ground[8][7].Set_Unit("Knight", "White");

    Play_Ground[1][3].Set_Unit("Bishop", "Red");
    Play_Ground[1][6].Set_Unit("Bishop", "Red");
    Play_Ground[8][3].Set_Unit("Bishop", "White");
    Play_Ground[8][6].Set_Unit("Bishop", "White");

    Play_Ground[1][4].Set_Unit("Queen", "Red");
    Play_Ground[8][4].Set_Unit("Queen", "White");

    Play_Ground[1][5].Set_Unit("king", "Red");
    Play_Ground[8][5].Set_Unit("king", "White");

    return Play_Ground;
}

bool Can_Move(int From_x, int From_y, int To_x, int To_y, vector<vector<Chess_Box>> Play_Ground)
{
    if(To_x > 8 || To_y > 8 || To_x < 1 || To_y < 1) return false;
    int dx, dy, x, y;

    if(Play_Ground[From_x][From_y].Get_Unit().second == Play_Ground[To_x][To_y].Get_Unit().second) return false;
    switch(Play_Ground[From_x][From_y].Get_Unit().first[0])
    {
        case 'R':
            if(From_x != To_x && From_y != To_y) return false;
            if(From_x == To_x)
            {
                for(int i = min(From_y, To_y) + 1; i < max(From_y,To_y); ++i)
                {
                    if(Play_Ground[From_x][i].Get_Unit().first != "None") return false;
                }
                return true;
            }
            else
            {
                for(int i = min(From_x, To_x) + 1; i < max(From_x, To_x); ++i)
                {
                    if(Play_Ground[i][From_y].Get_Unit().first != "None") return false;
                }
                return true;
            }
            break;
        case 'K':
            if(abs(From_x - To_x) > 2 || abs(From_x - To_x) < 1) return false;
            if(abs(From_y - To_y) > 2 || abs(From_y - To_y) < 1) return false;
            if(abs(From_x - To_x) + abs(From_y - To_y) == 3) return true;
            return false;
            break;
        case 'B':
            if(abs(From_x - To_x) != abs(From_y - To_y)) return false;
            dx = From_x < To_x ? 1 : -1;
            dy = From_y < To_y ? 1 : -1;
            x = From_x + dx;
            y = From_y + dy;
            while(x != To_x)
            {
                if(Play_Ground[x][y].Get_Unit().first != "None") return false;
                x += dx;
                y += dy;
            }
            return true;
            break;
        case 'Q':
            if(abs(From_x - To_x) == abs(From_y - To_y))
            {
                dx = From_x < To_x ? 1 : -1;
                dy = From_y < To_y ? 1 : -1;
                x = From_x + dx;
                y = From_y + dy;
                while(x != To_x)
                {
                    if(Play_Ground[x][y].Get_Unit().first != "None") return false;
                    x += dx;
                    y += dy;
                }
                return true;
            }
            if(From_x != To_x && From_y != To_y) return false;
            if(From_x == To_x)
            {
                for(int i = min(From_y,To_y) + 1; i <= max(From_y,To_y) - 1; ++i)
                {
                    if(Play_Ground[From_x][i].Get_Unit().first != "None") return false;
                }
            }
            else
            {
                for(int i = min(From_x,To_x) + 1; i <= max(From_x,To_x) - 1; ++i)
                {
                    if(Play_Ground[i][From_y].Get_Unit().first != "None") return false;
                }
            }
            return true;
            break;
        case 'k':
            if(abs(From_x - To_x) > 1 || abs(From_y - To_y) > 1) return false;
            return true;
            break;
        case 'P':
            if(Play_Ground[From_x][From_y].Get_Unit().second == "Red")
            {
                if(From_x == 2)
                {
                    if(To_y == From_y && To_x == From_x + 1 && Play_Ground[To_x][To_y].Get_Unit().first == "None") return true;
                    if((To_y == From_y + 1 || To_y == From_y - 1) && To_x == From_x + 1 && Play_Ground[To_x][To_y].Get_Unit().first != "None") return true;
                    if(To_y == From_y && To_x == From_x + 2 && Play_Ground[To_x][To_y].Get_Unit().first == "None" && Play_Ground[From_x + 1][From_y].Get_Unit().first == "None") return true;
                }
                else
                {
                    if(To_y == From_y && To_x == From_x + 1 && Play_Ground[To_x][To_y].Get_Unit().first == "None") return true;
                    if((To_y == From_y + 1 || To_y == From_y - 1) && To_x == From_x + 1 && Play_Ground[To_x][To_y].Get_Unit().first != "None") return true;
                }
                return false;
            }
            else
            {
                if(From_x == 7)
                {
                    if(To_y == From_y && To_x == From_x - 1 && Play_Ground[To_x][To_y].Get_Unit().first == "None") return true;
                    if((To_y == From_y - 1 || To_y == From_y + 1) && To_x == From_x - 1 && Play_Ground[To_x][To_y].Get_Unit().first != "None") return true;
                    if(To_y == From_y && To_x == From_x - 2 && Play_Ground[To_x][To_y].Get_Unit().first == "None" && Play_Ground[From_x - 1][From_y].Get_Unit().first == "None") return true;
                }
                else
                {
                    if(To_y == From_y && To_x == From_x - 1 && Play_Ground[To_x][To_y].Get_Unit().first == "None") return true;
                    if((To_y == From_y - 1 || To_y == From_y + 1) && To_x == From_x - 1 && Play_Ground[To_x][To_y].Get_Unit().first != "None") return true;
                }
                return false;
            }
            break;
    }
    return false;
}

void Move(int From_x, int From_y, int To_x, int To_y, vector<vector<Chess_Box>> &Play_Ground)
{
    Play_Ground[To_x][To_y].Set_Unit(Play_Ground[From_x][From_y].Get_Unit().first, Play_Ground[From_x][From_y].Get_Unit().second);
    Play_Ground[From_x][From_y].Set_Ori(0,0);
    Play_Ground[From_x][From_y].Set_Unit("None", "None");
    Play_Ground[From_x][From_y].Set_Pos(55 + 113 * (From_y - 1), 50 + 114 * (From_x - 1));
    if((To_x == 1 || To_x == 8) && Play_Ground[To_x][To_y].Get_Unit().first == "Pawn")
    {
        Play_Ground[To_x][To_y].Set_Unit("Queen", Play_Ground[To_x][To_y].Get_Unit().second);
    }
}

//void Update(int From_x, int From_y, int To_x, int To_y, vector<vector<Chess_Box>> Play_Ground, vector<vector<int>> &Result, int &Max)
//{
//    res++;
//    if(!Can_Move(From_x, From_y, To_x, To_y, Play_Ground)) return;
//    int Point = Play_Ground[To_x][To_y].Get_Point();
//    Max = max(Max, Point);
//    Result.push_back({From_x, From_y, To_x, To_y, Point});
//}

vector<int> Next_Move(vector<vector<Chess_Box>> Play_Ground)
{
    vector<vector<string>> Map(10);
    for(vector<string> &S : Map) S.resize(10);
    string Color, Army;
    for(int i = 1; i <= 8; ++i)
    {
        for(int j = 1; j <= 8; ++j)
        {
            Army = Play_Ground[i][j].Get_Unit().first;
            Color = Play_Ground[i][j].Get_Unit().second;
            Map[i][j] = Army[0];
            Map[i][j] += Color[0];
        }
    }
    return Find_Way(Map);
}
