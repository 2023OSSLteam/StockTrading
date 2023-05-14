#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include "data.h"


void menu(){
cout<<"      <�޴�>      "<<endl;
cout<<"C: ȸ������"<<endl;
cout<<"R: ���� ���� ����"<<endl;
cout<<"U: ���� ���� ����"<<endl;
cout<<"D: Ż��"<<endl;
cout<<"q: ����"<<endl;

};

void create(vector<account> &users, map<string, vector<int>> stockdata){//ȸ������

account newN=new Account;

//�⺻

    
    cout<<"�̸��� �ۼ��Ͻÿ�.: ";
    cin>>newN->owner_name;
  


while(1){
    int b=0;
    cout<<"���¹�ȣ�� �ۼ��Ͻÿ�.: ";
    cin>>newN->accountID;
    for(int i=0; i<users.size() ; i++){
        if(users[i]->accountID.compare(newN->accountID)==0){
            cout<<"������ ���¹�ȣ�� �ֽ��ϴ�. �ٽ� �Է��ϼ���."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            b++;
        }
    }
    if(b==0){
        break;
    }
}

cout<<"���� ��й�ȣ�� �ۼ��Ͻÿ�.: ";
cin>>newN->password;

cout<<"�������� ���Դϱ�?";
cin>>newN->cash;


//stock
char y_n;
cout<<"������ �ִ� �ֽ��� �ֽ��ϱ�?(��: y �ƴϿ�: n)";
cin>>y_n;



    while(y_n=='Y' || y_n=='y'){
        stock newstock= new Stock;
        string a;//ȸ�� �̸�

        while(1){
            int b=0;
            cout<<"������ �ִ� �ֽ��� �����?: ";
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
            cout<<"���� ������ ���� �ʴ� �ֽ��Դϴ�."<<endl;
        }


        cout<<"�� �ֽ��� ���� ������?: ";
        cin>>newstock->purchase_price;


        cout<<"�� �ֽ��� ����������?: ";
        cin>>newstock->holding_amount;


        newstock->purchase_amount=newstock->purchase_price*newstock->holding_amount;


        newstock->current_price = stockdata[newstock->name].back();


        newstock->evaluation_amount = newstock->current_price*newstock->holding_amount;



        newN->stockOwned[newstock->name]=newstock;

        while(1){
            cout<<"�� ���� �ֽ��� �� �ֽ��ϱ�?(��:y �ƴϿ�:n)";
            cin>>y_n;

            if(y_n=='N' || y_n=='n'){
                break;
            }
            else if(y_n=='y' || y_n=='Y'){
                break;
            }
            else if(cin.fail()){
                cout<<"�߸��Է��Ͽ����ϴ�."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
            }
            else{
                cout<<"�߸��Է��Ͽ����ϴ�."<<endl;
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
//stock�� �̿��Ͽ� ������ accountä���

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

users.push_back(newN);//users�� ���� ���� ȸ�� �ֱ�

}



void read(vector<account> users){//�ڱ� ���� �б�
    string name;
    string number;//���¹�ȣ
    string pass;//�н�����
    int y_n=0;

    cout<<"����, ���¹�ȣ, ���º�й�ȣ�� �ۼ��Ͻÿ�."<<endl;
    cout<<"����: ";
    cin>>name;
    cout<<"���¹�ȣ: ";
    cin>>number;
    cout<<"���º�й�ȣ: ";  
    cin>>pass;


    for(int i=0; i<users.size(); i++){

        if(users[i]->owner_name.compare(name)==0 && users[i]->accountID.compare(number)==0 && users[i]->password.compare(pass)==0){

            cout<<"user: "+users[i]->owner_name<<endl;
            cout<<"���¹�ȣ: "+users[i]->accountID<<endl;
            cout<<"������: "<<users[i]->cash<<endl;
            for(auto const& a : users[i]->stockOwned){
                
                auto const& val=a.second;
                cout<<"���: ";
                cout<<val->name<<endl;
                cout<<"���� �ݾ�: ";
                cout<<val->current_price<<endl;
                cout<<"���� ����: ";
                cout<<val->holding_amount<<endl;
                cout<<"�򰡱ݾ�: ";
                cout.precision(0);
                cout<<fixed<<val->evaluation_amount<<endl;
            }
            y_n++;
            break;
        }
    }

    if(y_n == 0){
        cout<<"������ �߸� �Է��Ͽ��ų� ���� �����Դϴ�. �ٽ� �õ����ּ���."<<endl;
    }
}


void update(vector<account> users){//������ ���¿��� �������� ����� ���·� �̵�
    string name, num, password, newnum, newpassword;
    int check;//������ ������ ����
    int number;
    int move;
    int out=0;
    while(1){
        cout<<"0. ������"<<endl<<"1.������ �̵�"<<endl<<"2.���º���"<<endl<<"������ �Ͻðڽ��ϱ�?: ";
        cin>>number;
        if(number==1){
            cout<<"�̸��� �Է��Ͻÿ�"<<endl;
            cin>>name;
            cout<<"���¹�ȣ�� �Է��Ͻʽÿ�: "<<endl;
            cin>>num;
            cout<<"���º�й�ȣ�� �Է��Ͻÿ�: "<<endl;
            cin>>password;

            for(int i=0; i<users.size();i++){
                if(users[i]->owner_name.compare(name)==0 && users[i]->accountID.compare(num)==0 && users[i]->password.compare(password)==0){
                    cout<<"�ݾ��� �߰��� ���Դϱ�? �� ���Դϱ�?(�߰�:1, ����:0)";
                    cin>>check;
                    if(check==1){
                        cout<<"�󸶸� ���� ���Դϱ�?";
                        cin>>move;
                        if(move<0){
                            cout<<"������ ���� �� �����ϴ�. ����� �Է��ϼ���."<<endl;
                            break;
                        }
                        else if(move==0){
                            cout<<"0���� ���� �� �����ϴ�. ����� �Է��ϼ���."<<endl;
                            break;
                        }
                        else if(move>0){
                            users[i]->cash+=move;
                            cout<<"�����Ǿ����ϴ�."<<endl;
                            break;
                        }
                        else if(cin.fail()){
                            cout<<"���ڸ� �Է��Ͻÿ�."<<endl;
                            break;
                        }
                        else{
                            cout<<"�� �� ���� ����"<<endl;
                            break;
                        }
                    }
                    else if(check==0){
                        cout<<"�󸶸� �̵��Ͻðڽ��ϱ�?(������:"+users[i]->cash<<"): ";
                        cin>>move;
                        if(move>users[i]->cash){
                            cout<<"�ݾ��� �ʰ��Ͽ����ϴ�."<<endl;
                            break;
                        }
                        else if(move<0){
                            cout<<"����� �־�� �մϴ�."<<endl;
                            break;
                        }
                        else if(cin.fail()){
                            cout<<"������ �ƴ� ��, Ȥ�� ���ڴ� �Է¹��� �� �����ϴ�."<<endl;
                            break;
                        }
                        else if(move>=0 && move<=users[i]->cash){
                            users[i]->cash=users[i]->cash-move;
                            break;
                        }
                        else{
                            cout<<"�� �� ���� ����"<<endl;
                            break;
                        }
                    }
                    else if(cin.fail()){
                        cout<<"���ڸ� �Է��Ͻÿ�."<<endl;
                    }
                    else{
                        cout<<"�� �� ���� ����"<<endl;
                    }


                    
                }

            }
        }
        else if(number==2){
            cout<<"�̸��� �Է��Ͻÿ�"<<endl;
            cin>>name;
            cout<<"���¹�ȣ�� �Է��Ͻʽÿ�: "<<endl;
            cin>>num;
            cout<<"���º�й�ȣ�� �Է��Ͻÿ�: "<<endl;
            cin>>password;

            for(int i=0; i<users.size(); i++){
                if(users[i]->owner_name.compare(name)==0 && users[i]->accountID.compare(num)==0 && users[i]->password.compare(password)==0){
                    while(1){
                        int b=0;
                        cout<<"������ ���¹�ȣ�� �Է��Ͻʽÿ�: "<<endl;
                        cin>>newnum;
                        for(int i=0; i<users.size() ; i++){
                            if(users[i]->accountID.compare(newnum)==0){
                                cout<<"������ ���¹�ȣ�� �ֽ��ϴ�. �ٽ� �Է��ϼ���."<<endl;
                                cin.clear();
                                cin.ignore(256,'\n');
                                b++;
                            }
                        }
                        if(b==0){
                            break;
                        }
                    
                    }
                    
                    
                    cout<<"������ ���º�й�ȣ�� �Է��Ͻÿ�: "<<endl;
                    cin>>newpassword;
                    int newcash;
                    cout<<"������ ���¿� �������� ���ΰ�?"<<endl;
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
                    cout<<"������ �����ϴ�."<<endl;
                }
            }
        }
        else if(cin.fail()){
            cout<<"�߸��Է��Ͽ����ϴ�."<<endl;
            cin.clear();
            cin.ignore(256,'\n');

        }
        else if(number==0){
            break;
        }
        else{
            cout<<"�߸��Է��Ͽ����ϴ�."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
        }
    cout<<"�����ðڽ��ϱ�?(��:1 �ƴϿ�:0): ";
    cin>>out;
    if(out==1){
        break;
    }
    }

}



void del(vector<account> &users){//Ż��
    string name, ID, password;
    cout<<"�̸��� �ۼ��Ͻÿ�.: ";
    cin>>name;
    cout<<"���¹�ȣ�� �ۼ��Ͻÿ�.: ";
    cin>>ID;
    cout<<"��й�ȣ�� �ۼ��Ͻÿ�.: ";
    cin>>password;

    int check=0;
    for(int i=0; i<users.size(); i++){
        int y_n;
        cout<<"������ Ż���Ͻðڽ��ϱ�?(��:1 �ƴϿ�:0): ";
        cin>>y_n;
        if(y_n==1){
            if(name.compare(users[i]->owner_name)==0 && ID.compare(users[i]->accountID)==0 && password.compare(users[i]->password)==0){
                users.erase(users.begin()+i);
                string a= "./data/userdata/"+users[i]->accountID;
                a+=".txt";

                const char *b= a.c_str();
                //cout<<remove(b); 
                cout<<"�����Ǿ����ϴ�."<<endl;
                check++;
                break;
            }
        }
        else{
            cout<<"��ҵǾ����ϴ�."<<endl;
            break;
        }
    }

    if(check==0){
        cout<<"��ġ�ϴ� ������ �����ϴ�."<<endl;
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
