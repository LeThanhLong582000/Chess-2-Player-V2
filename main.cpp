#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "Chess.h"

using namespace std;
using namespace sf;

vector<vector<Chess_Box>> Play_Ground = Make_Play_Ground();

int main()
{
    srand(time(NULL));
    clock_t St, End;
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

            if(Playing == "Red")
            {
                St = clock();
                vector<int> Next;
                Next = Next_Move(Play_Ground);
                cout << Play_Ground[Next[0]][Next[1]].Get_Unit().first << '\n';
                cout << Next[0] << ' ' << Next[1] << ' ' << "To" << ' ' << Next[2] << ' ' << Next[3] << '\n';
                if(Play_Ground[Next[2]][Next[3]].Get_Unit().first == "king") window.close();
                Move(Next[0], Next[1], Next[2], Next[3], Play_Ground);
                Playing = "White";
                End = clock();
                cout << End - St << '\n';
            }

            if(Moving)
            {
                Play_Ground[From_x][From_y].Set_Ori(28,28);
                Play_Ground[From_x][From_y].Set_Pos(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
            }

            if(Mouse::isButtonPressed(Mouse::Left))
            {
                ans_x = (Mouse::getPosition(window).y - 50) / 114 + 1;
                ans_y = (Mouse::getPosition(window).x - 55) / 113 + 1;
                if(!Moving)
                {
                    if(Play_Ground[ans_x][ans_y].Get_Unit().second == Playing)
                    {
                        if(Play_Ground[ans_x][ans_y].Get_Unit().first == "None") continue;
                        if(ans_x == 9 || ans_y == 9) continue;
                        From_x = ans_x;
                        From_y = ans_y;
                        Moving = true;
                    }
                }
                else
                {
                    if(ans_x == 9 || ans_y == 9 || ans_y == 0 || ans_x == 0) continue;
                    To_x = ans_x;
                    To_y = ans_y;
                    if(Can_Move(From_x, From_y, To_x, To_y, Play_Ground))
                    {
                        if(Play_Ground[To_x][To_y].Get_Unit().first == "king")
                        {
                            window.close();
                        }
                        Move(From_x, From_y, To_x, To_y, Play_Ground);
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
