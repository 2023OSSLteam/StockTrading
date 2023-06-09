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
                user->purchaseAmount += val->purchase_amount;
                user->totalStockValue += val->evaluation_amount;
            }
            user->assetAmount = user->purchaseAmount + user->cash;
            user->assetValue = user->totalStockValue + user->cash;
            
            user->assetReturnRatio = float(user->assetValue)/float(user->assetAmount);
            if(user->assetReturnRatio >= 1)
                user->assetReturnRatio -= 1;
            else
                user->assetReturnRatio = 1 - user->assetReturnRatio;
            user->assetReturnRatio = user->assetReturnRatio*100.0;

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

void save(vector<account> users){
    string a;
    ofstream user("./data/userdata/user.txt", ios_base::out);
    for(vector<account>::size_type i = 0; i<users.size();i++){
        user<<users[i]->owner_name<<"  ";
        user<<users[i]->accountID<<"  ";
        user<<users[i]->password<<"  ";
        user<<users[i]->cash<<endl;
        ofstream ID("./data/userdata/"+users[i]->accountID+".txt", ios_base::out);
        for(auto const& a : users[i]->stockOwned){
            auto const& val=a.second;
            ID<<val->name<<"  ";
            ID<<val->purchase_price<<"  ";
            ID<<val->holding_amount<<endl;
            
        }
        ID.close();
    }
    user.close();
}
