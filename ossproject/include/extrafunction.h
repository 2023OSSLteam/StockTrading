#include <iostream>
#include <vector>

#ifndef ACCOUNT_H
#include "account.h"
#define ACCOUNT_H
#endif

void viewPortfolio(account u);
void goNextDay(map<string, vector<int>>& stocks, vector<account>& users);
void calculateRSI(map<string, vector<int>>& stocks, string stockName);
void printNowStock(map<string, vector<int>>& stocks, int rank);
void fallSearch(map<string, vector<int>>& stocks, int fallRate);
void sellALL(vector<account>& users);
void graph(map<string, vector<int>> stockdata);
void sell(vector<account> &users, map<string, vector<int>> stockdata);
void buy(vector<account> &users, map<string, vector<int>> stockdata);
void ranking(vector<account> users);
void whoBest(vector<account>& users);