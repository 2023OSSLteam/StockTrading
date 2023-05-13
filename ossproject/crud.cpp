#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include "data.h"
#include <iomanip>

void menu(){
cout<<"      <�޴�>"      <<endl;
cout<<"C: ȸ������"<<endl;
cout<<"R: ���� ���� ����"<<endl;
cout<<"U: ���� ���� ����"<<endl;
cout<<"D: Ż��"<<endl;
cout<<"q: ����"<<endl;

};

void create(vector<account> *users, map<string, vector<int>> stockdata){//ȸ������

account newN = new Account;

//�⺻
cout<<"�̸��� �ۼ��Ͻÿ�.: ";
cin>>newN->owner_name;

cout<<"���¹�ȣ�� �ۼ��Ͻÿ�.: ";
cin>>newN->accountID;

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

        cout<<"������ �ִ� �ֽ��� �����?: ";
        cin>>newstock->name;


        cout<<"�� �ֽ��� ���� ������?: ";
        cin>>newstock->purchase_price;


        cout<<"�� �ֽ��� ����������?: ";
        cin>>newstock->holding_amount;


        newstock->purchase_amount=newstock->purchase_price*newstock->holding_amount;


        newstock->current_price = stockdata[newstock->name].back();


        newstock->evaluation_amount = newstock->current_price*newstock->holding_amount;



        newN->stockOwned[a]=newstock;

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

users->push_back(newN);//users�� ���� ���� ȸ�� �ֱ�

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
                cout<<val->current_price << std::setprecision(0) <<endl;
                cout<<"���� ����: ";
                cout<<val->holding_amount<<endl;
                cout<<"�򰡱ݾ�: ";
                cout<< std::fixed << val->evaluation_amount<< std::setprecision(0)<<endl;
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
                    cout<<"������ ���¹�ȣ�� �Է��Ͻʽÿ�: "<<endl;
                    cin>>newnum;
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



void delte(){//Ż��



}
