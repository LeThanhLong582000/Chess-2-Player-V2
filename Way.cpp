#include <bits/stdc++.h>
#include "Way.h"

using namespace std;

const int deep = 4;
string Ground[10][10];
int From_x, From_y, To_x, To_y, Max;
vector<vector<int>> Result;
vector<vector<int>> Ans;

bool Can_Go()
{
    if(To_x > 8 || To_y > 8 || To_x < 1 || To_y < 1) return false;
    if(Ground[To_x][To_y][1] == Ground[From_x][From_y][1]) return false;

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
    return false;
}

int get_point()
{
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
            if(To_x == 8 || To_x == 1) Point = 90;
            break;
    }
    if(Ground[From_x][From_y][1] == 'W') Point = -Point;
    return Point;
}

int Find_Max(int k = 2)
{
    int Fx = From_x, Fy = From_y;
    int Point = -10000, AnsPoint;
    int AnsFx, AnsFy, AnsTx, AnsTy;
    string AnsF, AnsT;
    switch(Ground[From_x][From_y][0])
    {
        case 'R':
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx;
                To_y = Fy + i;
                if(To_y > 8) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx;
                To_y = Fy - i;
                if(To_y < 0) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy;
                if(To_x > 8) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy;
                if(To_x < 0) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            break;
        case 'K':
            To_x = Fx + 1;
            To_y = Fy + 2;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx + 1;
            To_y = Fy - 2;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx + 2;
            To_y = Fy + 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx + 2;
            To_y = Fy - 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 1;
            To_y = Fy + 2;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 1;
            To_y = Fy - 2;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 2;
            To_y = Fy + 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 2;
            To_y = Fy - 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            break;
        case 'B':
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy + i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy - i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy + i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy - i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            break;
        case 'Q':
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx;
                To_y = Fy + i;
                if(To_y > 8) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx;
                To_y = Fy - i;
                if(To_y < 0) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy;
                if(To_x > 8) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy;
                if(To_x < 0) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy + i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy - i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy + i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy - i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = max(Point, AnsPoint + ClassMin(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            break;
        case 'k':
            for(int i = -1; i <= 1; ++i)
            {
                for(int j = -1; j <= 1; ++j)
                {
                    To_x = Fx + i;
                    To_y = Fy + j;
                    if(Can_Go())
                    {
                        AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                        AnsF = Ground[Fx][Fy];
                        AnsT = Ground[To_x][To_y];
                        AnsPoint = get_point();
                        Ground[Fx][Fy] = "NN";
                        Ground[To_x][To_y] = AnsF;
                        Point = max(Point, AnsPoint + ClassMin(k + 1));
                        From_x = Fx;
                        From_y = Fy;
                        Ground[AnsFx][AnsFy] = AnsF;
                        Ground[AnsTx][AnsTy] = AnsT;
                    }
                }
            }
            break;
        case 'P':
            To_x = Fx - 1;
            To_y = Fy + 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 1;
            To_y = Fy;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 1;
            To_y = Fy - 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 2;
            To_y = Fy;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = max(Point, AnsPoint + ClassMin(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            break;
    }
    return Point;
}

int ClassMax(int k = 2)
{
    if(k > deep) return 0;
    int Point = -10000;
    for(int i = 1; i <= 8; ++i)
    {
        for(int j = 1; j <= 8; ++j)
        {
            if(Ground[i][j][1] == 'R')
            {
                From_x = i;
                From_y = j;
                int ans = Find_Max(k);
                Point = max(Point, ans);
            }
        }
    }
    return Point;
}

int Find_Min(int k = 2)
{
    int Fx = From_x, Fy = From_y;
    int Point = 10000, AnsPoint;
    int AnsFx, AnsFy, AnsTx, AnsTy;
    string AnsF, AnsT;
    switch(Ground[From_x][From_y][0])
    {
        case 'R':
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx;
                To_y = Fy + i;
                if(To_y > 8) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx;
                To_y = Fy - i;
                if(To_y < 0) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy;
                if(To_x > 8) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy;
                if(To_x < 0) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            break;
        case 'K':
            To_x = Fx + 1;
            To_y = Fy + 2;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx + 1;
            To_y = Fy - 2;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx + 2;
            To_y = Fy + 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx + 2;
            To_y = Fy - 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 1;
            To_y = Fy + 2;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 1;
            To_y = Fy - 2;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 2;
            To_y = Fy + 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 2;
            To_y = Fy - 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            break;
        case 'B':
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy + i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy - i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy + i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy - i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            break;
        case 'Q':
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx;
                To_y = Fy + i;
                if(To_y > 8) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx;
                To_y = Fy - i;
                if(To_y < 0) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy;
                if(To_x > 8) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy;
                if(To_x < 0) break;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy + i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx + i;
                To_y = Fy - i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy + i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = Fx - i;
                To_y = Fy - i;
                if(Can_Go())
                {
                    AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                    AnsF = Ground[Fx][Fy];
                    AnsT = Ground[To_x][To_y];
                    AnsPoint = get_point();
                    Ground[Fx][Fy] = "NN";
                    Ground[To_x][To_y] = AnsF;
                    Point = min(Point, AnsPoint + ClassMax(k + 1));
                    From_x = Fx;
                    From_y = Fy;
                    Ground[AnsFx][AnsFy] = AnsF;
                    Ground[AnsTx][AnsTy] = AnsT;
                }
            }
            break;
        case 'k':
            for(int i = -1; i <= 1; ++i)
            {
                for(int j = -1; j <= 1; ++j)
                {
                    To_x = Fx + i;
                    To_y = Fy + j;
                    if(Can_Go())
                    {
                        AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                        AnsF = Ground[Fx][Fy];
                        AnsT = Ground[To_x][To_y];
                        AnsPoint = get_point();
                        Ground[Fx][Fy] = "NN";
                        Ground[To_x][To_y] = AnsF;
                        Point = min(Point, AnsPoint + ClassMax(k + 1));
                        From_x = Fx;
                        From_y = Fy;
                        Ground[AnsFx][AnsFy] = AnsF;
                        Ground[AnsTx][AnsTy] = AnsT;
                    }
                }
            }
            break;
        case 'P':
            To_x = Fx - 1;
            To_y = Fy + 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 1;
            To_y = Fy;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 1;
            To_y = Fy - 1;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            To_x = Fx - 2;
            To_y = Fy;
            if(Can_Go())
            {
                AnsFx = Fx, AnsFy = Fy, AnsTx = To_x, AnsTy = To_y;
                AnsF = Ground[Fx][Fy];
                AnsT = Ground[To_x][To_y];
                AnsPoint = get_point();
                Ground[Fx][Fy] = "NN";
                Ground[To_x][To_y] = AnsF;
                Point = min(Point, AnsPoint + ClassMax(k + 1));
                From_x = Fx;
                From_y = Fy;
                Ground[AnsFx][AnsFy] = AnsF;
                Ground[AnsTx][AnsTy] = AnsT;
            }
            break;
    }
    return Point;
}

int ClassMin(int k = 2)
{
    if(k > deep) return 0;
    int Point = 10000;
    for(int i = 1; i <= 8; ++i)
    {
        for(int j = 1; j <= 8; ++j)
        {
            if(Ground[i][j][1] == 'W')
            {
                From_x = i;
                From_y = j;
                int ans = Find_Min(k);
                Point = min(Point, ans);
            }
        }
    }
    return Point;
}

int MiniMax(int k = 2)
{
    int AnsFx = From_x, AnsFy = From_y, AnsTx = To_x, AnsTy = To_y;
    string AnsF = Ground[From_x][From_y], AnsT = Ground[To_x][To_y];
    Ground[From_x][From_y] = "NN";
    Ground[To_x][To_y] = AnsF;
    int Point = ClassMin();
    From_x = AnsFx;
    From_y = AnsFy;
    To_x = AnsTx;
    To_y = AnsTy;
    Ground[AnsFx][AnsFy] = AnsF;
    Ground[AnsTx][AnsTy] = AnsT;
    return Point;
}

void Update()
{
    if(!Can_Go()) return ;
    int Point = 0;
    int Fx = From_x, Fy = From_y, Tx = To_x, Ty = To_y;
//    cout << "Move: " << From_x << ' ' << From_y << ' ' << "To " << To_x << ' ' << To_y << '\n';
    Point = get_point() + MiniMax();
    From_x = Fx;
    From_y = Fy;
    To_x = Tx;
    To_y = Ty;
    Result.push_back({From_x, From_y, To_x, To_y, Point});
//    cout << "Point: " << Point << '\n';
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
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x;
                To_y = From_y - i;
                if(To_y < 0) break;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y;
                if(To_x > 8) break;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y;
                if(To_x < 0) break;
                Update();
            }
            break;
        case 'K':
            To_x = From_x + 1;
            To_y = From_y + 2;
            Update();
            To_x = From_x + 1;
            To_y = From_y - 2;
            Update();
            To_x = From_x + 2;
            To_y = From_y + 1;
            Update();
            To_x = From_x + 2;
            To_y = From_y - 1;
            Update();
            To_x = From_x - 1;
            To_y = From_y + 2;
            Update();
            To_x = From_x - 1;
            To_y = From_y - 2;
            Update();
            To_x = From_x - 2;
            To_y = From_y + 1;
            Update();
            To_x = From_x - 2;
            To_y = From_y - 1;
            Update();
            break;
        case 'B':
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y + i;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y - i;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y + i;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y - i;
                Update();
            }
            break;
        case 'Q':
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x;
                To_y = From_y + i;
                if(To_y > 8) break;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x;
                To_y = From_y - i;
                if(To_y < 0) break;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y;
                if(To_x > 8) break;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y;
                if(To_x < 0) break;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y + i;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x + i;
                To_y = From_y - i;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y + i;
                Update();
            }
            for(int i = 1; i < 8; ++i)
            {
                To_x = From_x - i;
                To_y = From_y - i;
                Update();
            }
            break;
        case 'k':
            for(int i = -1; i <= 1; ++i)
            {
                for(int j = -1; j <= 1; ++j)
                {
                    To_x = From_x + i;
                    To_y = From_y + j;
                    Update();
                }
            }
            break;
        case 'P':
            To_x = From_x + 1;
            To_y = From_y + 1;
            Update();
            To_x = From_x + 1;
            To_y = From_y;
            Update();
            To_x = From_x + 1;
            To_y = From_y - 1;
            Update();
            To_x = From_x + 2;
            To_y = From_y;
            Update();
            break;
    }
}

vector<int> Find_Way(vector<vector<string>> Map)
{
    From_x = 8;
    From_y = 1;
    To_x = 1;
    To_y = 1;
    Result.clear();
    Ans.clear();
    Max = -10000;
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
    cout << "Size: " << Result.size() << '\n';
    int cnt = rand() % ((int) Ans.size());
    cout << "Max " << Max << '\n';
    return Ans[cnt];
}
