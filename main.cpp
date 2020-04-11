#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "Chess_Box.h"

using namespace std;
using namespace sf;

vector<vector<Chess_Box>> Play_Ground = Make_Play_Ground();

bool Can_Move(int From_x, int From_y, int To_x, int To_y)
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
            for(int i = min(From_x, To_x); i < max(From_x, To_x); ++i)
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

int main()
{
//    Music music;
//    music.openFromFile("NgauHung.ogg");
//    music.setLoop(true);
//    music.play();
    for(int i = 1; i <= 8; ++i)
    {
        for(int j = 1; j <= 8; ++j)
        {
            Play_Ground[i][j].Set_Pos(55 + 113 * (j - 1), 50 + 114 * (i - 1));
        }
    }

    RenderWindow window(VideoMode(1008,1008),"Chess", Style::Default);
    Texture Back_Ground_Texture;
    Back_Ground_Texture.loadFromFile("ChessBoard.png");
    Sprite Back_Ground;
    Back_Ground.setScale(2.0,2.0);
    Back_Ground.setTexture(Back_Ground_Texture);

    bool Moving = false;
    int From_x = 0, From_y = 0, To_x = 0, To_y = 0;
    int ans_x = 0, ans_y = 0;

    string Playing = "White";

    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed) window.close();

            if(Moving)
            {
                Play_Ground[From_x][From_y].Set_Ori(28,28);
                Play_Ground[From_x][From_y].Set_Pos(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
            }

            if(Mouse::isButtonPressed(Mouse::Left))
            {
                ans_x = (Mouse::getPosition(window).y - 50) / 114 + 1;
                ans_y = (Mouse::getPosition(window).x - 55) / 113 + 1;
                if(!Moving && Play_Ground[ans_x][ans_y].Get_Unit().second == Playing)
                {
                    if(Play_Ground[ans_x][ans_y].Get_Unit().first == "None") continue;
                    if(ans_x == 9 || ans_y == 9) continue;
                    From_x = ans_x;
                    From_y = ans_y;
                    Moving = true;
                }
                else
                {
                    if(ans_x == 9 || ans_y == 9) continue;
                    To_x = ans_x;
                    To_y = ans_y;
                    if(Can_Move(From_x, From_y, To_x, To_y))
                    {
                        if(Play_Ground[To_x][To_y].Get_Unit().first == "King")
                        {
                            window.close();
                        }
                        Play_Ground[To_x][To_y].Set_Unit(Play_Ground[From_x][From_y].Get_Unit().first, Play_Ground[From_x][From_y].Get_Unit().second);
                        Play_Ground[From_x][From_y].Set_Ori(0,0);
                        Play_Ground[From_x][From_y].Set_Unit("None", "None");
                        Play_Ground[From_x][From_y].Set_Pos(55 + 113 * (From_y - 1), 50 + 114 * (From_x - 1));
                        if(To_x == 1 || To_x == 8)
                        {
                            Play_Ground[To_x][To_y].Set_Unit("Queen", Play_Ground[To_x][To_y].Get_Unit().second);
                        }
                        Moving = false;
                        Playing = (Playing == "White") ? "Red" : "White";
                    }
                    else
                    {
                        Play_Ground[From_x][From_y].Set_Ori(0,0);
                        Play_Ground[From_x][From_y].Set_Pos(55 + 113 * (From_y - 1), 50 + 114 * (From_x - 1));
                        Moving = false;
                    }
                }
            }
        }
        window.clear();
        window.draw(Back_Ground);
        for(int i = 1; i <= 8; ++i)
        {
            for(int j = 1; j <= 8; ++j)
            {
                if(Play_Ground[i][j].Get_Unit().first != "None") Play_Ground[i][j].Display(window);
            }
        }
        window.display();
    }
    return 0;
}
