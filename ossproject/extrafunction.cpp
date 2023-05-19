#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <sstream>
#include <algorithm>
#include <iomanip>
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

void calculateRSI(map<string, vector<int>>& stocks, string stockName)
{
    int searchflag = 0;
    vector<int> diff;
    vector<int> up;
    vector<int> down;
    vector<double> AU;
    vector<double> DU;
    vector<double> rsi;

    for (auto& s : stocks) 
    {
        if(s.first.compare(stockName) == 0)
        {
            int lastIndex = s.second.size() - 19;

            for (int i = lastIndex; i < s.second.size(); i++) 
            {
                diff.push_back(s.second[i] - s.second[i-1]);
                if(diff.back() >= 0)
                {
                    up.push_back(diff.back());
                    down.push_back(0);

                }
                else
                {
                    down.push_back(abs(diff.back()));
                    up.push_back(0);
                }
                
            }
            for(int i=14; i<19;i++)
            {
                double uavg = 0;
                double davg = 0;

                for(int k=i-14; k<i-1;k++)
                {
                    uavg += up[k];
                    davg += down[k];                    
                }
                rsi.push_back(((uavg / 14.0) / ((uavg / 14.0)+ (davg / 14.0)))*100);

            }

            searchflag = 1;
            break;
        }

    }
    if(searchflag == 0) 
    {
        cout << "stock not found" << endl;
        return;
    }
    
    cout << "[" ;
    for (int i = 0; i < 5; i++) 
    {
        cout.precision(3);
        if(i<4)    
            cout << rsi[i] << " -> ";
        else
            cout << rsi[i] ;
    }
    cout << "]" << endl;

    if(rsi[4] >= 70) cout <<"과매수 구간으로 매도를 추천 드립니다!"<<endl;
    else if(rsi[4] <= 30) cout <<"과매도 구간으로 매수를 추천 드립니다!"<<endl;


    if(rsi[0] <= rsi[4])
        cout << "해당 주식은 상승 추세에 있습니다!" << endl;
    else
        cout << "해당 주식은 하락 추세에 있습니다!" << endl;

    cout << endl;

}


void printNowStock(map<string, vector<int>>& stocks, int rank)
{   
    int r = 0;
    cout << "     Stocks     | Today |  Change  | Ratio" << endl;
    cout << "----------------|-------|----------|------" << endl;
    
    for (auto& s : stocks) 
    {
        if(rank == r)
            break;

        int current_p = s.second.back();
        int yesterday = s.second[s.second.size() - 2];
        int spread = (current_p - yesterday);
        float ratio =  (float(spread) / float(yesterday)) * 100;
        
        cout.width(16);
        cout << s.first ;
        cout << "|" ;

        cout.width(7);
        cout << current_p;
        cout << "|" ;

        string sign = spread >= 0 ? "+" : "";
        string spread_str = sign + to_string(spread);

        cout.width(10); 
        cout << spread_str;
        cout << "|" ;

        sign = ratio >= 0 ? "+" : "";
        string ratio_str = sign + to_string(ratio);
        
        int index = ratio_str.find('.');
        ratio_str = ratio_str.substr(0, index) + ratio_str.substr(index , 3); //  
    
        cout.width(6);
        cout  << ratio_str <<"%" <<endl;

        r++;
    }
    cout << endl;
}

void fallSearch(map<string, vector<int>>& stocks, int fallRate)
{
    cout << "최근 6개월간 고점대비 " << fallRate << "% 이상 하락한 종목은??" << endl;
    cout << "       Stocks       | High |   Now   | Fall Rate" << endl;
    cout << "--------------------|------|---------|----------" << endl;

    for (auto& s : stocks) 
    {
        
        int max = *max_element(s.second.begin(), s.second.end()-1);
        int today = s.second.back();

        int spread = (today - max);
        float ratio =  (float(spread) / float(max)) * 100;

        if(ratio < -fallRate)
        {
            cout.width(20);
            cout << std::left << s.first ;
            cout << "|" ;

            cout.width(6);
            cout << max ;
            cout << "|" ;

            cout.width(9);
            cout << today ;
            cout << "|" ;
            

            cout.width(10);
            cout << std::right << ratio << "%" << endl;

        }   
        
    }
    cout << endl;
    cout << endl;
}


void sellALL(vector<account>& users)
{
    string name, ID, password;
    string sellitem;
    cout<<"이름 : ";
    cin>>name;
    cout<<"계좌번호 : ";
    cin>>ID;
    cout<<"비밀번호 : ";
    cin>>password;


    for(vector<account>::size_type i = 0; i<users.size(); i++)
    {
        if(name.compare(users[i]->owner_name)==0 && ID.compare(users[i]->accountID)==0 && password.compare(users[i]->password)==0)
        {
            for(auto const& stocks : users[i]->stockOwned)
            {
                auto const& val = stocks.second;
                cout<<"기업 : "<<val->name <<  endl;
                cout<<"매입 금액 : " << std::fixed << std::setprecision(0) << val->purchase_amount <<  endl;
                cout<<"청산 금액 : " << std::fixed << std::setprecision(0) << val->evaluation_amount <<  endl;
                cout<<"수익 : " << std::fixed << std::setprecision(0) << val->evaluation_amount - val->purchase_amount<< endl;;
                cout << endl;
                users[i]->cash += val->evaluation_amount;                
            }
            users[i]->assetAmount = users[i]->cash;
            users[i]->assetValue = users[i]->cash;
            users[i]->assetReturnRatio = 0;
            users[i]->assetReturnValue = 0;
            users[i]->stockOwned.clear();
        }
            
    }        
    
}