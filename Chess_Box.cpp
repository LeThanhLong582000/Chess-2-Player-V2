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
