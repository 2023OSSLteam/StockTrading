#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
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
        cout << symbol << " " << rate <<"%" << endl;

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
    
    cout << "Cash " << cashrate << "%" << endl;

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