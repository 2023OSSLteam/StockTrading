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
  viewPortfolio(users[0]);
  /*  
  cout << "Purchase Amount: " << users[0]->purchaseAmount << endl;
  cout << "Total Stock Value: " << users[0]->totalStockValue << endl;
  cout << "Asset: " << users[0]->assetAmount << endl;
  cout << "Asset: " << users[0]->assetValue << endl;
  cout << "Cash: " << users[0]->cash << endl;
  cout << "Asset Return Ratio: " << users[0]->assetReturnRatio << "%" << endl;
  cout << "Asset Return Value: " << users[0]->assetReturnValue << endl;
  */

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
