from pykrx import stock
import pandas as pd
from datetime import datetime, timedelta

# 날짜 설정
end_date = datetime.now().strftime('%Y%m%d')
start_date = (datetime.now() - timedelta(days=180)).strftime('%Y%m%d')

# 코스피 200 종목 코드 가져오기
tickers = stock.get_index_portfolio_deposit_file("1028")

# 종목별 종가 데이터 가져오기
df_list = []
for ticker in tickers:
    print(ticker)
    df = stock.get_market_ohlcv_by_date(start_date, end_date, ticker)
    df = df[['종가']]
    df.columns = [stock.get_market_ticker_name(ticker)]
    df_list.append(df)

# 데이터 합치기
result = pd.concat(df_list, axis=1)

# csv 파일로 저장
result.to_csv('kospi200.csv')