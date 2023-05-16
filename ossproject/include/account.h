#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Stock {
    string name;        // 종목명
    double purchase_price;  // 매입가격
    double current_price;   // 현재가
    double purchase_amount; // 매입금액
    double evaluation_amount; // 평가금액
    int holding_amount;   // 보유수량

};
using stock = Stock* ;

struct Account {
	string owner_name; // 이름
	string accountID; // 계좌번호
	string password; // 계좌 비밀번호
	map<string, stock> stockOwned; // 보유 주식 데이터

	int purchaseAmount = 0; // 매입 금액
	int totalStockValue = 0; // 평가 금액
	
	int assetAmount = 0; // 총 매입 자산
	int assetValue = 0; // 총 평가 자산
	int cash = 0; // 예수금
	double assetReturnRatio = 0; // 계좌 수익률
	int assetReturnValue = 0; // 계좌 수익
	~Account() {}
};



using account = Account*;
