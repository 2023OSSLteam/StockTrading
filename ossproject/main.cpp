#include <iostream>
#include <vector>
#include <string>
#include "data.h"
#include "extrafunction.h"
#include "crud.h"

using namespace std;

int main(int argc, char **argv)
{
  char c;
  int pflag = 0;
  int rsiflag=0;
  int v_num = 20;
  int f_num = 20;

  string RSIname;

  string portAccount;

  map<string, vector<int>> stocks = loadAllStockData();
  vector<account> users;
  
  users = loadUserData(stocks);

  do{
    menu();
    cout<<">> ";
    cin >> c ;
    cout<<endl;
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
        
      case 'G':
        graph(stocks);
        break;
        
      case 'S':
        sell(users,stocks);
        break;
        
      case 'O':
        ranking(users);
        break;
        
      case 'B':
        buy(users,stocks);
        break;
      
      case 'P':
        
        cout << "포트폴리오를 확인할 계좌번호 입력 : " << endl;
        cin >> portAccount;
        
        for(auto p : users)
        {
          if((p->accountID).compare(portAccount) == 0)
          {
            viewPortfolio(p);
            pflag = 1;
            break;
          }             
        }
        if(pflag == 1) 
        {
          pflag = 0;
          break;
        }
        cout << "해당 계좌는 검색되지 않습니다" << endl;
        break;
        
      case 'A':
        readall(users);
        break;
      
      case 'N':
        goNextDay(stocks, users);
        break;
      
      case 'I':
        cout<<"RSI를 계산할 종목은?? : ";
        cin>> RSIname;

        for(auto const& a : stocks)
        {
            auto const& val=a.first;
            if((val).compare(RSIname)==0)
            {
                rsiflag=1;
                calculateRSI(stocks, RSIname);
                break;
            }
        }

        if(rsiflag == 0) cout << "해당 종목은 검색되지 않습니다." << endl;
        else rsiflag = 0;    
        
        break;
        
      
      case 'V':
        cout << "전광판에 표시할 종목 수는?? (1~200): ";
        cin >> v_num; 
        if(v_num < 1 || v_num > 200)
        {
          cout << "범위에 맞게 다시 입력해 주세요" << endl;
          break;
        }

        printNowStock(stocks, v_num);
        break;
      
      case 'F':
        cout << "고점대비 떨어진 % 입력 (1 ~ 99): ";
        cin >> f_num;
        
        if(f_num < 1 || f_num > 99)
        {
          cout << "범위에 맞게 다시 입력해 주세요" << endl;
          break;
        }

        fallSearch(stocks, f_num);
        break;

      case 'W':
        sellALL(users);
        break;

      case 'E':
        whoBest(users);
        break;

      case 'J':
        save(users);

    }
  }while (c != 'q');

  return 0;
}

