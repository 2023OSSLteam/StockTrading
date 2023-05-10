#include <iostream>
#include <vector>
#include "account.h"

map<string, vector<int>> loadAllStockData();
void loadUserStockData(account u, map<string, vector<int>> stockdata);
vector<account> loadUserData(map<string, vector<int>> stockdata);
void saveUserData(vector<account> users);

