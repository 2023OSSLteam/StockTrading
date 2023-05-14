#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include "data.h"


void menu(){
cout<<"      <메뉴>      "<<endl;
cout<<"C: 회원가입"<<endl;
cout<<"R: 나의 정보 보기"<<endl;
cout<<"U: 나의 정보 수정"<<endl;
cout<<"D: 탈퇴"<<endl;
cout<<"q: 종료"<<endl;

};

void create(vector<account> &users, map<string, vector<int>> stockdata){//회원가입

account newN=new Account;

//기본

    
    cout<<"이름을 작성하시오.: ";
    cin>>newN->owner_name;
  


while(1){
    int b=0;
    cout<<"계좌번호를 작성하시오.: ";
    cin>>newN->accountID;
    for(int i=0; i<users.size() ; i++){
        if(users[i]->accountID.compare(newN->accountID)==0){
            cout<<"동일한 계좌번호가 있습니다. 다시 입력하세요."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            b++;
        }
    }
    if(b==0){
        break;
    }
}

cout<<"계좌 비밀번호를 작성하시오.: ";
cin>>newN->password;

cout<<"예수금은 얼마입니까?";
cin>>newN->cash;


//stock
char y_n;
cout<<"가지고 있는 주식은 있습니까?(예: y 아니요: n)";
cin>>y_n;



    while(y_n=='Y' || y_n=='y'){
        stock newstock= new Stock;
        string a;//회사 이름

        while(1){
            int b=0;
            cout<<"가지고 있는 주식의 기업은?: ";
            cin>>newstock->name;
            for(auto const& a : stockdata){
                auto const& val=a.first;
                if((val).compare(newstock->name)==0){
                    b++;
                    break;
                }
            }

            if(b!=0){
                break;
            }
            cout<<"저희가 가지고 있지 않는 주식입니다."<<endl;
        }


        cout<<"그 주식의 매입 가격은?: ";
        cin>>newstock->purchase_price;


        cout<<"그 주식의 보유수량은?: ";
        cin>>newstock->holding_amount;


        newstock->purchase_amount=newstock->purchase_price*newstock->holding_amount;


        newstock->current_price = stockdata[newstock->name].back();


        newstock->evaluation_amount = newstock->current_price*newstock->holding_amount;



        newN->stockOwned[newstock->name]=newstock;

        while(1){
            cout<<"그 외의 주식은 더 있습니까?(예:y 아니오:n)";
            cin>>y_n;

            if(y_n=='N' || y_n=='n'){
                break;
            }
            else if(y_n=='y' || y_n=='Y'){
                break;
            }
            else if(cin.fail()){
                cout<<"잘못입력하였습니다."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
            }
            else{
                cout<<"잘못입력하였습니다."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
            }
        }
        if(y_n=='N' || y_n=='n'){
            break;
        }
cin.clear();
cin.ignore(256,'\n');
}
//stock를 이용하여 나머지 account채우기

for(auto const& a : newN->stockOwned){
    auto const& key=a.first;
    auto const& val=a.second;
    newN->purchaseAmount += val->purchase_amount ;
    newN->totalStockValue += val->evaluation_amount;
    }
newN->assetAmount = newN->purchaseAmount + newN->cash;
newN->assetValue = newN->totalStockValue + newN->cash;
            
newN->assetReturnRatio = newN->assetValue/newN->assetAmount;
newN->assetReturnValue = newN->assetValue - newN->assetAmount;

users.push_back(newN);//users에 새로 만든 회원 넣기

}



void read(vector<account> users){//자기 정보 읽기
    string name;
    string number;//계좌번호
    string pass;//패스워드
    int y_n=0;

    cout<<"서명, 계좌번호, 계좌비밀번호를 작성하시오."<<endl;
    cout<<"서명: ";
    cin>>name;
    cout<<"계좌번호: ";
    cin>>number;
    cout<<"계좌비밀번호: ";  
    cin>>pass;


    for(int i=0; i<users.size(); i++){

        if(users[i]->owner_name.compare(name)==0 && users[i]->accountID.compare(number)==0 && users[i]->password.compare(pass)==0){

            cout<<"user: "+users[i]->owner_name<<endl;
            cout<<"계좌번호: "+users[i]->accountID<<endl;
            cout<<"예수금: "<<users[i]->cash<<endl;
            for(auto const& a : users[i]->stockOwned){
                
                auto const& val=a.second;
                cout<<"기업: ";
                cout<<val->name<<endl;
                cout<<"현재 금액: ";
                cout<<val->current_price<<endl;
                cout<<"보유 수량: ";
                cout<<val->holding_amount<<endl;
                cout<<"평가금액: ";
                cout.precision(0);
                cout<<fixed<<val->evaluation_amount<<endl;
            }
            y_n++;
            break;
        }
    }

    if(y_n == 0){
        cout<<"정보를 잘못 입력하였거나 없는 정보입니다. 다시 시도해주세요."<<endl;
    }
}


void update(vector<account> users){//기존의 계좌에서 예수금이 충분한 계좌로 이동
    string name, num, password, newnum, newpassword;
    int check;//예수금 더할지 말지
    int number;
    int move;
    int out=0;
    while(1){
        cout<<"0. 나가기"<<endl<<"1.예수금 이동"<<endl<<"2.계좌변경"<<endl<<"무엇을 하시겠습니까?: ";
        cin>>number;
        if(number==1){
            cout<<"이름을 입력하시오"<<endl;
            cin>>name;
            cout<<"계좌번호를 입력하십시오: "<<endl;
            cin>>num;
            cout<<"계좌비밀번호를 입력하시오: "<<endl;
            cin>>password;

            for(int i=0; i<users.size();i++){
                if(users[i]->owner_name.compare(name)==0 && users[i]->accountID.compare(num)==0 && users[i]->password.compare(password)==0){
                    cout<<"금액을 추가할 것입니까? 뺄 것입니까?(추가:1, 제거:0)";
                    cin>>check;
                    if(check==1){
                        cout<<"얼마를 넣을 것입니까?";
                        cin>>move;
                        if(move<0){
                            cout<<"음수를 넣을 수 없습니다. 양수를 입력하세요."<<endl;
                            break;
                        }
                        else if(move==0){
                            cout<<"0원을 넣을 수 없습니다. 양수를 입력하세요."<<endl;
                            break;
                        }
                        else if(move>0){
                            users[i]->cash+=move;
                            cout<<"충전되었습니다."<<endl;
                            break;
                        }
                        else if(cin.fail()){
                            cout<<"숫자를 입력하시오."<<endl;
                            break;
                        }
                        else{
                            cout<<"알 수 없는 오류"<<endl;
                            break;
                        }
                    }
                    else if(check==0){
                        cout<<"얼마를 이동하시겠습니까?(예수금:"+users[i]->cash<<"): ";
                        cin>>move;
                        if(move>users[i]->cash){
                            cout<<"금액을 초과하였습니다."<<endl;
                            break;
                        }
                        else if(move<0){
                            cout<<"양수를 넣어야 합니다."<<endl;
                            break;
                        }
                        else if(cin.fail()){
                            cout<<"정수가 아닌 수, 혹은 문자는 입력받을 수 없습니다."<<endl;
                            break;
                        }
                        else if(move>=0 && move<=users[i]->cash){
                            users[i]->cash=users[i]->cash-move;
                            break;
                        }
                        else{
                            cout<<"알 수 없는 오류"<<endl;
                            break;
                        }
                    }
                    else if(cin.fail()){
                        cout<<"숫자를 입력하시오."<<endl;
                    }
                    else{
                        cout<<"알 수 없는 오류"<<endl;
                    }


                    
                }

            }
        }
        else if(number==2){
            cout<<"이름을 입력하시오"<<endl;
            cin>>name;
            cout<<"계좌번호를 입력하십시오: "<<endl;
            cin>>num;
            cout<<"계좌비밀번호를 입력하시오: "<<endl;
            cin>>password;

            for(int i=0; i<users.size(); i++){
                if(users[i]->owner_name.compare(name)==0 && users[i]->accountID.compare(num)==0 && users[i]->password.compare(password)==0){
                    while(1){
                        int b=0;
                        cout<<"변경할 계좌번호를 입력하십시오: "<<endl;
                        cin>>newnum;
                        for(int i=0; i<users.size() ; i++){
                            if(users[i]->accountID.compare(newnum)==0){
                                cout<<"동일한 계좌번호가 있습니다. 다시 입력하세요."<<endl;
                                cin.clear();
                                cin.ignore(256,'\n');
                                b++;
                            }
                        }
                        if(b==0){
                            break;
                        }
                    
                    }
                    
                    
                    cout<<"변경할 계좌비밀번호를 입력하시오: "<<endl;
                    cin>>newpassword;
                    int newcash;
                    cout<<"변경할 계좌에 예수금은 얼마인가?"<<endl;
                    cin>>newcash;

                    string a= "./data/userdata/"+users[i]->accountID;
                    a+=".txt";

                    const char *b= a.c_str();
                    //cout<<remove(b); 

                    users[i]->accountID=newnum;
                    users[i]->password=newpassword;
                    users[i]->cash+=newcash;
                    break;
                }
                else{
                    cout<<"정보가 없습니다."<<endl;
                }
            }
        }
        else if(cin.fail()){
            cout<<"잘못입력하였습니다."<<endl;
            cin.clear();
            cin.ignore(256,'\n');

        }
        else if(number==0){
            break;
        }
        else{
            cout<<"잘못입력하였습니다."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
        }
    cout<<"끝내시겠습니까?(예:1 아니오:0): ";
    cin>>out;
    if(out==1){
        break;
    }
    }

}



void del(vector<account> &users){//탈퇴
    string name, ID, password;
    cout<<"이름을 작성하시오.: ";
    cin>>name;
    cout<<"계좌번호를 작성하시오.: ";
    cin>>ID;
    cout<<"비밀번호를 작성하시오.: ";
    cin>>password;

    int check=0;
    for(int i=0; i<users.size(); i++){
        int y_n;
        cout<<"정말로 탈퇴하시겠습니까?(예:1 아니오:0): ";
        cin>>y_n;
        if(y_n==1){
            if(name.compare(users[i]->owner_name)==0 && ID.compare(users[i]->accountID)==0 && password.compare(users[i]->password)==0){
                users.erase(users.begin()+i);
                string a= "./data/userdata/"+users[i]->accountID;
                a+=".txt";

                const char *b= a.c_str();
                //cout<<remove(b); 
                cout<<"삭제되었습니다."<<endl;
                check++;
                break;
            }
        }
        else{
            cout<<"취소되었습니다."<<endl;
            break;
        }
    }

    if(check==0){
        cout<<"일치하는 정보가 없습니다."<<endl;
    }
}


void save(vector<account> users){
    string a;
    ofstream user("./data/userdata/user.txt", ios_base::in);
    for(int i=0; i<users.size();i++){
        user<<users[i]->owner_name<<"  ";
        user<<users[i]->accountID<<"  ";
        user<<users[i]->password<<"  ";
        user<<users[i]->cash<<endl;
        ofstream ID("./data/userdata/"+users[i]->accountID+".txt");
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
