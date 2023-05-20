#include <iostream>
#include <vector>

#ifndef ACCOUNT_H
#include "account.h"
#define ACCOUNT_H
#endif

map<string, vector<int>> loadAllStockData();
void loadUserStockData(account u, map<string, vector<int>> stockdata);
vector<account> loadUserData(map<string, vector<int>> stockdata);
void save(vector<account> users);
