#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include "account.h"
#include "extrafunction.h"

void setColor(unsigned short text, unsigned short back)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void viewPortfolio(account u)
{   
    srand(time(0));
     

    for (const auto& [symbol, stk] : u->stockOwned) 
    {
        int rate = (stk->purchase_amount / u->assetAmount)*100;
        
        cout.width(16);
        cout << std::left << symbol;
        cout.width(3);
        cout << std::left << rate << "%" << endl;

        unsigned short text = rand() % 16;
        unsigned short back = (rand() % 15) + 1;
        setColor(text,back);
        for(int i=0;i<rate;i++)
        {
            cout << " " ;
        }
        
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << endl;
    }
    int cashrate = (float(u->cash)/float(u->assetAmount))*100.0;
    
    cout.width(16);
    cout << std::left << "Cash"; 
    cout.width(3);
    cout << std::left << cashrate << "%" << endl;

    unsigned short text = rand() % 16;
    unsigned short back = (rand() % 15) + 1;

    setColor(text,back);
    for(int i=0;i<cashrate;i++)
    {
        cout << " " ;
    }
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << endl;
         
    //cout << u->assetAmount << endl;
    
}


void goNextDay(map<string, vector<int>>& stocks, vector<account>& users)
{
    for (auto& s : stocks) 
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.9, 1.1);

        double randomValue = dis(gen);
        s.second.push_back(s.second.back()*randomValue);
    }

    for (auto& u : users)
    {
        u->purchaseAmount = 0;
        for (auto& userstock : u->stockOwned)
        {
            userstock.second->current_price = stocks[userstock.second->name].back();
            userstock.second->evaluation_amount = userstock.second->current_price * userstock.second->holding_amount;            
            u->purchaseAmount += userstock.second->evaluation_amount;
        }

        u->assetValue = u->purchaseAmount + u->cash;

        u->assetReturnRatio = float(u->assetValue)/float(u->assetAmount);
        if(u->assetReturnRatio >= 1)
            u->assetReturnRatio -= 1;
        else
            u->assetReturnRatio = 1 - u->assetReturnRatio;
        u->assetReturnRatio = u->assetReturnRatio*100.0;

        u->assetReturnValue = u->assetValue - u->assetAmount;
    }
}
/*
vector<double> calculateRSI(map<string, vector<int>>& stocks, string stockName)
{
    

    return 0;
}*/