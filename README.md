# Stock Trading System  
Stock Trading System란 주식 거래 시스템으로 사용자의 계좌 포트폴리오를 관리하고  
주식 데이터, 보조 지표, 뉴스 데이터를 제공합니다

## Database

- **Account Strucuture**  
  
| Data       | Variable         | Type   | Description |
|------------|------------------|--------|-------------|
| 소유주 이름      | owner_name | string | 계좌 소유자의 이름 *e.g. 홍길동* |
| 계좌번호    | accountID | string |시스템 상에 등록된 사용자의 계좌번호 *e.g. 1234-5678* |
| 계좌 비밀번호 | password | string |시스템 상에 등록된 사용자의 계좌 비밀번호 *e.g. 1234*|
| 보유 주식 데이터 | stockOwned | map    | 소유주의 보유 종목명, 종목 주가, 각 종목 수익률, 각 종목 매입 단가, 각 평가 금액을 담은 데이터 set|
| 매입 금액 | purchaseAmount | int    | 총 주식 매입 금액 = 보유 주식 데이터의 각 종목 평균 단가의 합 |
| 평가 금액 | totalStockValue  | int    | 총 주식 평가 금액 = 보유 주식 데이터의 각 종목 평가 금액의 합 |
| 총 자산 | asset  | int    | 평가 금액과 예수금을 합한 값 |
| 예수금 | cash | int    | 현재 잔여 현금 |
| 계좌 수익률 | assetReturnRatio | float  | 매입 금액과 평가 금액의 가격 비율 *e.g. 14%*|
| 계좌 수익 | assetReturnValue | int    | 평가 금액 - 매입 금액 *e.g. 124,000*|

- **stockOwned Map** 

- **Stock Data**  
## Function of Stock Trading

### CRUD

- C: 예금주, 보유 주식, 예수금, 계좌 비밀번호를 넣게 만든다.

- R: 현재 가입한 사람들의 정보를 보인다.

- U: 사용자인지 관리자인지 묻고 사용자일 경우 계좌 비밀번호나 일부 정보만 바꿀 수 있게 하고 관리자라면 관리자 전용 비밀번호를 작성하게 하고 맞으면 몇몇 기능을 추가로 수정할 수 있게 한다.

- D: 탈퇴 시 그 정보를 지운다.

- S: 예금주들 정보 저장

- L: 예금주들 정보 로드

### Extra Function

- 구매 기능: 특정 주식을 구매할 수 있게 만들고 구매하면 그 구매한 크기만큼 보유 주식의 크기를 변환시킨다.
<img src="https://github.com/2023OSSLteam/StockTrading/blob/main/img/%EA%B5%AC%EB%A7%A4.png" width="30%" height="20%">

- 판매 기능: 특정 주식을 판매할 수 있게 만들고 판매하면 그 판매한 크기만큼 보유 주식의 크기 및 예수금 등을 변환시킨다.
<img src="https://github.com/2023OSSLteam/StockTrading/blob/main/img/%ED%8C%90%EB%A7%A4.png" width="30%" height="20%">

- 그래프 보기 기능: 현재 시간 때에서 1년 전까지 주식의 변동을 그래프로 볼 수 있게 한다.
<img src="https://github.com/2023OSSLteam/StockTrading/blob/main/img/chart1.png" width="40%" height="30%">

- 우수고객확인기능: 가장 보유 주식이 많은 사람 상위 10%를 순서대로 나열시킨다.
<img src="https://github.com/2023OSSLteam/StockTrading/blob/main/img/image.png" width="30%" height="20%">

- 일괄 청산 : 해당 유저의 모든 주식을 청산 후 자산에 
- 주식 데이터 업데이트: 하루가 지남에 따라 변동된 주가를 반영한다.
- 보조 지표: 현재 RSI 지표 출력
- 포트폴리오 비중 출력: 자신이 보유하고 있는 종목들의 비중들을 나타냄
- 고점 대비 과대 낙폭 주식 검색: 고점 대비 크게 떨어진 주식들을 출력한다.

## Team Role
### 김성은
- Wiki 편집
- 포트폴리오 비중 출력
- 주식 데이터 업데이트
- 보조 지표 RSI
- 일괄 청산 기능
- 고점 대비 과대 낙폭 주식 검색
### 김성지
- 주식에 영향을 줄 수 있는 사건 사고 검색
- 주식 차트 생성
- CRUD 및 로드 세이브
- 가상 주식 판매 및 구매
- 우수 고객 정리

## Development Environment
<img src="https://img.shields.io/badge/git-F05032?style=for-the-badge&logo=c%2B%2B&logoColor=white">
<img src="https://img.shields.io/badge/visualstudiocode-007ACC?style=for-the-badge&logo=c%2B%2B&logoColor=white">

## Development Language
<img src="https://img.shields.io/badge/c++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white">

## About us
안녕하세요 20학번 김성지입니다.

AI Quant Developer를 꿈꾸는 20학번 김성은입니다!!    
OSS Project 파이팅!!  
  
<a href="https://github.com/immanuelk1m">
<img src="https://img.shields.io/badge/github-181717?style=for-the-badge&logo=c%2B%2B&logoColor=white">
</a>
