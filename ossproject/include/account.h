#include <iostream>
#include <map>
#include <vector>
#include <string>

struct Stock {
    string name;        // 종목명
    double purchase_price;  // 매입가격
    double current_price;   // 현재가
    double purchase_amount; // 매입금액
    double evaluation_amount; // 평가금액
    int holding_amount;   // 보유수량

};

struct Account {
	string owner_name; // 이름
	string accountID; // 계좌번호
	string password; // 계좌 비밀번호
	vector<string> stock_list// 보유 주식 목록
	map<string, Stock> stockOwned; // 보유 주식 데이터

	int purchaseAmount = 0; // 매입 금액
	int totalStockValue = 0; //
	int asset = 0; // 총 자산
	int cash = 0; // 예수금
	int assetReturnRatio = 0; // 계좌 수익률
	int assetReturnValue = 0; // 계좌 수익

	Account(string name, string ID, string password) 
	{
		string owner_name = name;
		string accountID = ID;
		string password = password;
	}
	~Account() {}
};



using account = Account*;
