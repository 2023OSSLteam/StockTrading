#include <iostream>
#include <vector>
#include "account.h"

map<string, vector<int>> loadAllStockData();
void loadUserStockData(account u, map<string, vector<int>> stockdata);
vector<account> loadUserData(map<string, vector<int>> stockdata);
void saveUserData(vector<account> users);
void menu();
void create (vector<account> &users,map<string, vector<int>> stockdata);
void read(vector<account> users);
void update(vector<account> users);
void del(vector<account> &users);
void save(vector<account> users);
void sell(vector<account> &users, map<string, vector<int>> stockdata);
