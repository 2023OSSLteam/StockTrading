#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "data.h"

using namespace std;

map<string, vector<int>> loadAllStockData()
{    
    string line;
    ifstream myfile("./data/stockdata.txt"); // 파일 경로 및 이름 입력
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
        cout << "Unable to open file 3" << endl;
    }

    return stocks;
}

void loadUserStockData(account u, map<string, vector<int>> stockdata)
{
    cout << u->accountID << endl;
    cout <<"./data/userdata/"+u->accountID+".txt"<<endl;

    ifstream infile("./data/userdata/"+u->accountID+".txt");

    string line;

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
                if(index == 0) mystock->name = word;
                else if(index == 1) mystock->purchase_price = stoi(word);
                else if(index == 2) mystock->holding_amount = stoi(word);
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
        cout << "Unable to open file 2";
    }

}

vector<account> loadUserData(map<string, vector<int>> stockdata)
{
    ifstream infile("./data/userdata/user.txt");
    string line;
    vector<account> userdata;

    if (infile.is_open()) 
    {
        cout<<"open file1";
        while (getline(infile, line)) 
        {

            account user = new Account;

            istringstream iss(line);
            string word;
            int index = 0;

            while (iss >> word) 
            {
                if(index == 0) user->owner_name = word;
                else if(index == 1) user->accountID = word;
                else if(index == 2) user->password = word;
                else if(index == 3) user->cash = stoi(word);
                index++;             
            }

            loadUserStockData(user, stockdata);
            
            for (auto const& [key, val] : user->stockOwned) 
            {
                user->purchaseAmount += val->purchase_amount ;
                user->totalStockValue += val->evaluation_amount;
            }
            user->assetAmount = user->purchaseAmount + user->cash;
            user->assetValue = user->totalStockValue + user->cash;
            
            user->assetReturnRatio = user->assetValue/user->assetAmount;
            user->assetReturnValue = user->assetValue - user->assetAmount;

            userdata.push_back(user); 
        }

        infile.close();
    }
    else
    {
        cout << "Unable to open file 1" << endl;
    }

    return userdata;
}

void saveUserData(vector<account> users)
{

}