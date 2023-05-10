#include <iostream>
#include <vector>
#include <string>
#include "account.h"


using namespace std;

int main(int argc, char **argv) 
{
  char c;
  cin >> c ;
  map<vector> stocks;
  vector<account> users;
  loadUserData(vector<account> users);
  // load 함수 구현
  // 각 기능 단축키 설명

  do{
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
