#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "data.h"
#include "account.h"

using namespace std;

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

void loadUserStockData(account u, map<string, vector<int>> stockdata)
{
    ifstream infile("./data/userdata/"+u->accountID+".txt");

    

    if (infile.is_open()) 
    {
        while (getline(infile, line)) 
        {
            stock mystock = new Stock;
            istringstream iss(line);
            string word;
            int index = 0;

            while (iss >> word) 
            {
                if(index == 0) line = mystock->name;
                else if(index == 1) line = mystock->purchase_price;
                else if(index == 2) line = mystock->holding_amount;
                index++;             
            }
            mystock->purchase_amount =  mystock->purchase_price * mystock->holding_amount;

            mystock->current_price = stockdata[mystock->name].back();
            mystock->evaluation_amount = mystock->current_price * mystock->holding_amount;

            u->stockOwned[mystock->name] = mystock; 
        }

        infile.close();
    }
    else
    {
        cout << "Unable to open file";
    }

}

vector<account> loadUserData(map<string, vector<int>> stockdata)
{
    ifstream infile("./data/userdata/user.txt");
    string line;
    vector<account> userdata;

    if (infile.is_open()) 
    {
        while (getline(infile, line)) 
        {

            account user = new Account;

            istringstream iss(line);
            string word;
            int index = 0;

            while (iss >> word) 
            {
                if(index == 0) line = user->owner_name;
                else if(index == 1) line = user->accountID;
                else if(index == 2) line = user->password;
                index++;             
            }

            loadUserStockData(user, stockdata);
            userdata.push_back(user); 
        }

        infile.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    return userdata;
}

void saveUserData(vector<account> users)
{

}