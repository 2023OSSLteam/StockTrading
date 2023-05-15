#include <iostream>
#include <vector>
#include <string>
#include "data.h"
#include "extrafunction.h"




using namespace std;

int main(int argc, char **argv) 
{
  char c;
  
  map<string, vector<int>> stocks = loadAllStockData();
  vector<account> users;
  users = loadUserData(stocks);
  //viewPortfolio(users[0]);
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
    menu();
    
    cin >> c ;
    switch (c) 
    {
      case 'C':
        create(users, stocks);
        break;

      case 'R':
        read(users);
        break;

      case 'U':
        update(users);
        break;

      case 'D':
        del(users);
        break;
      case 'P':
        viewPortfolio(users[1]);
        break;
        
      case 'A':
      string a;
      cin>>a;

      if(a.compare("RunElevated")==0){
        int a1;
        cout<<"1.사용자의 모든 정보 열람"<<endl;
        cout<<"어느 기능을 이용하겠습니까?: ";
        cin>>a1;
        if(a1==1){
          int a=0;
          a=readall(users);
          if(a==0){
            c='q';
          }
        }
      }
      else{
        cin.clear();
        cin.ignore(256,'\n');
      }

    }
  }while (c != 'q');

  save(users);
  return 0;
}

