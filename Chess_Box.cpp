#include "Chess_Box.h"

using namespace sf;
using namespace std;

Chess_Box::Chess_Box()
{
    this->x = 0;
    this->y = 0;
    this->Unit = "None";
    this->Color = "None";
    this->Army.Set_Unit("None", "None");
}

void Chess_Box::Set_Unit(string unit, string Color)
{
    this->Unit = unit;
    this->Color = Color;
    if(unit != "None") this->Army.Set_Unit(unit, Color);
}

pair<string,string> Chess_Box::Get_Unit()
{
    return make_pair(this->Unit, this->Color);
}

void Chess_Box::Set_Pos(int x,int y)
{
    this->x = x;
    this-> y = y;
    this->Army.Set_Pos(x,y);
}

pair<int,int> Chess_Box::Get_Pos()
{
    return make_pair(this->x, this->y);
}

void Chess_Box::Set_Ori(int x, int y)
{
    this->Army.Set_Ori(x,y);
}

void Chess_Box::Display(RenderWindow &window)
{
    this->Army.Display(window);
}

vector<vector<Chess_Box>> Make_Play_Ground()
{
    vector<vector<Chess_Box>> Play_Ground(10);
    for(int i = 0; i < Play_Ground.size(); ++i)
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
