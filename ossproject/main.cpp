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
        
        cout << "��Ʈ�������� Ȯ���� ���¹�ȣ �Է� : " << endl;
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
        cout << "�ش� ���´� �˻����� �ʽ��ϴ�" << endl;
        break;
        
      case 'A':
        readall(users);
        break;
      
      case 'N':
        goNextDay(stocks, users);
        break;
      
      case 'I':
        cout<<"RSI�� ����� ������?? : ";
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

        if(rsiflag == 0) cout << "�ش� ������ �˻����� �ʽ��ϴ�." << endl;
        else rsiflag = 0;    
        
        break;
        
      
      case 'V':
        cout << "�����ǿ� ǥ���� ���� ����?? (1~200): ";
        cin >> v_num; 
        if(v_num < 1 || v_num > 200)
        {
          cout << "������ �°� �ٽ� �Է��� �ּ���" << endl;
          break;
        }

        printNowStock(stocks, v_num);
        break;
      
      case 'F':
        cout << "������� ������ % �Է� (1 ~ 99): ";
        cin >> f_num;
        
        if(f_num < 1 || f_num > 99)
        {
          cout << "������ �°� �ٽ� �Է��� �ּ���" << endl;
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

