#include <iostream>
#include "account.h"
#include "extrafunction.h"

void viewPortfolio(account u)
{
    
    for (const auto& [symbol, stk] : u->stockOwned) 
    {
        cout << symbol << " " << stk->purchase_price / u->purchaseAmount << endl;
    }
    cout << u->cash << endl;
}