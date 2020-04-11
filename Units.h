#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

class Units
{
private:
    Texture texture;
    Sprite sprite;
public:
    Units();
    void Set_Pos(int x,int y);
    pair<int,int> Get_Pos();
    void Display(RenderWindow &window);
    void Set_Unit(string unit, string Color);
    void Set_Ori(int x, int y);
};
