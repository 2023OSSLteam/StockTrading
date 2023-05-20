#include <Windows.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <set>
#include <time.h>
#include <random>
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

            for (std::vector<int>::size_type i = lastIndex; i < s.second.size(); i++) 
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

    if(rsi[4] >= 70) cout <<"���ż� �������� �ŵ��� ��õ �帳�ϴ�!"<<endl;
    else if(rsi[4] <= 30) cout <<"���ŵ� �������� �ż��� ��õ �帳�ϴ�!"<<endl;


    if(rsi[0] <= rsi[4])
        cout << "�ش� �ֽ��� ��� �߼��� �ֽ��ϴ�!" << endl;
    else
        cout << "�ش� �ֽ��� �϶� �߼��� �ֽ��ϴ�!" << endl;

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
    cout << "�ֱ� 6������ ������� " << fallRate << "% �̻� �϶��� ������??" << endl;
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
    cout<<"�̸� : ";
    cin>>name;
    cout<<"���¹�ȣ : ";
    cin>>ID;
    cout<<"��й�ȣ : ";
    cin>>password;


    for(vector<account>::size_type i = 0; i<users.size(); i++)
    {
        if(name.compare(users[i]->owner_name)==0 && ID.compare(users[i]->accountID)==0 && password.compare(users[i]->password)==0)
        {
            for(auto const& stocks : users[i]->stockOwned)
            {
                auto const& val = stocks.second;
                cout<<"��� : "<<val->name <<  endl;
                cout<<"���� �ݾ� : " << std::fixed << std::setprecision(0) << val->purchase_amount <<  endl;
                cout<<"û�� �ݾ� : " << std::fixed << std::setprecision(0) << val->evaluation_amount <<  endl;
                cout<<"���� : " << std::fixed << std::setprecision(0) << val->evaluation_amount - val->purchase_amount<< endl;;
                cout << endl;
                users[i]->cash += val->evaluation_amount;                
            }
            users[i]->assetAmount = users[i]->cash;
            users[i]->assetValue = users[i]->cash;
            users[i]->assetReturnRatio = 0;
            users[i]->assetReturnValue = 0;
            users[i]->stockOwned.clear();
            return;
        }
            
    }      
    cout << "�ش� ���´� �˻����� �ʽ��ϴ�" << endl; 
}


void graph(map<string, vector<int>> stockdata){
    int a;
    cout<<"1. �ֱ� �Ѵ޵����� ��ȭ"<<endl;
    cout<<"2. �ֱ� ���� ���� ��ȭ"<<endl;
    cin>>a;
    string c;
    int check=0;
    int end;
    if(a==1){//�Ѵް���
        int arr[30];
        cout<<"��� ����� �ֱ� �Ѵ�ġ �ֽ��� Ȯ���ϰڽ��ϱ�? ";
        cin>>c;
        for(auto const& [key,val] : stockdata){
            if(key==c){
                check++;
                end=val.size()-31;
                int order=0;
                for(int i=val.size()-1; i>=end; --i){
                    arr[order]=val[i];
                    order++;
                }
                break;
            }
        }
        if(check==0){
            cout<<"��ġ�ϴ� ������ �����ϴ�."<<endl<<endl;
        }
        else{
        int com=arr[0]/50;

            for(int i=0; i<30; i++){
                int jump=arr[i]/com;
                for(int j=10; j<jump; j++){
                    cout<<" ";
                }
                cout<<"*"<<arr[i]<<endl;
            }
        }
    }
    else if(a==2){//����ġ
        int arr2[30]={0};
        cout<<"��� ����� �ֱ� ���� ���� �ֽ��� Ȯ���ϰڽ��ϱ�? ";
        cin>>c;
        for(auto const& [key,val] : stockdata){
            if(key==c){
                check++;
                end=val.size()-91;
                int order=0;
                int order2=0;

                for(int i=val.size()-1; i>=end; --i){
                    arr2[order]+=val[i];
                    order2++;
                    if(order2==3){
                        order++;
                        order2=0;
                    }
                }
                break;
            }
        }
        if(check==0){
            cout<<"��ġ�ϴ� ������ �����ϴ�."<<endl<<endl;
        }
        else{
            int com1=arr2[0]/50;

            for(int i=0; i<30; i++){
                int jump1=arr2[i]/com1;
                for(int j=10; j<jump1; j++){
                    cout<<" ";
                }
                cout<<"*"<<arr2[i]/3<<endl;
            }
        }
    }
    else if(cin.fail()){
        cout<<"�߸� �Է��Ͽ����ϴ�."<<endl<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    else{
        cout<<"���� ��ȣ�Դϴ�."<<endl<<endl;
    }
}

void whoBest(vector<account>& users)
{   
    cout << "���ͷ��� ���� User ���" << endl;
    cout << "     Name     |    High    |   Now  " << endl;
    cout << "--------------|------------|--------" << endl;
    sort(users.begin(), users.end(), [](const account &a, const account &b) {return a->assetReturnRatio > b->assetReturnRatio;});
    
    for (const account &user : users) 
    {
        cout.width(14);
        cout << std::left; 
        cout << user->owner_name ; 
        
        cout << "|" ;

        cout.width(12);
        cout << user->accountID ; 
        
        cout << "|" ;

        cout.width(8);
        cout << std::right << user->assetReturnRatio <<"%" << endl;
    }
}

void ranking(vector<account> users){
    multimap<int, Rank> ranker;//int���� �� �ֽ� �ݾ�, Rank���� ��� �̸��� �ֽ� �׸��� �� ����
    vector<account>::size_type count=0;
    for(vector<account>::size_type i = 0; i<users.size();i++){
        Rank a;

        a.people=users[i]->owner_name;
        for(auto const& [key,val] : users[i]->stockOwned){
            a.hold.insert({val->name,val->holding_amount});
        }
        ranker.insert({users[i]->assetValue, a});
    }

    for(auto const& [key,val] : ranker){
        count++;
        cout<<"��: "<<val.people<<endl<<endl;
        cout<<"�� �ݾ�: "<<key<<endl<<endl;;
        for(auto const& [key1,val1] : val.hold){
            cout<<"�ֽ�: "<<key1<<endl;
            cout<<"�� ����: "<<val1<<endl;
            cout<<endl;
        }
        cout<<endl;
        if(users.size()<10){
            if(count==5){
                break;
            }
        }
        else if(users.size()>=10){
            if(count==users.size()/10){
                break;
            }
        }
    }
}

void sell(vector<account> &users, map<string, vector<int>> stockdata){
    int check=0;//�̸�, ���¹�ȣ, ��й�ȣ�� ��ġ�ϴ� ���� ���� ��
    int check2=0;//�ֽ��� ��ġ�ϴ� ���� ���� ��
    string name, ID, password;
    string sellitem;
    cout<<"�̸��� �ۼ��Ͻÿ�.: ";
    cin>>name;
    cout<<"���¹�ȣ�� �ۼ��Ͻÿ�.: ";
    cin>>ID;
    cout<<"��й�ȣ�� �ۼ��Ͻÿ�.: ";
    cin>>password;

    for(vector<account>::size_type i = 0; i<users.size(); i++)
    {
        if(name.compare(users[i]->owner_name)==0 && ID.compare(users[i]->accountID)==0 && password.compare(users[i]->password)==0){
            cout<<"���� ���� ���� �ֽ���"<<endl;
            for(auto& a : users[i]->stockOwned)
            {
                auto& val=a.second;
                cout<<"���: "<<val->name;
                cout<<", ���� ����: "<<val->holding_amount;
                cout<<", ���� �ݾ�: "<<val->current_price<<endl;;
            }
            cout<<endl;
            cout<<"��� �ֽ��� �Ǹ��Ͻðڽ��ϱ�?: ";
            cin>>sellitem;
            for(auto const& [key, val] : users[i]->stockOwned){
                if(sellitem.compare(val->name)==0){
                    check2++;
                    int sellamount;
                    cout<<"�� �ָ� �Ǹ��Ͻðڽ��ϱ�?: ";
                    cin>>sellamount;
                    if(sellamount>val->holding_amount){
                        cout<<"���� ������ �ִ� �������� �� ���� ���� �Ǹ��� �� �����ϴ�."<<endl;
                        break;
                    }
                    else if(cin.fail()){
                        cout<<"�� �� ���� ����"<<endl;
                        break;
                    }
                    else if(sellamount<=0){
                        cout<<"����� �ۼ��� �ֽʽÿ�."<<endl;
                        break;
                    }
                    else{
                        int money;
                        money=sellamount*val->current_price;
                        val->holding_amount=val->holding_amount-sellamount;
                        users[i]->cash+=money;
                        val->purchase_amount =  val->purchase_price * val->holding_amount;
                        val->evaluation_amount = val->current_price * val->holding_amount;
                        users[i]->assetAmount = users[i]->purchaseAmount + users[i]->cash;
                        users[i]->assetValue = users[i]->totalStockValue + users[i]->cash;
                        
                        users[i]->assetReturnRatio = users[i]->assetValue/users[i]->assetAmount;
                        users[i]->assetReturnValue = users[i]->assetValue - users[i]->assetAmount;
                        if(val->holding_amount==0){
                            users[i]->stockOwned.erase(val->name);
                        }
                        break;
                    }
                }
            }


            check++;
            break;
        }
    }
    if(check==0){
        cout<<"��ġ�ϴ� ������ �����ϴ�."<<endl;
    }
    if(check2==0 && check != 0){
        cout<<"������ ���� ���� �ֽ��Դϴ�."<<endl;
    }
}



void buy(vector<account> &users, map<string, vector<int>> stockdata){
    string name, ID, password;
    string buyitem;
    int buy;
    int check=0;
    int check3=0;
    int price=0;
    cout<<"�̸��� �ۼ��Ͻÿ�.: ";

    cin>>name;
    cout<<"���¹�ȣ�� �ۼ��Ͻÿ�.: ";

    cin>>ID;
    cout<<"��й�ȣ�� �ۼ��Ͻÿ�.: ";

    cin>>password;

     for(vector<account>::size_type i = 0; i<users.size(); i++){
        if(name.compare(users[i]->owner_name)==0 && ID.compare(users[i]->accountID)==0 && password.compare(users[i]->password)==0){
            check3++;
            cout<<"���� ���� ���� �ֽ���"<<endl;
            for(auto const& a : users[i]->stockOwned){
                auto const& val=a.second;
                cout<<"���: "<<val->name;
                cout<<", ���� ����: "<<val->holding_amount;
                cout<<", ���� �ݾ�: "<<val->current_price<<endl;;
            }
            cout<<endl;
            cout<<"�����ϰ� ���� �ֽ��� �����Դϱ�?: ";
            cin>>buyitem;
            for(auto const& [key,val]: stockdata){
                if(buyitem.compare(key)==0){
                    check++;
                    price=val.back();
                    cout<<"������: "<<users[i]->cash<<endl;
                    cout<<key<<": "<<price<<endl;
                    cout<<"�� �ָ� �����Ͻðڽ��ϱ�?: ";
                    cin>>buy;
                    price=price*buy;
                    if(users[i]->cash<price){
                        cout<<"�������� �ʰ��Ͽ����ϴ�. ���Ű� �Ұ����մϴ�."<<endl;
                        break;
                    }
                    else if(price<0){
                        cout<<"������ �Է����� �����ּ���."<<endl;
                        break;
                    }
                    else if(cin.fail()){
                        cout<<"�� �� ���� ����"<<endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                        break;
                    }
                    else{
                        users[i]->cash-=price;
                        stock a=new Stock;
                        a->name=buyitem;
                        a->purchase_amount=val.back();
                        a->current_price=val.back();
                        a->purchase_amount=price;
                        a->evaluation_amount=price;
                        a->holding_amount=buy;

                        int check4=0;
                        for(auto const& [key,val] : users[i]->stockOwned){
                            if(buyitem.compare(key)==0){
                                val->holding_amount+=buy;
                                val->purchase_price=(val->purchase_amount+val->current_price*buy)/val->holding_amount;
                                val->purchase_amount=val->purchase_price*val->holding_amount;
                                val->evaluation_amount=val->current_price*val->holding_amount;
                                
                                check4++;
                            }
                        }
                        if(check4==0){
                        users[i]->stockOwned.insert({buyitem,a});
                        }



                        users[i]->purchaseAmount+=a->purchase_amount;
                        users[i]->totalStockValue+=a->evaluation_amount;
                        users[i]->assetAmount=users[i]->purchaseAmount+users[i]->cash;
                        users[i]->assetValue = users[i]->totalStockValue + users[i]->cash;
                        users[i]->assetReturnRatio = users[i]->assetValue/users[i]->assetAmount;
                        users[i]->assetReturnValue = users[i]->assetValue - users[i]->assetAmount;
                        break;
                        
                    }
                }
            }
            if(check==0){
                cout<<"����Ʈ ������ ���Ű� �Ұ����� �ֽ��̰ų� �������� �ʴ� �ֽ��Դϴ�."<<endl;
                break;
            }
        }

     }
     if(check3==0){
        cout<<"��ġ�ϴ� ������ �����ϴ�."<<endl;
     }
}