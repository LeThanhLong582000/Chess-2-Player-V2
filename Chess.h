#include <bits/stdc++.h>
#include "Chess_Box.h"

using namespace std;

vector<vector<Chess_Box>> Make_Play_Ground();

bool Can_Move(int From_x, int From_y, int To_x, int To_y, vector<vector<Chess_Box>> Play_Ground);

void Move(int From_x, int From_y, int To_x, int To_y, vector<vector<Chess_Box>> &Play_Ground);

vector<int> Next_Move();