#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "account.h"
#include "extrafunction.h"


void viewPortfolio(account u)
{   
    for (const auto& [symbol, stk] : u->stockOwned) 
    {
        cout << symbol << " " << (stk->purchase_amount / u->assetAmount)*100 << endl;
    }
    //cout << u->cash << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    for(int i=0;i<100;i++)
        cout << "/■" ;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    //cout << u->assetAmount << endl;
    cout << "cash " << (float(u->cash)/float(u->assetAmount))*100.0 << endl;
}