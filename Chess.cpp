#include "Chess.h"

using namespace std;

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

    Play_Ground[1][5].Set_Unit("King", "Red");
    Play_Ground[8][5].Set_Unit("King", "White");

    return Play_Ground;
}

bool Can_Move(int From_x, int From_y, int To_x, int To_y, vector<vector<Chess_Box>> Play_Ground)
{
    int dx, dy, x, y;

    if(Play_Ground[From_x][From_y].Get_Unit().second == Play_Ground[To_x][To_y].Get_Unit().second) return false;
    if(Play_Ground[From_x][From_y].Get_Unit().first == "Rock")
    {
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
    }
    if(Play_Ground[From_x][From_y].Get_Unit().first == "Knight")
    {
        if(abs(From_x - To_x) > 2 || abs(From_x - To_x) < 1) return false;
        if(abs(From_y - To_y) > 2 || abs(From_y - To_y) < 1) return false;
        if(abs(From_x - To_x) + abs(From_y - To_y) == 3) return true;
        return false;
    }
    if(Play_Ground[From_x][From_y].Get_Unit().first == "Bishop")
    {
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
    }
    if(Play_Ground[From_x][From_y].Get_Unit().first == "Queen")
    {
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
    }
    if(Play_Ground[From_x][From_y].Get_Unit().first == "King")
    {
        if(abs(From_x - To_x) > 1 || abs(From_y - To_y) > 1) return false;
        return true;
    }
    if(Play_Ground[From_x][From_y].Get_Unit().first == "Pawn")
    {
        if(Play_Ground[From_x][From_y].Get_Unit().second == "Red")
        {
            if(From_x == 2)
            {
                if(To_y == From_y && To_x == From_x + 1 && Play_Ground[To_x][To_y].Get_Unit().first == "None") return true;
                if((To_y == From_y + 1 || To_y == From_y - 1) && To_x == From_x + 1 && Play_Ground[To_x][To_y].Get_Unit().first != "None") return true;
                if(To_y == From_y && To_x == From_x + 2 && Play_Ground[To_x][To_y].Get_Unit().first == "None") return true;
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
                if(To_y == From_y && To_x == From_x - 2 && Play_Ground[To_x][To_y].Get_Unit().first == "None") return true;
            }
            else
            {
                if(To_y == From_y && To_x == From_x - 1 && Play_Ground[To_x][To_y].Get_Unit().first == "None") return true;
                if((To_y == From_y - 1 || To_y == From_y + 1) && To_x == From_x - 1 && Play_Ground[To_x][To_y].Get_Unit().first != "None") return true;
            }
            return false;
        }
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

vector<int> Next_Move()
{
    vector<int> Next(4);
    Next[0] = rand() % 8 + 1;
    Next[1] = rand() % 8 + 1;
    Next[2] = rand() % 8 + 1;
    Next[3] = rand() % 8 + 1;
    return Next;
}
