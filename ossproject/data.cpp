#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "data.h"
#include "account.h"

map<string, vector<int>> loadAllStockData()
{    
    string line;
    ifstream myfile("stockdata.txt"); // 파일 경로 및 이름 입력
    map<string, vector<int>> stocks;

    if (myfile.is_open()) 
    {
        
        while (getline(myfile, line)) 
        {
            vector<int> words; // string 타입의 벡터 생성
            istringstream iss(line);
            string word;
            string ticker;
            
            iss >> word;
            ticker = word;
            while (iss >> word) 
            { // 띄어쓰기로 분리하여 벡터에 추가
                words.push_back(stoi(word));                
            }
            stocks[ticker] = words;
        }
        
        myfile.close();        
    }
    else 
    {
        cout << "Unable to open file";
    }

    return stocks;
}

void loadUserStockData(account u)
{
    ifstream infile("./data/userdata/"+u->owner_name+".csv");

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
        loadUserStockData(user);
        users.push_back(user); 
    }

    infile.close();

    return 0;
}

void saveUserData(vector<account> users)
{

}