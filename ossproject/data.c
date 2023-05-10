#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "data.h"
#include "account.h"

void loadUserStockData(account u)
{

}

void loadUserData(vector<account> users)
{
    ifstream infile("./data/userdata/user.csv");
    string line;

    getline(infile, line);

    while (getline(infile, line)) 
    {
        stringstream ss(line);

        account user = new Account;
        int index = 0;

        while (getline(ss, line, ',')) 
        {
            if(index == 0) line = user->owner_name;
            else if(index == 1) line = user->accountID;
            else if(index == 2) line = user->password;
        }
        users.push_back(user); 
    }

    infile.close();

    return 0;
}

void saveUserData(vector<account> users)
{

}