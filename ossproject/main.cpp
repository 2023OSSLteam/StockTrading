#include <iostream>
#include <vector>
#include <string>
#include "data.h"
#include "extrafunction.h"


using namespace std;

int main(int argc, char **argv)
{
  char c;
  int pflag = 0;

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
        calculateRSI(stocks, "�Ｚ����");
        break;
        
      
      case 'V':
        printNowStock(stocks, 50);
        break;
      
      case 'F':
        fallSearch(stocks, 30);
        break;
      case 'W':
        sellALL(users);
        break;

      case 'T':
        sellALL(users);
        break;
      case 'E':
        whoBest(users);
        break;
      
        
        /*
        string a;
        cin>>a;
        
      if(a.compare("RunElevated")==0)
      {
        readall(users);
        
        int a1;
        cout<<"1.������� ��� ���� ����"<<endl;
        cout<<"��� ����� �̿��ϰڽ��ϱ�?: ";
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
      } */

    }
  }while (c != 'q');

  //save(users);
  return 0;
}

