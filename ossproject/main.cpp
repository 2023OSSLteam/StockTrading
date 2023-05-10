#include <iostream>
#include <vector>
#include <string>
#include "data.h"


using namespace std;

int main(int argc, char **argv) 
{
  char c;
  
  map<string, vector<int>> stocks = loadAllStockData();
  vector<account> users;
  users = loadUserData(stocks);

  cout << users[0]->owner_name << endl;

  // load 함수 구현
  // 각 기능 단축키 설명

  do{
    cin >> c ;
    switch (c) 
    {
      case 'C':
        break;

      case 'R':
        break;

      case 'U':
        break;

      case 'D':
        break;
    }
  }while (c != 'q');

  return 0;
}
