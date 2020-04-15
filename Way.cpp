#include <bits/stdc++.h>
#include "Way.h"

using namespace std;

string Ground[10][10];
int From_x, From_y, To_x, To_y, Max;
vector<vector<int>> Result;
vector<vector<int>> Ans;

bool Can_Go()
{
    if(To_x > 8 || To_y > 8 || To_x < 1 || To_y < 1) return false;
    if(Ground[To_x][To_y][1] == 'R') return false;

    int dx, dy, x, y;
    switch(Ground[From_x][From_y][0])
    {
        case 'R':
            if(From_x != To_x && From_y != To_y) return false;
            if(From_x == To_x)
            {
                for(int i = min(From_y, To_y) + 1; i < max(From_y,To_y); ++i)
                {
                    if(Ground[From_x][i][0] != 'N') return false;
                }
                return true;
            }
            else
            {
                for(int i = min(From_x, To_x) + 1; i < max(From_x, To_x); ++i)
                {
                    if(Ground[i][From_y][0] != 'N') return false;
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
                if(Ground[x][y][0] != 'N') return false;
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
                    if(Ground[x][y][0] != 'N') return false;
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
                    if(Ground[From_x][i][0] != 'N') return false;
                }
            }
            else
            {
                for(int i = min(From_x,To_x) + 1; i <= max(From_x,To_x) - 1; ++i)
                {
                    if(Ground[i][From_y][0] != 'N') return false;
                }
            }
            return true;
            break;
        case 'k':
            if(abs(From_x - To_x) > 1 || abs(From_y - To_y) > 1) return false;
            return true;
            break;
        case 'P':
            if(Ground[From_x][From_y][1] == 'R')
            {
                if(From_x == 2)
                {
                    if(To_y == From_y && To_x == From_x + 1 && Ground[To_x][To_y][0] == 'N') return true;
                    if((To_y == From_y + 1 || To_y == From_y - 1) && To_x == From_x + 1 && Ground[To_x][To_y][0] != 'N') return true;
                    if(To_y == From_y && To_x == From_x + 2 && Ground[To_x][To_y][0] == 'N' && Ground[From_x + 1][From_y][0] == 'N') return true;
                }
                else
                {
                    if(To_y == From_y && To_x == From_x + 1 && Ground[To_x][To_y][0] == 'N') return true;
                    if((To_y == From_y + 1 || To_y == From_y - 1) && To_x == From_x + 1 && Ground[To_x][To_y][0] != 'N') return true;
                }
                return false;
            }
            else
            {
                if(From_x == 7)
                {
                    if(To_y == From_y && To_x == From_x - 1 && Ground[To_x][To_y][0] == 'N') return true;
                    if((To_y == From_y - 1 || To_y == From_y + 1) && To_x == From_x - 1 && Ground[To_x][To_y][0] != 'N') return true;
                    if(To_y == From_y && To_x == From_x - 2 && Ground[To_x][To_y][0] == 'N' && Ground[From_x - 1][From_y][0] == 'N') return true;
                }
                else
                {
                    if(To_y == From_y && To_x == From_x - 1 && Ground[To_x][To_y][0] == 'N') return true;
                    if((To_y == From_y - 1 || To_y == From_y + 1) && To_x == From_x - 1 && Ground[To_x][To_y][0] != 'N') return true;
                }
                return false;
            }
            break;
    }
}

void update()
{
    if(Can_Go() == false) return;
    int Point = 0;
    switch(Ground[To_x][To_y][0])
    {
        case 'R':
            Point = 50;
            break;
        case 'K':
            Point = 30;
            break;
        case 'B':
            Point = 30;
            break;
        case 'Q':
            Point = 90;
            break;
        case 'k':
            Point = 900;
            break;
        case 'P':
            Point = 10;
            if(To_x == 8) Point = 90;
            break;
    }
    Result.push_back({From_x, From_y, To_x, To_y, Point});
    Max = max(Max, Point);
}

void Find()
{
    switch(Ground[From_x][From_y][0])
    {
        case 'R':
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x;
                To_y = From_y + i;
                if(To_y > 8) break;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x;
                To_y = From_y - i;
                if(To_y < 0) break;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y;
                if(To_x > 8) break;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y;
                if(To_x < 0) break;
                update();
            }
            break;
        case 'K':
            To_x = From_x + 1;
            To_y = From_y + 2;
            update();
            To_x = From_x + 1;
            To_y = From_y - 2;
            update();
            To_x = From_x + 2;
            To_y = From_y + 1;
            update();
            To_x = From_x + 2;
            To_y = From_y - 1;
            update();
            To_x = From_x - 1;
            To_y = From_y + 2;
            update();
            To_x = From_x - 1;
            To_y = From_y - 2;
            update();
            To_x = From_x - 2;
            To_y = From_y + 1;
            update();
            To_x = From_x - 2;
            To_y = From_y - 1;
            update();
            break;
        case 'B':
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y + i;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y - i;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y + i;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y - i;
                update();
            }
            break;
        case 'Q':
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x;
                To_y = From_y + i;
                if(To_y > 8) break;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x;
                To_y = From_y - i;
                if(To_y < 0) break;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y;
                if(To_x > 8) break;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y;
                if(To_x < 0) break;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y + i;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y - i;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y + i;
                update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y - i;
                update();
            }
            break;
        case 'k':
            for(int i = -1; i <= 1; ++i)
            {
                for(int j = -1; j <= 1; ++j)
                {
                    To_x = From_x + i;
                    To_y = From_y + j;
                    update();
                }
            }
            break;
        case 'P':
            To_x = From_x + 1;
            To_y = From_y + 1;
            update();
            To_x = From_x + 1;
            To_y = From_y;
            update();
            To_x = From_x + 1;
            To_y = From_y - 1;
            update();
            To_x = From_x + 2;
            To_y = From_y;
            update();
            break;
    }
}

vector<int> Find_Way(vector<vector<string>> Map)
{
    Result.clear();
    Ans.clear();
    Max = -1;
    for(int i = 1; i <= 8; ++i)
    {
        for(int j = 1; j <= 8; ++j)
        {
            Ground[i][j] = Map[i][j];
        }
    }
    for(int i = 1; i <= 8; ++i)
    {
        for(int j = 1; j <= 8; ++j)
        {
            if(Ground[i][j][1] == 'R')
            {
                From_x = i;
                From_y = j;
                Find();
            }
        }
    }
    for(auto x : Result)
    {
        if(x[4] == Max) Ans.push_back(x);
    }
    int cnt = rand() % ((int) Ans.size());
    return Ans[cnt];
}
