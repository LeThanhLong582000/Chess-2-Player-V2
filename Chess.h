#include <bits/stdc++.h>
#include "Chess_Box.h"
#include "Way.h"

using namespace std;

vector<vector<Chess_Box>> Make_Play_Ground();

bool Can_Move(int From_x, int From_y, int To_x, int To_y, vector<vector<Chess_Box>> Play_Ground);

void Move(int From_x, int From_y, int To_x, int To_y, vector<vector<Chess_Box>> &Play_Ground);

//void Update(int From_x, int From_y, int To_x, int To_y, vector<vector<Chess_Box>> Play_Ground, vector<vector<int>> &Result, int &Max);

vector<int> Next_Move(vector<vector<Chess_Box>> Play_Ground);
