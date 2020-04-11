#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Units.h"

using namespace std;
using namespace sf;


class Chess_Box
{
private:
    string Unit;
    string Color;
    Units Army;
    int x,y;
public:
    Chess_Box();
    void Set_Unit(string Unit, string Color);
    pair<string,string> Get_Unit();
    void Set_Pos(int x,int y);
    void Set_Ori(int x,int y);
    pair<int,int> Get_Pos();
    void Display(RenderWindow &window);
};

vector<vector<Chess_Box>> Make_Play_Ground();
