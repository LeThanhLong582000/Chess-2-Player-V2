#include "Units.h"

using namespace std;
using namespace sf;

Units::Units()
{
    this->texture.loadFromFile("Units.png");
    this->sprite.setTexture(texture);
    this->sprite.setScale(2,2);
    this->sprite.setPosition(0,0);
}

void Units::Set_Pos(int x,int y)
{
    this->sprite.setPosition(x,y);
}

pair<int,int> Units::Get_Pos()
{
    return make_pair(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

void Units::Display(RenderWindow &window)
{
    window.draw(this->sprite);
}

void Units::Set_Ori(int x, int y)
{
    this->sprite.setOrigin(x,y);
}

void Units::Set_Unit(string unit, string Color)
{
    if(Color == "Red")
    {
        if(unit == "Pawn")
        {
            this->sprite.setTextureRect(IntRect(285,0,56,55));
        }
        if(unit == "Rock")
        {
            this->sprite.setTextureRect(IntRect(0,0,56,55));
        }
        if(unit == "Knight")
        {
            this->sprite.setTextureRect(IntRect(57,0,56,55));
        }
        if(unit == "Bishop")
        {
            this->sprite.setTextureRect(IntRect(114,0,56,55));
        }
        if(unit == "Queen")
        {
            this->sprite.setTextureRect(IntRect(171,0,56,55));
        }
        if(unit == "King")
        {
            this->sprite.setTextureRect(IntRect(228,0,56,55));
        }
    }
    else
    {
        if(unit == "Pawn")
        {
            this->sprite.setTextureRect(IntRect(285,60,56,55));
        }
        if(unit == "Rock")
        {
            this->sprite.setTextureRect(IntRect(0,60,56,55));
        }
        if(unit == "Knight")
        {
            this->sprite.setTextureRect(IntRect(57,60,56,55));
        }
        if(unit == "Bishop")
        {
            this->sprite.setTextureRect(IntRect(114,60,56,55));
        }
        if(unit == "Queen")
        {
            this->sprite.setTextureRect(IntRect(171,60,56,55));
        }
        if(unit == "King")
        {
            this->sprite.setTextureRect(IntRect(228,60,56,55));
        }
    }
}
