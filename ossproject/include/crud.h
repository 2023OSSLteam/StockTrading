#include <iostream>
#include <vector>

#ifndef ACCOUNT_H
#include "account.h"
#define ACCOUNT_H
#endif

void menu();

void create (vector<account> &users,map<string, vector<int>> stockdata);
void read(vector<account> users);
int readall(vector<account> users);
void update(vector<account> users);
void del(vector<account> &users);
