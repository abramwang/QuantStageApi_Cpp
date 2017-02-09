# 子午投资

# PT_QuantPlatform开发文档

|          |               |          |                 |
| -------- | ------------- | -------- | --------------- |
| **研制单位** | 子午投资管理有限公司    | **应用单位** |                 |
| **项目名称** |               | **项目编号** |                 |
| **文档名称** | PT_QuantPform | **文档编号** |                 |
| **文档状态** | 草稿            | **文档版本** | 0.3.2.3.release |
| **提交**   |               | **提交日期** | 2016年10月13日     |
| **审批**   |               | **审批日期** |                 |
|          |               |          |                 |

------

​                                                                          **修改记录**

| 文档版本               | 文档状态    | 修订日期       | 修订者  | 修订内容               |
| ------------------ | ------- | ---------- | ---- | ------------------ |
| 1.0.0.1012.release | Created | 2016-10-12 | 王商   |                    |
| 1.0.0.1013.release | Added   | 2016-10-13 | 王商   | 添加各参数说明            |
| 0.3.2.3            | Added   | 2016-12-16 | 王商   | 修改版本号；增添因子说明；新增接口。 |
|                    |         |            |      |                    |
|                    |         |            |      |                    |
|                    |         |            |      |                    |
|                    |         |            |      |                    |
|                    |         |            |      |                    |

文档状态标识：Created-Added-Modified-Deleted







[TOC]

# 1 行情接口

## 1.1 系统构架

暂略

## 1.2 开发包文件结构

暂略

## 1.3 访问回调时序图

暂略

## 1.4创建回调函数实例

```c++
class MarketClient : public GetDataSpi
{
private:
	GD_ErrorType m_err;
	PT_QuantPlatform::GetDataApi* m_api;
	vector<TDF_CODE*> m_allCode;
	TradeClient* m_tclient;
public:
//	void stressTesting();
public:
	virtual void OnRecvCode(TDF_CODE* pCode, int codeNum, TDF_OPTION_CODE* pOptionCode, int optionCodeNum)
	{
		cout << codeNum << endl;
	};		//代码表

	virtual void OnRecvMarket(TDF_MARKET_DATA* pMarket){};     								//行情
	virtual void OnRecvFuture(TDF_FUTURE_DATA* pFuture){};									//期货
	virtual void OnRecvFutureOption(TDF_FUTURE_DATA* pFuture){};							//期权
	virtual void OnRecvIndex(TDF_INDEX_DATA* pIndex){};										//指数
	virtual void OnRecvTransaction(TDF_TRANSACTION* pTransaction){};							//逐笔
	virtual void OnRecvOrderQueue(TDF_ORDER_QUEUE* pOrderQueue){};							//委托队列
	virtual void OnRecvOrder(TDF_ORDER* pOrder){};											//逐笔委托数据（仅深市有）
	virtual void OnRecvGDKLine(GD_Kline_Data* pKline){};									//K线数据

	virtual void OnRecvDayBegin(GD_ISODateTimeType pDate)
	{
		cout << "DayBegin:" << endl;
	};			//接收当前交易日
	virtual void OnRecvDayEnd(GD_ISODateTimeType pDate)
	{
		cout << "DayEnd:" << endl;
	};				//接收到闭市消息

	//每次数据日期变更都会通知这两个接口，无论是历史还是实时
	virtual void OnRecvRspOver(){}

	//系统信息
	virtual void OnConnect(){};
	virtual void OnDisconnect(){};
	virtual void OnReconnectStatus(bool successed){};

	virtual void OnRecvDataTimeless(GD_Stock_Timeliness_Notification* pData){};		//数据时效性状态切换通知，通过这个
	virtual void OnError(string error){};	//错误信息


public:
	MarketClient(TradeClient* tClient){};
	~MarketClient(){};
};
```

## 1.5 获取行情连接对象实例

```c++
API_EXPORT PT_QuantPlatform::GetDataApi* CreateGetDataApi(PT_QuantPlatform::GetDataSpi* spi, bool autoRecon, int reconTimeOut, bool autoReq = false, PT_QuantPlatform::TradeDataApi* tApi = NULL, bool enableLog = true);
```

| 参数           | 类型                              | 说明                                       |
| ------------ | ------------------------------- | ---------------------------------------- |
| spi          | PT_QuantPlatform::GetDataSpi*   | 自定义的回调类的实例对象指针                           |
| autoRecon    | bool                            | 是否断线后自动连接                                |
| reconTimeOut | int                             | 断线重连重试时间间隔，单位毫秒                          |
| autoReq      | bool                            | 用标识自动重连后，是否自动发送上一个请求；默认值为*false*。        |
| tApi         | PT_QuantPlatform::TradeDataApi* | 交易对象实例指针，在使用模拟引擎撮合时，必须把交易对象实例指针传进来，否则将没有行情进行撮合处理；默认值为*NULL*。 |
| enableLog    | bool                            | 是否开启日志功能；默认值为*true*。                     |
|              |                                 |                                          |

## 1.6 释放行情连接对象实例

```c++
API_EXPORT void DelGetDataApi(PT_QuantPlatform::GetDataApi* pAPI);
```

| 参数   | 类型                            | 说明            |
| ---- | ----------------------------- | ------------- |
| pAPI | PT_QuantPlatform::GetDataApi* | 需要释放的行情对象实例指针 |
|      |                               |               |

## 1.7 行情Spi参数说明



### 1.7.1 代码表获取

登录成功后即会马上调用该回调。

```c++
void OnRecvCode(TDF_CODE* pCode, int codeNum, TDF_OPTION_CODE* pOptionCode, int optionCodeNum)；
```

| 参数            | 类型               | 说明   |
| ------------- | ---------------- | ---- |
| pCode         | TDF_CODE*        | 股票代码 |
| codeNum       | int              | 股票数量 |
| pOptionCode   | TDF_OPTION_CODE* | 期权代码 |
| optionCodeNum | int              | 期权数量 |
|               |                  |      |

TDF_CODE 各项参数说明：

| 参数名称       | 参数类型     | 说明                    |
| ---------- | -------- | --------------------- |
| szWindCode | char[32] | Wind Code: AG1302.SHF |
| szMarket   | char[8]  | market code: SHF      |
| szCode     | char[32] | original code:ag1302  |
| szENName   | char[32] |                       |
| szCNName   | char[32] | chinese name: 沪银1302  |
| nType      | int      |                       |
|            |          |                       |

TDF_OPTION_CODE 各项参数说明：

| 参数名称                    | 参数类型     | 说明                                       |
| ----------------------- | -------- | ---------------------------------------- |
| basicCode               | TDF_CODE | 股票代码                                     |
| szContractID            | char[32] | 期权合约代码                                   |
| szUnderlyingSecurityID  | char[32] | 标的证券代码                                   |
| chCallOrPut             | char     | 认购认沽C1;认购，则本字段为“C”；若为认沽，则本字段为“P”。        |
| nExerciseDate           | int      | 期权行权日，YYYYMMDD                           |
| chUnderlyingType        | char     | 标的证券类型C3    0-A股 1-ETF (EBS – ETF， ASH – A 股)。 |
| chOptionType            | char     | 欧式美式C1        若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”。 |
| chPriceLimitType        | char     | 涨跌幅限制类型C1 ‘N’表示有涨跌幅限制类型，‘R’表示无涨跌幅限制类型。   |
| nContractMultiplierUnit | int      | 合约单位，经过除权除息调整后的合约单位， 一定是整数。              |
| nExercisePrice          | int      | 期权行权价，经过除权除息调整后的期权行权价，右对齐，精确到厘。          |
| nStartDate              | int      | 期权首个交易日，YYYYMMDD。                        |
| nEndDate                | int      | 期权最后交易日/行权日，YYYYMMDD。                    |
| nExpireDate             | int      | 期权到期日，YYYYMMDD。                          |
|                         |          |                                          |

### 1.7.2 行情

```c++
void OnRecvMarket(TDF_MARKET_DATA* pMarket);
```

| 参数      | 类型               | 说明     |
| ------- | ---------------- | ------ |
| pMarket | TDF_MARKET_DATA* | 行情快照数据 |
|         |                  |        |

TDF_MARKET_DATA各项参数说明：

| 参数名称                 | 参数类型             | 说明            |
| -------------------- | ---------------- | ------------- |
| szWindCode           | char[32]         | 600001.SH     |
| szCode               | char[32]         | 原始Code        |
| nActionDay           | int              | 业务发生日(自然日)    |
| nTradingDay          | int              | 交易日           |
| nTime                | int              | 时间(HHMMSSmmm) |
| nStatus              | int              | 状态            |
| nPreClose            | unsigned int     | 前收盘价          |
| nOpen                | unsigned int     | 开盘价           |
| nHigh                | unsigned int     | 最高价           |
| nLow                 | unsigned int     | 最低价           |
| nMatch               | unsigned int     | 最新价           |
| nAskPrice            | unsigned int[10] | 申卖价           |
| nAskVol              | unsigned int[10] | 申卖量           |
| nBidPrice            | unsigned int[10] | 申买价           |
| nBidVol              | unsigned int[10] | 申买量           |
| nNumTrades           | unsigned int     | 成交笔数          |
| iVolume              | __int64          | 成交总量          |
| iTurnover            | __int64          | 成交总金额         |
| nTotalBidVol         | __int64          | 委托买入量         |
| nTotalAskVol         | __int64          | 委托卖出量         |
| nWeightedAvgBidPrice | unsigned int     | 加权平均委买价格      |
| nWeightedAvgAskPrice | unsigned int     | 加权平均委卖价格      |
| nIOPV                | int              | IOPV净值估值      |
| nYieldToMaturity     | int              | 到期收益率         |
| nHighLimited         | unsigned int     | 涨停价           |
| nLowLimited          | unsigned int     | 跌停价           |
| chPrefix             | char[4]          | 证券信息前缀        |
| nSyl1                | int              | 市盈率1          |
| nSyl2                | int              | 市盈率2          |
| nSD2                 | int              | 升跌2（对比上一笔）    |
|                      |                  |               |

### 1.7.3 期货

```c++
void OnRecvFuture(TDF_FUTURE_DATA* pFuture);
```

| 参数      | 类型               | 说明   |
| ------- | ---------------- | ---- |
| pFuture | TDF_FUTURE_DATA* | 期货数据 |
|         |                  |      |

TDF_FUTURE_DATA 各项参数说明：

| 参数名称             | 参数类型            | 说明             |
| ---------------- | --------------- | -------------- |
| szWindCode       | char[32]        | 600001.SH      |
| szCode           | char[32]        | 原始Code         |
| nActionDay       | int             | 业务发生日(自然日)     |
| nTradingDay      | int             | 交易日            |
| nTime            | int             | 时间(HHMMSSmmm)  |
| nStatus          | int             | 状态             |
| iPreOpenInterest | __int64         | 昨持仓            |
| nPreClose        | unsigned int    | 昨收盘价           |
| nPreSettlePrice  | unsigned int    | 昨结算            |
| nOpen            | unsigned int    | 开盘价            |
| nHigh            | unsigned int    | 最高价            |
| nLow             | unsigned int    | 最低价            |
| nMatch           | unsigned int    | 最新价            |
| iVolume          | __int64         | 成交总量           |
| iTurnover        | __int64         | 成交总金额          |
| iOpenInterest    | __int64         | 持仓总量           |
| nClose           | unsigned int    | 今收盘            |
| nSettlePrice     | unsigned int    | 今结算            |
| nHighLimited     | unsigned int    | 涨停价            |
| nLowLimited      | unsigned int    | 跌停价            |
| nPreDelta        | int             | 昨虚实读           |
| nCurrDelta       | int             | 今虚实度           |
| nAskPrice        | unsigned int[5] | 申卖价            |
| nAskVol          | unsigned int[5] | 申卖量            |
| nBidPrice        | unsigned int[5] | 申买价            |
| nBidVol          | unsigned int[5] | 申买量            |
| lAuctionPrice    | int             | 波动性中断参考价       |
| lAuctionQty      | int             | 波动性中断集合竞价虚拟匹配量 |
|                  |                 |                |

### 1.7.4 期权

```c++
void OnRecvFutureOption(TDF_FUTURE_DATA* pFuture);
```

| 参数      | 类型               | 说明   |
| ------- | ---------------- | ---- |
| pFuture | TDF_FUTURE_DATA* | 期权数据 |
|         |                  |      |

TDF_FUTURE_DATA 各项参数说明：

| 参数名称             | 参数类型            | 说明             |
| ---------------- | --------------- | -------------- |
| szWindCode       | char[32]        | 600001.SH      |
| szCode           | char[32]        | 原始Code         |
| nActionDay       | int             | 业务发生日(自然日)     |
| nTradingDay      | int             | 交易日            |
| nTime            | int             | 时间(HHMMSSmmm)  |
| nStatus          | int             | 状态             |
| iPreOpenInterest | __int64         | 昨持仓            |
| nPreClose        | unsigned int    | 昨收盘价           |
| nPreSettlePrice  | unsigned int    | 昨结算            |
| nOpen            | unsigned int    | 开盘价            |
| nHigh            | unsigned int    | 最高价            |
| nLow             | unsigned int    | 最低价            |
| nMatch           | unsigned int    | 最新价            |
| iVolume          | __int64         | 成交总量           |
| iTurnover        | __int64         | 成交总金额          |
| iOpenInterest    | __int64         | 持仓总量           |
| nClose           | unsigned int    | 今收盘            |
| nSettlePrice     | unsigned int    | 今结算            |
| nHighLimited     | unsigned int    | 涨停价            |
| nLowLimited      | unsigned int    | 跌停价            |
| nPreDelta        | int             | 昨虚实读           |
| nCurrDelta       | int             | 今虚实度           |
| nAskPrice        | unsigned int[5] | 申卖价            |
| nAskVol          | unsigned int[5] | 申卖量            |
| nBidPrice        | unsigned int[5] | 申买价            |
| nBidVol          | unsigned int[5] | 申买量            |
| lAuctionPrice    | int             | 波动性中断参考价       |
| lAuctionQty      | int             | 波动性中断集合竞价虚拟匹配量 |
|                  |                 |                |

### 1.7.5 指数

```c++
void OnRecvIndex(TDF_INDEX_DATA* pIndex);
```

| 参数     | 类型              | 说明   |
| ------ | --------------- | ---- |
| pIndex | TDF_INDEX_DATA* | 指数数据 |
|        |                 |      |

TDF_INDEX_DATA 各项参数说明：

| 参数名称           | 参数类型     | 说明            |
| -------------- | -------- | ------------- |
| szWindCode     | char[32] | 600001.SH     |
| szCode         | char[32] | 原始Code        |
| nActionDay     | int      | 业务发生日(自然日)    |
| nTradingDay    | int      | 交易日           |
| nTime          | int      | 时间(HHMMSSmmm) |
| nOpenIndex     | int      | 今开盘指数         |
| nHighIndex     | int      | 最高指数          |
| nLowIndex      | int      | 最低指数          |
| nLastIndex     | int      | 最新指数          |
| iTotalVolume   | __int64  | 参与计算相应指数的交易数量 |
| iTurnover      | __int64  | 参与计算相应指数的成交金额 |
| nPreCloseIndex | int      | 前盘指数          |
|                |          |               |

### 1.7.6 逐笔

```c++
void OnRecvTransaction(TDF_TRANSACTION* pTransaction);
```

| 参数           | 类型               | 说明     |
| ------------ | ---------------- | ------ |
| pTransaction | TDF_TRANSACTION* | 逐笔成交数据 |
|              |                  |        |

TDF_TRANSACTION 各项参数说明：

| 参数名称           | 参数类型     | 说明                         |
| -------------- | -------- | -------------------------- |
| szWindCode     | char[32] | 600001.SH                  |
| szCode         | char[32] | 原始Code                     |
| nActionDay     | int      | 自然日                        |
| nTime          | int      | 成交时间(HHMMSSmmm)            |
| nIndex         | int      | 成交编号                       |
| nPrice         | int      | 成交价格                       |
| nVolume        | int      | 成交数量                       |
| nTurnover      | int      | 成交金额                       |
| nBSFlag        | int      | 买卖方向(买：'B', 卖：'A', 不明：' ') |
| chOrderKind    | char     | 成交类别                       |
| chFunctionCode | char     | 成交代码                       |
| nAskOrder      | int      | 叫卖方委托序号                    |
| nBidOrder      | int      | 叫买方委托序号                    |
|                |          |                            |

### 1.7.7 委托队列

```c++
 void OnRecvOrderQueue(TDF_ORDER_QUEUE* pOrderQueue);
```

| 参数          | 类型               | 说明     |
| ----------- | ---------------- | ------ |
| pOrderQueue | TDF_ORDER_QUEUE* | 委托队列数据 |
|             |                  |        |

TDF_ORDER_QUEUE 各项参数说明：

| 参数名称       | 参数类型     | 说明                    |
| ---------- | -------- | --------------------- |
| szWindCode | char[32] | 600001.SH             |
| szCode     | char[32] | 原始Code                |
| nActionDay | int      | 自然日                   |
| nTime      | int      | 时间(HHMMSSmmm)         |
| nSide      | int      | 买卖方向('B':Bid 'A':Ask) |
| nPrice     | int      | 委托价格                  |
| nOrders    | int      | 订单数量                  |
| nABItems   | int      | 明细个数                  |
| nABVolume  | int[200] | 订单明细                  |
|            |          |                       |

### 1.7.8 逐笔委托数据

注：仅深市有

```c++
void OnRecvOrder(TDF_ORDER* pOrder);
```

| 参数     | 类型         | 说明           |
| ------ | ---------- | ------------ |
| pOrder | TDF_ORDER* | 逐笔委托数据（仅深市有） |
|        |            |              |

TDF_ORDER 各项参数说明：

| 参数名称           | 参数类型     | 说明                |
| -------------- | -------- | ----------------- |
| szWindCode     | char[32] | 600001.SH         |
| szCode         | char[32] | 原始Code            |
| nActionDay     | int      | 委托日期(YYMMDD)      |
| nTime          | int      | 委托时间(HHMMSSmmm)   |
| nOrder         | int      | 委托号               |
| nPrice         | int      | 委托价格              |
| nVolume        | int      | 委托数量              |
| chOrderKind    | char     | 委托类别              |
| chFunctionCode | char     | 委托代码('B','S','C') |
|                |          |                   |

### 1.7.9 k线数据

```c++
void OnRecvGDKLine(GD_Kline_Data* pKline);
```

| 参数     | 类型             | 说明   |
| ------ | -------------- | ---- |
| pKline | GD_Kline_Data* | k线数据 |
|        |                |      |

GD_Kline_Data 各项参数说明：

| 参数名称       | 参数类型               | 说明                              |
| ---------- | ------------------ | ------------------------------- |
| nType      | GD_CycType         | 周期类型(注：见**数据字典1**)              |
| szCode     | char[32]           | 是否订阅全市场                         |
| szDatetime | char[21]           | 日期和时间类型（格式：yyyy-MM-dd hh:mm:ss） |
| nDate      | unsigned int       | 日期：yyyyMMdd                     |
| nTime      | unsigned int       | 时间：hhmmsszzz                    |
| nOpen      | double             | 开盘价                             |
| nHigh      | double             | 最高价                             |
| nLow       | double             | 最低价                             |
| nClose     | double             | 今收盘                             |
| nPreClose  | double             | 昨日收盘价                           |
| nHighLimit | double             | 涨停价                             |
| nLowLimit  | double             | 跌停价                             |
| iVolume    | unsigned long long | 成交总量                            |
| nTurover   | double             | 成交总额                            |
|            |                    |                                 |

### 1.7.10 模拟时间线确认回调

每次数据日期变更都会通知这两个接口，无论是历史还是实时。

```c++
void OnRecvRspSimulationTimelineConfirmed(GD_SimulationTimelineConfirmed_Rsp* pConfirmed);
```

| 参数         | 类型                                  | 说明        |
| ---------- | ----------------------------------- | --------- |
| pConfirmed | GD_SimulationTimelineConfirmed_Rsp* | 模拟时间线确认回调 |
|            |                                     |           |

### 1.7.11 接收当前交易日

```c++
void OnRecvDayBegin(GD_ISODateTimeType pDate);
```

| 参数    | 类型                 | 说明      |
| ----- | ------------------ | ------- |
| pDate | GD_ISODateTimeType | 当前交易日时间 |
|       |                    |         |

| 类型别名               | 类型       | 描述                                    |
| ------------------ | -------- | ------------------------------------- |
| GD_ISODateTimeType | char[21] | 日期和时间类型 （格式： yyyy - MM - dd hh:mm:ss） |
|                    |          |                                       |

### 1.7.12 接收到闭市消息

```c++
void OnRecvDayEnd(GD_ISODateTimeType pDate);
```

| 参数    | 类型                 | 说明      |
| ----- | ------------------ | ------- |
| pDate | GD_ISODateTimeType | 当前交易日时间 |
|       |                    |         |

| 类型别名               | 类型       | 描述                                   |
| ------------------ | -------- | ------------------------------------ |
| GD_ISODateTimeType | char[21] | 日期和时间类型（格式 ：yyyy - MM - dd hh:mm:ss） |
| char[21]           |          |                                      |

### 1.7.13 数据接受完毕

每次历史数据请求结束都会调用这个接口

```c++
void OnRecvRspOver();
```

### 1.7.14 交易日查询回调

```c++
void OnRspTradingDay(GD_ISODateTimeType* pDay, int dayNum);
```

| 参数     | 类型                 | 说明        |
| ------ | ------------------ | --------- |
| pDay   | GD_ISODateTimeType | 接收当前交易日消息 |
| dayNum | int                | 交易日列表     |
|        |                    |           |

| 类型别名               | 类型       | 描述                                  |
| ------------------ | -------- | ----------------------------------- |
| GD_ISODateTimeType | char[21] | 日期和时间类型（格式：yyyy - MM - dd hh:mm:ss） |
|                    |          |                                     |

### 1.7.15 前复权因子

```c++
void OnRevRestorationFactor(GD_RestorationFactor* factor, int factorNum);
```

| 参数        | 类型                    | 说明     |
| --------- | --------------------- | ------ |
| factor    | GD_RestorationFactor* | 前复权因子  |
| factorNum | int                   | 复权因子列表 |
|           |                       |        |

GD_RestorationFactor 各项参数说明：

| 参数名称                    | 参数类型               | 说明         |
| ----------------------- | ------------------ | ---------- |
| szWindCode              | GD_CodeType        | 证券代码       |
| szExDivDate             | GD_ISODateTimeType | 除息除权日      |
| nPerCashDiv             | double             | 每股派现       |
| nPerShareDivRatio       | double             | 每股送股比例     |
| nPerShareTransRatio     | double             | 每股转增股比例    |
| nAllotmentRatio         | double             | 每股配股比例     |
| nAllotmentPrice         | double             | 配股价        |
| nRestorationFactor      | double             | 复权因子（前复权）  |
| nAccumRestorationFactor | double             | 累积复权因子     |
| szEndDate               | char[21]           | 累积复权因子截止日期 |
|                         |                    |            |

| 类型别名               | 类型       | 描述                                   |
| ------------------ | -------- | ------------------------------------ |
| GD_CodeType        | char[32] | 证券代码                                 |
| GD_ISODateTimeType | char[21] | 日期和时间类型（格式 ：yyyy - MM - dd hh:mm:ss） |
|                    |          |                                      |

### 1.7.16 连接成功系统通知

```c++
void OnConnect();
```



### 1.7.17 断线系统通知

```c++
void OnDisconnect();
```



### 1.7.18 自动断线重连状态通知

是否连接成功。

```c++
void OnReconnectStatus(bool successed);
```



### 1.7.19 通过这个进行数据时效性状态通知

```c++
void OnRecvDataTimeless(GD_Stock_Timeliness_Notification* pData);
```

| 参数    | 类型                                | 说明      |
| ----- | --------------------------------- | ------- |
| pData | GD_Stock_Timeliness_Notification* | 数据时效性通知 |
|       |                                   |         |

GD_Stock_Timeliness_Notification 各项参数说明：

| 参数名称   | 参数类型              | 说明                      |
| ------ | ----------------- | ----------------------- |
| isTick | bool              | True 为tick, false 为K线数据 |
| nType  | GD_TimelinessType | 数据时效性属性（注：参见**数据字典2**）  |
| szCode | GD_CodeType       | 代码名称                    |
|        |                   |                         |

| 类型别名        | 类型       | 描述   |
| ----------- | -------- | ---- |
| GD_CodeType | char[32] | 证券代码 |
|             |          |      |

### 1.7.20 错误信息

```c++
void OnError(string error);
```

| 参数    | 类型     | 说明   |
| ----- | ------ | ---- |
| error | string | 错误信息 |
|       |        |      |





## 1.8 行情Api参数说明



### 1.8.1 登录认证服务器

```c++
bool Login(char* user, char* pass, int &err);
```

成功登陆，返回true；否则，返回false。

| 参数   | 类型    | 说明    |
| ---- | ----- | ----- |
| user | char* | 用户名   |
| pass | char* | 密码    |
| err  | int & | 错误码返回 |
|      |       |       |

### 1.8.2 请求实时行情

tick数据和k线可以同时请求，ReqUpdateSubStockCode可以同时修改k线和tick的订阅代码。

#### 1.8.2.1 请求实时tick

```c++
void ReqRealtimeData(std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int subDataType, int &err);
```

| 参数          | 类型                    | 说明                                |
| ----------- | --------------------- | --------------------------------- |
| subCodes    | std::vector\<char*> & | 订阅代码列表                            |
| isAllMarket | bool                  | 是否订阅全市场代码                         |
| beginTime   | int                   | 开始时间，精确到秒。例："2016-06-01 09:30:00" |
| subDataType | int                   | 接收数据类型                            |
| err         | int &                 | 错误码返回                             |
|             |                       |                                   |

#### 1.8.2.2 请求实时k线

type为k线周期类型，一次只能订阅一种周期。其他参数同上，数据回调为 OnRecvGDKLine。

```c++
void ReqRealtimeGDKlineData(int type, std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int &err);
```

| 参数          | 类型                    | 说明                                 |
| ----------- | --------------------- | ---------------------------------- |
| type        | int                   | k线的周期类型                            |
| subCodes    | std::vector\<char*> & | 订阅代码列表                             |
| isAllMarket | bool                  | 是否订阅全市场代码                          |
| beginTime   | int                   | 开始时间，精确到秒。例："2016-06-01 09:30:00"。 |
| err         | int &                 | 错误码返回                              |
|             |                       |                                    |

#### 1.8.2.3 更新订阅代码

```c++
void ReqUpdateSubStockCode(GD_UpdateSubCodeType reqType, std::vector<char*> &subCodes, bool isAllMarket, int &err);
```

| 参数          | 类型                    | 说明                                     |
| ----------- | --------------------- | -------------------------------------- |
| reqType     | GD_UpdateSubCodeType  | 更新订阅代码，可以增加、替换和删除订阅的代码。（注：参见**数据字典4**） |
| subCodes    | std::vector\<char*> & | 订阅代码列表                                 |
| isAllMarket | bool                  | 是否订阅全市场代码                              |
| err         | int &                 | 错误码返回                                  |
|             |                       |                                        |

### 1.8.3 请求模拟行情时间线

#### 1.8.3.1 请求模拟时间线 

```c++
void ReqSimulationTimeline(GD_ISODateTimeType beginTime, GD_PlaybackSpeedType speadTyp, int &err);
```

| 参数        | 类型                   | 说明                        |
| --------- | -------------------- | ------------------------- |
| beginTime | GD_ISODateTimeType   | 请求历史数据模拟回测类型，参加**数据字典14** |
| speadTyp  | GD_PlaybackSpeedType | 请求历史数据模拟回测类型，参见**数据字典14** |
| err       | int &                | 错误码返回                     |
|           |                      |                           |

| 类型别名               | 类型       | 描述                                   |
| ------------------ | -------- | ------------------------------------ |
| GD_ISODateTimeType | char[21] | 日期和时间类型（格式 ：yyyy - MM - dd hh:mm:ss） |
|                    |          |                                      |

#### 1.8.3.2 

```c++
void ReqSimulationTickData(std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int subDataType, int &err);
```

| 参数          | 类型                   | 说明                                  |
| ----------- | -------------------- | ----------------------------------- |
| subCodes    | std::vector<char*> & | 订阅代码列表。                             |
| isAllMarket | bool                 | 是否订阅全市场数据。                          |
| beginTime   | int                  | 开始时间，精确到秒。例如：“2016-06-01 09:30:00”。 |
| subDataType | int                  | 日期和时间类型，格式 yyyy - MM - dd hh:mm:ss。 |
| int &       | err                  | 错误码返回                               |
|             |                      |                                     |

#### 1.8.3.3

```c++
void ReqSimulationGDKlineData(int type, std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int &err);
```

| 参数          | 类型                   | 说明                                |
| ----------- | -------------------- | --------------------------------- |
| type        | int                  | 请求k线数据的周期类型 。                     |
| subCodes    | std::vector<char*> & | 订阅代码列表。                           |
| isAllMarket | bool                 | 是否请阅全市场数据。                        |
| beginTime   | int                  | 开始时间，精确到秒。例："2016-06-01 09:30:00" |
| err         | int &                | 错误码返回                             |
|             |                      |                                   |

#### 1.8.3.4

```c++
void ReqSimulationUpdateSubStockCode(GD_UpdateSubCodeType reqType, std::vector<char*> &subCodes, bool isAllMarket, int &err);
```

| 参数          | 类型                   | 说明                   |
| ----------- | -------------------- | -------------------- |
| reqType     | GD_UpdateSubCodeType | 更新订阅代码类型，参见**数据字典4** |
| subCodes    | std::vector<char*>   | 订阅代码列表               |
| isAllMarket | bool                 | 是否订阅全市场代码            |
| err         | int &                | 错误码返回                |
|             |                      |                      |



### 1.8.4 请求历史行情

tick数据和k线可以同时请求，ReqUpdateSubStockCode可以同时修改k线和tick的订阅代码。

#### 1.8.4.1 请求历史Level2 tick行情

modelType 为数据回放速度选择, fast为最快速，normal为与真实行情同样的速度。

```c++
void ReqHistoryData(GD_ISODateTimeType beginTime, GD_ISODateTimeType endTime, GD_PlaybackSpeedType modelType, std::vector<char*> &subCodes, bool isAllMarket, int &err);
```

| 参数          | 类型                   | 说明                                    |
| ----------- | -------------------- | ------------------------------------- |
| beginTime   | GD_ISODateTimeType   | 历史数据开始时间，精确到秒。例："2016-06-01 09:30:00" |
| endTime     | GD_ISODateTimeType   | 历史数据结束时间，精确到秒。例："2016-06-01 09:30:00" |
| modelType   | GD_PlaybackSpeedType | 修订操作类型选择，参见**数据字典14**                 |
| subCodes    | std::vector<char*> & | 订阅代码列表                                |
| isAllMarket | bool                 | 是否订阅全市场代码                             |
| err         | int &                | 错误码返回                                 |
|             |                      |                                       |

| 类型别名               | 类型       | 描述                              |
| ------------------ | -------- | ------------------------------- |
| GD_ISODateTimeType | char[21] | 日期和时间类型（格式 yyyy-MM-dd hh:mm:ss） |
|                    |          |                                 |

#### 1.8.4.2 请求历史k线数据行情

数据回调为 OnRecvGDKLine。

```c++
void ReqHistoryGDKLineData(GD_CycType type, GD_ISODateTimeType beginTime, GD_ISODateTimeType endTime, std::vector<char*> &subCodes, bool isAllMarket, int &err);
```

| 参数          | 类型                    | 说明                                |
| ----------- | --------------------- | --------------------------------- |
| type        | GD_CycType            | 请求k线数据的周期类型（注：见**数据字典1** ）        |
| beginTime   | GD_ISODateTimeType    | 开始时间，精确到秒。例："2016-06-01 09:30:00" |
| endTime     | GD_ISODateTimeType    | 结束时间，精确到秒。例："2016-06-01 09:30:00" |
| subCodes    | std::vector\<char*> & | 订阅代码表                             |
| isAllMarket | bool                  | 是否订阅全市场数据。                        |
| err         | int &                 | 错误码返回                             |
|             |                       |                                   |

| 类型别名               | 类型       | 描述                               |
| ------------------ | -------- | -------------------------------- |
| GD_ISODateTimeType | char[21] | 日期和时间类型（格式： yyyy-MM-dd hh:mm:ss） |
|                    |          |                                  |

#### 1.8.4.3 查询的交易日列表

```c++
void ReqTradingDay(GD_ISODateTimeType beginDay, GD_ISODateTimeType endDay, int &err);
```

| 参数       | 类型                 | 说明                          |
| -------- | ------------------ | --------------------------- |
| beginDay | GD_ISODateTimeType | 开始时间（格式：yyy-MM-dd hh:mm:ss） |
| endDay   | GD_ISODateTimeType | 结束时间（格式：yyy-MM-dd hh:mm:ss） |
| err      | int &              | 错误码返回                       |
|          |                    |                             |

| 类型别名               | 类型       | 描述                               |
| ------------------ | -------- | -------------------------------- |
| GD_ISODateTimeType | char[21] | 日期和时间类型（格式 ：yyyy-MM-dd hh:mm:ss） |
|                    |          |                                  |

#### 

### 1.8.5 指标接口

#### 1.8.5.1 启用K线计算函数

```c++
void calculateKLineByTick(std::vector<GD_CycType> cycs);
```

| 参数   | 类型                       | 说明   |
| ---- | ------------------------ | ---- |
| cycs | std::vector\<GD_CycType> | 指标接口 |
|      |                          |      |

#### 1.8.5.2 获取前复权因子

```c++
std::vector<GD_RestorationFactor> getRestorationFactor(std::vector<char*> &subCodes, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);
```

| 参数        | 类型                   | 说明                                |
| --------- | -------------------- | --------------------------------- |
| subCodes  | std::vector<char*> & | 订阅代码列表                            |
| beginDate | GD_ISODateTimeType   | 开始时间，精确到秒。例：“2016-06-01 09:30:00” |
| endDate   | GD_ISODateTimeType   | 结束时间，精确到秒。例：“2016-06-01 09:30:00” |
| err       | int &                | 错误码返回                             |
|           |                      |                                   |

| 类型别名               | 类型       | 描述                                   |
| ------------------ | -------- | ------------------------------------ |
| GD_ISODateTimeType | char[21] | 日期和时间类型（格式: yyyy - MM - dd hh:mm:ss） |
|                    |          |                                      |

#### 1.8.5.3 获取详细K线

```c++
std::vector<GD_DetailMarketDayKline> getDetailMarketDayKline(std::vector<char*> &subCodes, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);
```

| 参数        | 类型                   | 说明                                |
| --------- | -------------------- | --------------------------------- |
| subCodes  | std::vector<char*> & | 订阅代码列表                            |
| beginDate | GD_ISODateTimeType   | 开始时间，精确到秒。例：“2016-06-01 09:30:00” |
| endDate   | GD_ISODateTimeType   | 结束时间，精确到秒。例：“2016-06-01 09:30:00” |
| err       | int &                | 错误码返回                             |
|           |                      |                                   |

| 类型别名               | 类型       | 描述                                  |
| ------------------ | -------- | ----------------------------------- |
| GD_ISODateTimeType | char[21] | 日期和时间类型（格式：yyyy - MM - dd hh:mm:ss） |
|                    |          |                                     |

#### 1.8.5.4 获取股票因子 

```c++
vector<GD_StockFactors> getStockFactors(GD_CodeType code, vector<char*> &factorKeys, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);
```

**Factor key** **说明** 参见**附录**。

| 参数         | 类型                 | 说明                                |
| ---------- | ------------------ | --------------------------------- |
| code       | GD_CodeType        | 证券代码                              |
| factorKeys | vector<char*> &    | 因子的key，参见因子附录。                    |
| beginDate  | GD_ISODateTimeType | 开始日期，精确到秒。例：“2016-06-01 09:30:00” |
| endDate    | GD_ISODateTimeType | 结束日期，精确到秒。例：“2016-06-01 09:30:30” |
| err        | int &              | 错误码返回                             |
|            |                    |                                   |

| 类型别名               | 类型       | 描述                                   |
| ------------------ | -------- | ------------------------------------ |
| GD_ISODateTimeType | char[21] | 日期和时间类型（格式 ：yyyy - MM - dd hh:mm:ss） |
|                    |          |                                      |





## 1.9 获取API 版本号

```c++
const char* GetQuantPlatformApiVersion();
```

## 1.10 创建数据连接对象

```c++
PT_QuantPlatform::GetDataApi* CreateGetDataApi(PT_QuantPlatform::GetDataSpi* spi, bool autoRecon, int reconTimeOut, bool autoReq = false, PT_QuantPlatform::TradeDataApi* tApi = NULL, bool enableLog = true);
```

| 参数               | 类型                              | 说明                  |
| ---------------- | ------------------------------- | ------------------- |
| spi              | PT_QuantPlatform::GetDataSpi*   | 数据回调对象实例            |
| autoRecon        | bool                            | 是否启动自动重连            |
| reconTimeOut     | int                             | 自动重连时间间隔，单位毫秒。      |
| autoReq = false  | bool                            | 自动重连后是否自动发送上一个数据请求。 |
| tApi = NULL      | PT_QuantPlatform::TradeDataApi* | 模拟交易连接对象实例。         |
| enableLog = true | bool                            | 是否启用日志。             |
|                  |                                 |                     |

## 1.11 析构数据连接对象

```c++
void DelGetDataApi(PT_QuantPlatform::GetDataApi* pAPI);
```

| 参数   | 类型                            | 说明        |
| ---- | ----------------------------- | --------- |
| pAPI | PT_QuantPlatform::GetDataApi* | 数据连接对象指针。 |
|      |                               |           |

## 1.12 使用示例代码

```c++
//行情接口使用示例

PT_QuantPlatform::GetDataApi* m_api = CreateGetDataApi(spi/*spi实例*/, true, 200, false);  // 创建行情实例

if (!m_api->connect("IP", Port ))	// 连接服务器
{
	return;
}

m_api->Login("user", "passwd", m_err);    // 登录

vector<char*> subCode;
subCode.push_back("600000");

GD_ISODateTimeType beginTime;
GD_ISODateTimeType endTime;
string beginStr = "2016-06-01 09:30:00";
string endStr = "2016-06-03 09:30:00";
strcpy(beginTime, beginStr.c_str());
strcpy(endTime, endStr.c_str());

m_api->ReqSimulationData(beginTime, endTime, fast_GD_SimuModelType, subCode, false, m_err);  //  请求历史level2
```

# 2 交易接口



## 2.1 系统构架

暂略

## 2.2 开发包文件结构

暂略

## 2.3 访问回调时序图

暂略

## 2.4创建回调函数实例

```c++
class TradeClient : public TradeDataSpi
{
public:
	virtual void OnDisConnect(){};
    //插入订单回调
	virtual void OnRspOrderInsert(const TD_OrderInsert_Rsp *rsp, TD_ErrorCode error)
	{
		cout << "OrderInsert   error:" << error << " time:" << rsp->szInsertTime << " 			orderid:" << rsp->nOrderId << endl;
	};	
    //修改订单回调
	virtual void OnRspOrderModify(const TD_OrderModify_Rsp *rsp, TD_ErrorCode error){};	     //删除订单回调	
	virtual void OnRspOrderDelete(const TD_OrderDelete_Rsp *rsp, TD_ErrorCode error)
	{
		cout << "OnRspOrderDelete " << rsp->nOrderId << " error:" << error << endl;
	};				
	//查询订单回调
	virtual void OnRspQryOrder(const TD_QryOrder_Rsp *rsp, TD_ErrorCode error, bool isEnd)
	{
		cout << "isEnd:" << isEnd << " orderId:" << rsp->nOrderId << " status:" 
        << rsp->nStatus << " dealprice" << rsp->nOrderPrice 
        << " dealvol:" << rsp->nOrderVol << endl;
	};	
    //查询成交回调
	virtual void OnRspQryMatch(const TD_QryMatch_Rsp *rsp, TD_ErrorCode error, bool isEnd)
	{
		cout << "isEnd:" << isEnd << " orderId:" << rsp->nOrderId << " tradeid:" 
          << rsp->nMatchStreamId << " dealprice:" << rsp->nMatchPrice 
          << " deakvol:" << rsp->nMatchVol << endl;
	};	
    //查询持仓回调
	virtual void OnRspQryPosition(const TD_QryPosition_Rsp *rsp, TD_ErrorCode error, bool isEnd){};			
    //订单状态变化通知
	virtual void OnRtnOrderStatusChangeNotice(const TD_OrderStatusChangeNotice *notice)
	{
		cout << "OrderStatusChangeNotice   time:" << notice->szInsertTime 
          << " orderid:" << notice->nOrderId << " status:" << notice->nStatus << endl;
	};
    //成交状态更新通知
	virtual void OnRtnOrderMatchNotice(const TD_OrderMatchNotice *notice)
	{
		cout << "OrderMatchNotice   tradeid:" << notice->nMatchStreamId << " time:" 
          << notice->szMatchTime << " price:" << notice->nMatchPrice << " vol:" 
          << notice->nMatchVol << endl;
	};						
	 // 查询资金帐号回调
	virtual void OnRspQryCapitalAccount(const TD_QryCapital_Rsp* rsp, 
                                       TD_ErrorCode error, bool isEnd){}
     // 查询融券负债回调
	virtual void OnRspQrySecuDebt(const TD_QrySecuDebt_Rsp* rsp, 
                                 TD_ErrorCode error, bool isEnd){}		
    // 查询最大可委托量回调
	virtual void OnRspQryMaxEntrustCount(const TD_QryMaxEntrustCount_Rsp* rsp,
                                        TD_ErrorCode error){}	
    // 查询可融券列表回调
	virtual void OnRspQrySecuritiesLendingAmount
      (const TD_QrySecuritiesLendingAmount_Rsp* rsp, TD_ErrorCode error, bool isEnd){}
public:
	TradeClient(){};
	~TradeClient(){};
};
```

## 2.5 获取交易连接对象实例

```c++
API_EXPORT PT_QuantPlatform::TradeDataApi* CreateTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool isSimulation = false, bool enableLog = true);
```

| 参数           | 类型                              | 说明                      |
| ------------ | ------------------------------- | ----------------------- |
| spi          | PT_QuantPlatform::TradeDataSpi* | 自定义的回调类的实例对象指针          |
| autoRecon    | bool                            | 是否断线后自动重连               |
| reconTimeOut | int                             | 断线重连重试时间间隔，单位毫秒。        |
| isSimulation | bool                            | 是否使用模拟撮合引擎；默认值为*false*。 |
| enableLog    | bool                            | 是否开启日志功能；默认值为*true*。    |
|              |                                 |                         |

## 2.6 释放交易连接对象实例

```c++
API_EXPORT void DelTradeDataApi(PT_QuantPlatform::TradeDataApi* pAPI);
```

| 参数   | 类型                              | 说明          |
| ---- | ------------------------------- | ----------- |
| pAPI | PT_QuantPlatform::TradeDataApi* | 需要释放的交易实例指针 |
|      |                                 |             |



## 2.7 交易Spi说明

### 2.7.1 用户登录回调

```c++
void OnRspUserTradeInfo(const TD_UserTradeInfoRsp *rsp;
```

| 参数   | 类型                    | 说明       |
| ---- | --------------------- | -------- |
| rsp  | TD_UserTradeInfoRsp * | 用户登录信息回调 |
|      |                       |          |

### 2.7.2 连接成功

```c++
void OnTDConnect()；
```

### 2.7.3 断开

```c++
void OnTDDisConnect()；
```

### 2.7.4 断线重连尝试状态

```c++
void OnTDReconnectStatus(const bool successed)；
```

| 参数        | 类型   | 说明   |
| --------- | ---- | ---- |
| successed | bool |      |
|           |      |      |

### 2.7.5 插入订单回调

```c++
void OnRspOrderInsert(const TD_OrderInsert_Rsp *rsp, int error);
```

| 参数    | 类型                         | 说明     |
| ----- | -------------------------- | ------ |
| rsp   | const TD_OrderInsert_Rsp * | 插入订单回调 |
| error | int                        | 错误码    |
|       |                            |        |

TD_OrderInsert_Rsp 各项参数说明：

| 参数名称            | 参数类型               | 说明                             |
| --------------- | ------------------ | ------------------------------ |
| nReqId          | int                | 请求ID（有客户端API维护的唯一ID）           |
| nUserInt        | int                | 用户保留字段                         |
| nUserDouble     | double             | 用户保留字段                         |
| szUseStr        | char[128]          | 用户保留字段                         |
| nUserId         | int                | 客户端编号                          |
| nAccountId      | int                | 券商资金账户Id                       |
| nOrderId        | int                | 服务器维护（服务唯一）                    |
| szOrderStreamId | char[32]           | 委托编号（broker 或交易所的唯一编号）         |
| szContractCode  | char[32]           | 证券合约代码                         |
| szContractName  | char[32]           | 证券合约名称                         |
| nOrderType      | TD_OrderType       | 市价限价单（注：见数据字典**8**）            |
| nTradeType      | TD_TradeType       | 交易类型 买、卖、融券等（注：见数据字典**9**）     |
| nOffsetType     | TD_OffsetType      | 开平仓类型(注：见数据字典**10**)           |
| nOrderPrice     | double             | 申报价                            |
| nOrderVol       | int                | 申报量                            |
| szInsertTime    | char[32]           | 接收委托时间(格式 yyyy-MM-dd hh:mm:ss) |
| nStatus         | TD_OrderStatusType | 状态(见数据字典**11**)                |
| nDealedPrice    | double             | 成交均价                           |
| nDealedVol      | int                | 成交总量                           |
|                 |                    |                                |

### 2.7.3 修改订单回调

```c++
void OnRspOrderModify(const TD_OrderModify_Rsp *rsp, int error);
```

| 参数    | 类型                         | 说明       |
| ----- | -------------------------- | -------- |
| rsp   | const TD_OrderModify_Rsp * | 修改订单回调数据 |
| error | int                        | 错误码      |
|       |                            |          |

TD_OrderModify_Rsp 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    | 用户保留字段               |
| szUseStr    | char[128] | 用户保留字段               |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| nOrderId    | int       | 订单Id                 |
| nPrice      | double    | 修改申报价                |
| nVol        | int       | 修改申报量                |

### 2.7.4 删除订单回调

```c++
void OnRspOrderDelete(const TD_OrderDelete_Rsp *rsp, int error);
```

| 参数    | 类型                         | 说明       |
| ----- | -------------------------- | -------- |
| rsp   | const TD_OrderDelete_Rsp * | 删除订单回调数据 |
| error | int                        | 错误码      |
|       |                            |          |

TD_OrderDelete_Rsp 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    | 用户保留字段               |
| szUseStr    | char[128] | 用户保留字段               |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| nOrderId    | int       | 订单Id                 |

### 2.7.5 查询订单回调

```c++
void OnRspQryOrder(const TD_QryOrder_Rsp *rsp, int error, bool isEnd);
```

| 参数    | 类型                      | 说明       |
| ----- | ----------------------- | -------- |
| rsp   | const TD_QryOrder_Rsp * | 查询订单回调数据 |
| error | int                     | 错误码      |
| isEnd | bool                    | 是否是最后一条  |
|       |                         |          |

TD_QryOrder_Rsp 各项参数说明：

| 参数名称            | 参数类型               | 说明                             |
| --------------- | ------------------ | ------------------------------ |
| nReqId          | int                | 请求ID（有客户端API维护的唯一ID）           |
| nUserInt        | int                | 用户保留字段                         |
| nUserDouble     | double             | 用户保留字段                         |
| szUseStr        | char[128]          | 用户保留字段                         |
| nUserId         | int                | 客户端编号                          |
| nAccountId      | int                | 券商资金账户Id                       |
| nOrderId        | int                | 服务器维护（服务唯一）                    |
| szOrderStreamId | char[32]           | 委托编号（broker 或交易所的唯一编号）         |
| szContractCode  | char[32]           | 证券合约代码                         |
| szContractName  | char[32]           | 证券合约名称                         |
| nOrderType      | TD_OrderType       | 市价限价单（注：见**数据字典8**）            |
| nTradeType      | TD_TradeType       | 交易类型 买、卖、融券等(注：见**数据字典9**)     |
| nOffsetType     | TD_OffsetType      | 开平仓类型（注：见**数据字典10**）           |
| nOrderPrice     | double             | 申报价                            |
| nOrderVol       | int                | 申报量                            |
| szInsertTime    | char[32]           | 接收委托时间（格式 yyyy-MM-dd hh:mm:ss） |
| nStatus         | TD_OrderStatusType | 状态（注：见**数据字典11**）              |
| nDealedPrice    | double             | 成交均价                           |
| nDealedVol      | int                | 成交总量                           |
|                 |                    |                                |

### 2.7.6 查询成交回调

```c++
void OnRspQryMatch(const TD_QryMatch_Rsp *rsp, int error, bool isEnd);
```

| 参数    | 类型                      | 说明       |
| ----- | ----------------------- | -------- |
| rsp   | const TD_QryMatch_Rsp * | 查询成交回调数据 |
| error | int                     | 错误码      |
| isEnd | bool                    | 是否是最后一条  |

TD_QryMatch_Rsp 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    | 用户保留字段               |
| szUseStr       | char[128] | 用户保留字段               |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| nOrderId       | int       | 对于委托编号               |
| nMatchStreamId | int       | 成交系统编号               |
| nMatchPrice    | double    | 成交价                  |
| nMatchVol      | int       | 成交量                  |
| szContractCode | char[32]  | 股票代码                 |
| szMatchTime    | char[21]  | 成交时间                 |

### 2.7.7 查询持仓回调

```c++
void OnRspQryPosition(const TD_QryPosition_Rsp *rsp, int error, bool isEnd);
```

| 参数    | 类型                         | 说明       |
| ----- | -------------------------- | -------- |
| rsp   | const TD_QryPosition_Rsp * | 查询持仓回调数据 |
| error | int                        | 错误码      |
| isEnd | bool                       | 是否是最后一条  |

TD_QryPosition_Rsp 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    | 用户保留字段               |
| szUseStr       | char[128] | 用户保留字段               |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| szContractCode | char[32]  | 证券合约代码               |
| nPosition      | int       | 持仓总量                 |
| nPrice         | double    | 持仓均价                 |
| nProfit        | double    | 浮盈                   |

### 2.7.8 查询资金帐号回调

```c++
void OnRspQryCapitalAccount(const TD_QryCapital_Rsp* rsp, int error, bool isEnd);
```

| 参数    | 类型                       | 说明         |
| ----- | ------------------------ | ---------- |
| rsp   | const TD_QryCapital_Rsp* | 查询资金账号回调数据 |
| error | int                      | 错误码        |
| isEnd | bool                     | 是否是最后一条    |

TD_QryCapital_Rsp 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    | 用户保留字段               |
| szUseStr    | char[128] | 用户保留字段               |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| m_fundbal   | double    | 资金负债总额               |
| m_fundavl   | double    | 资金可用金额               |

### 2.7.9 查询融券负债回调

```c++
void OnRspQrySecuDebt(const TD_QrySecuDebt_Rsp* rsp, int error, bool isEnd); 
```

| 参数    | 类型                        | 说明         |
| ----- | ------------------------- | ---------- |
| rsp   | const TD_QrySecuDebt_Rsp* | 查询融券负债回调数据 |
| error | int                       | 错误码        |
| isEnd | bool                      | 是否是最后一条    |
|       |                           |            |

TD_QrySecuDebt_Rsp 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    | 用户保留字段               |
| szUseStr       | char[128] | 用户保留字段               |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| szContractCode | char[32]  | 股票代码                 |
| m_dstkbal      | int       | 负债总股数                |

### 2.7.10 查询最大可委托量回调

```c++
void OnRspQryMaxEntrustCount(const TD_QryMaxEntrustCount_Rsp* rsp, int error);
```

| 参数    | 类型                               | 说明           |
| ----- | -------------------------------- | ------------ |
| rsp   | const TD_QryMaxEntrustCount_Rsp* | 查询最大可成交量回调数据 |
| error | int                              | 错误码          |
|       |                                  |              |

TD_QryMaxEntrustCount_Rsp 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    | 用户保留字段               |
| szUseStr    | char[128] | 用户保留字段               |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| m_maxStkqty | int       | 最大可委托数量              |

### 2.7.11 查询可融券列表回调

```c++
void OnRspQrySecuritiesLendingAmount(const TD_QrySecuritiesLendingAmount_Rsp* rsp, int error, bool isEnd); 
```

| 参数    | 类型                                       | 说明          |
| ----- | ---------------------------------------- | ----------- |
| rsp   | const TD_QrySecuritiesLendingAmount_Rsp* | 查询可融券列表回调数据 |
| error | int                                      | 错误码         |
| isEnd | bool                                     | 是否是最后一条     |
|       |                                          |             |

TD_QrySecuritiesLendingAmountRsp 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    | 用户保留字段               |
| szUseStr       | char[128] | 用户保留字段               |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| szContractCode | char[32]  | 股票代码                 |
| m_sepremQty    | int       | 余券                   |
|                |           |                      |

### 2.7.12 订单状态变化通知

```c++
void OnRtnOrderStatusChangeNotice(const TD_OrderStatusChangeNotice *notice);
```

| 参数     | 类型                                 | 说明         |
| ------ | ---------------------------------- | ---------- |
| notice | const TD_OrderStatusChangeNotice * | 订单状态变化通知数据 |
|        |                                    |            |

TD_OrderStatusChangeNotice 各项参数说明：

| 参数名称            | 参数类型               | 说明                         |
| --------------- | ------------------ | -------------------------- |
| nReqId          | int                | 请求ID（有客户端API维护的唯一ID）       |
| nUserInt        | int                | 用户保留字段                     |
| nUserDouble     | double             | 用户保留字段                     |
| szUseStr        | char[128]          | 用户保留字段                     |
| nUserId         | int                | 客户端编号                      |
| nAccountId      | int                | 券商资金账户Id                   |
| nOrderId        | int                | 服务器维护（服务唯一）                |
| szOrderStreamId | char[32]           | 委托编号（broker 或交易所的唯一编号）     |
| szContractCode  | char[32]           | 证券合约代码                     |
| szContractName  | char[32]           | 证券合约名称                     |
| nOrderType      | TD_OrderType       | 市价限价单（注：见**数据字典8**)        |
| nTradeType      | TD_TradeType       | 交易类型 买、卖、融券等（注：见**数据字典9**） |
| nOffsetType     | TD_OffsetType      | 开平仓类型（注：见**数据字典10**）       |
| nOrderPrice     | double             | 申报价                        |
| nOrderVol       | int                | 申报量                        |
| szInsertTime    | char[21]           | 接收委托时间                     |
| nStatus         | TD_OrderStatusType | 状态（注：见**数据字典11**)          |
| nDealedPrice    | double             | 成交均价                       |
| nDealedVol      | int                | 成交总量                       |
|                 |                    |                            |

### 2.7.13 成交状态更新通知

```c++
void OnRtnOrderMatchNotice(const TD_OrderMatchNotice *notice);
```

| 参数     | 类型                          | 说明         |
| ------ | --------------------------- | ---------- |
| notice | const TD_OrderMatchNotice * | 成交状态更新通知数据 |
|        |                             |            |

TD_OrderMatchNotice 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    | 用户保留字段               |
| szUseStr       | char[128] | 用户保留字段               |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| nOrderId       | int       | 对于委托编号               |
| nMatchStreamId | int       | 成交系统编号               |
| nMatchPrice    | double    | 成交价                  |
| nMatchVol      | int       | 成交量                  |
| szContractCode | char[32]  | 股票代码                 |
| szMatchTime    | char[21]  | 成交时间                 |
|                |           |                      |

## 2.8 交易Api说明

### 2.8.1 登录

```c++
bool Login(char* user, char* pass, int &err);
```

登录成功，返回true；否则，返回false，且将错误码修改至`err。

| 参数   | 类型    | 说明    |
| ---- | ----- | ----- |
| user | char* | 登录用户名 |
| pass | char* | 登录密码  |
| err  | int & | 错误码返回 |
|      |       |       |

### 2.8.2 设置回测 

```c++
void SetNewBackTest(double stampTax, double transferFees, double commissions, char* szComment, int &err);
```

| 参数           | 类型     | 说明    |
| ------------ | ------ | ----- |
| stampTax     | double | 印花税   |
| transferFees | double | 过户费   |
| commissions  | double | 佣金    |
| szComment    | char*  | 回测备注  |
| err          | int &  | 错误码返回 |
|              |        |       |



### 2.8.3 插入订单

```c++
void OrderInsert(TD_OrderInsert_Req* req);
```

| 参数   | 类型                  | 说明     |
| ---- | ------------------- | ------ |
| req  | TD_OrderInsert_Req* | 插入订单数据 |
|      |                     |        |

TD_OrderInsert_Req 各项参数说明

| 参数名称            | 参数类型          | 说明                         |
| --------------- | ------------- | -------------------------- |
| nReqId          | int           | 请求ID（有客户端API维护的唯一ID）       |
| nUserInt        | int           | 用户保留字段                     |
| nUserDouble     | double        | 用户保留字段                     |
| szUseStr        | char[128]     | 用户保留字段                     |
| nUserId         | int           | 客户端编号                      |
| nAccountId      | int           | 券商资金账户Id                   |
| nOrderId        | int           | 服务器维护（服务唯一）                |
| szOrderStreamId | char[32]      | 委托编号（broker 或交易所的唯一编号）     |
| szContractCode  | char[32]      | 证券合约代码                     |
| szContractName  | char[32]      | 证券合约名称                     |
| nOrderType      | TD_OrderType  | 市价限价单（注：见**数据字典8**)        |
| nTradeType      | TD_TradeType  | 交易类型 买、卖、融券等（注：见**数据字典9**） |
| nOffsetType     | TD_OffsetType | 开平仓类型（注：见**数据字典10**）       |
| nOrderPrice     | double        | 申报价                        |
| nOrderVol       | int           | 申报量                        |
| szInsertTime    | char[21]      | 接收委托时间                     |
|                 |               |                            |

### 2.8.4 修改订单

```c++
void OrderModify(TD_OrderModify_Req* req);
```

| 参数   | 类型                  | 说明   |
| ---- | ------------------- | ---- |
| req  | TD_OrderModify_Req* | 修改订单 |
|      |                     |      |

TD_OrderModify_Req 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    | 用户保留字段               |
| szUseStr    | char[128] | 用户保留字段               |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| nOrderId    | int       | 订单Id                 |
| nPrice      | double    | 修改申报价                |
| nVol        | int       | 修改申报量                |
|             |           |                      |

### 2.8.5 删除订单

```c++
void OrderDelete(TD_OrderDelete_Req* req);
```

| 参数   | 类型                  | 说明   |
| ---- | ------------------- | ---- |
| req  | TD_OrderDelete_Req* | 删除订单 |
|      |                     |      |

TD_OrderDelete_Req 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    | 用户保留字段               |
| szUseStr    | char[128] | 用户保留字段               |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| nOrderId    | int       | 订单ID                 |
|             |           |                      |

### 2.8.6 查询当日所有订单

```c++
void QryOrder(TD_QryOrder_Req* req);
```

| 参数   | 类型               | 说明       |
| ---- | ---------------- | -------- |
| req  | TD_QryOrder_Req* | 查询当日所有订单 |
|      |                  |          |

TD_QryOrder_Req 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    | 用户保留字段               |
| szUseStr       | char[128] | 用户保留字段               |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| nOrderId       | int       | 委托编号                 |
| szContractCode | char[32]  | 证券合约代码               |
|                |           |                      |

### 2.8.7 查询所有成交

```c++
void QryMatch(TD_QryMatch_Req* req);
```

| 参数   | 类型               | 说明     |
| ---- | ---------------- | ------ |
| req  | TD_QryMatch_Req* | 查询所有成交 |
|      |                  |        |

TD_QryMatch_Req 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    | 用户保留字段               |
| szUseStr       | char[128] | 用户保留字段               |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| szContractCode | char[32]  | 证券合约代码               |
|                |           |                      |

### 2.8.8 查询头寸

```c++
void QryPosition(TD_QryPosition_Req* req);
```

| 参数   | 类型                  | 说明     |
| ---- | ------------------- | ------ |
| req  | TD_QryPosition_Req* | 查询所有头寸 |
|      |                     |        |

TD_QryPosition_Req 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    | 用户保留字段               |
| szUseStr       | char[128] | 用户保留字段               |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户信息             |
| szContractCode | char[32]  | 证券合约代码               |
|                |           |                      |

### 2.8.9 查询资金帐号

```c++
void QryCapitalAccount(TD_QryCapital_Req* req);
```

| 参数   | 类型                 | 说明     |
| ---- | ------------------ | ------ |
| req  | TD_QryCapital_Req* | 查询资金账号 |
|      |                    |        |

TD_QryCapital_Req 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    | 用户保留字段               |
| szUseStr    | char[128] | 用户保留字段               |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
|             |           |                      |

### 2.8.10 查询融券负债

```c++
void QrySecuDebt(TD_QrySecuDebt_Req* req);  
```

| 参数   | 类型                  | 说明     |
| ---- | ------------------- | ------ |
| req  | TD_QrySecuDebt_Req* | 查询融券负债 |
|      |                     |        |

TD_QuerySecuDebt_Req 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    | 用户保留字段               |
| szUseStr    | char[128] | 用户保留字段               |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
|             |           |                      |

### 2.8.11 查询最大可委托量

```c++
void QryMaxEntrustCount(TD_QryMaxEntrustCount_Req* req);
```

| 参数   | 类型                           | 说明       |
| ---- | ---------------------------- | -------- |
| req  | TD_QueryMaxEntrustCount_Req* | 查询最大可委托量 |
|      |                              |          |

TD_QryMaxEntrustCount_Req 各项参数说明：

| 参数名称           | 参数类型         | 说明                   |
| -------------- | ------------ | -------------------- |
| nReqId         | int          | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int          | 用户保留字段               |
| nUserDouble    | double       | 用户保留字段               |
| szUseStr       | char[128]    | 用户保留字段               |
| nUserId        | int          | 客户端编号                |
| nAccountId     | int          | 券商资金账户Id             |
| szContractCode | char[32]     | 股票代码                 |
| nPrice         | double       | 价格                   |
| nTraderType    | TD_TradeType | 交易行为（注：见**数据字典9**)   |
|                |              |                      |

### 2.8.12 查询可融券列表

```c++
void QrySecuritiesLendingAmount(TD_QrySecuritiesLendingAmount_Req* req);
```

| 参数   | 类型                                 | 说明      |
| ---- | ---------------------------------- | ------- |
| req  | TD_QrySecuritiesLendingAmount_Req* | 查询可融券列表 |
|      |                                    |         |

QrySecuritiesLendingAmount_Req 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    | 用户保留字段               |
| szUseStr       | char[128] | 用户保留字段               |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| szContractCode | char[32]  | 股票代码                 |
|                |           |                      |



## 2.9 创建交易连接实例 

```c++
PT_QuantPlatform::TradeDataApi* CreateTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool isSimulation = false, bool enableLog = true);
```

| 参数           | 类型                              | 说明             |
| ------------ | ------------------------------- | -------------- |
| spi          | PT_QuantPlatform::TradeDataSpi* | 回调对象实例。        |
| autoRecon    | bool                            | 是否自动重连。        |
| reconTimeOut | int                             | 自动重连时间间隔，单位毫秒。 |
| isSimulation | bool                            | 是否启用模拟撮合。      |
| enableLog    | bool                            | 是否启用日志。        |
|              |                                 |                |



## 2.10 析构连接对象 

```c++
void DelTradeDataApi(PT_QuantPlatform::TradeDataApi* pAPI);
```

| 参数   | 类型                              | 说明        |
| ---- | ------------------------------- | --------- |
| pAPI | PT_QuantPlatform::TradeDataApi* | 交易连接对象指针。 |
|      |                                 |           |



## 2.11 使用示例代码

```c++
//1、使用模拟引擎
TradeDataApi* m_tApi = CreateTradeDataApi(this, true, 200); 
// 创建模拟交易实例，不需连接、登录操作，可直接进行功能请求



//2、使用交易服务器
radeDataApi* m_tApi = CreateTradeDataApi(this, true, 200, true);  // 创建交易实例

if (!m_tApi->connect("IP", Port))  // 连接服务器
{
	return;	
}

if (!m_tApi->Login())  // 登陆
{
	return;	
}

```



# 3 数据字典

#### 数据字典 1

| 序号   | 字典项                               | 字典项名称         |
| ---- | --------------------------------- | ------------- |
| 1    | GD_CycType                        |               |
|      | none_GD_CycType                   | 空             |
|      | second_10_GD_CycType              | 10秒           |
|      | minute_GD_CycType                 | 分             |
|      | minute_5_GD_CycType               | 5分            |
|      | minute_15_GD_CycType              | 15分           |
|      | minute_30_GD_CycType              | 30分           |
|      | hour_GD_CycType                   | 小时            |
|      | day_GD_CycType                    | 日             |
| 2    | GD_TimelinessType                 | 数据效性          |
|      | historyData_GD_TimelinessType     | 历史数据          |
|      | realtimeData_GD_TimelinessType    | 实时数据          |
| 3    | GD_ErrorType                      |               |
|      | none_GD_ErrorType                 | 无             |
|      | userError_GD_ErrorType            | 用户不存在或用户名密码错误 |
|      | overLoginNumError_GD_ErrorType    | 登录数超限         |
|      | serverConnectedError_GD_ErrorType | 服务器连接错误       |
| 4    | GD_UpdateSubCodeType              |               |
|      | add_GD_UpdateSubCodeType          | 添加订阅代码        |
|      | remove_GD_UpdateSubCodeType       | 移除已有订阅代码      |
|      | replace_GD_UpdateSubCodeType      | 替换全部订阅代码      |
| 5    | GD_SimuModelType                  | 请求历史数据模拟回测类型  |
|      | fast_GD_SimuModelType             | 快速模式          |
|      | normal_GD_SimuModelType           | 正常模式          |
| 6    | TD_BrokerType                     | 券商类型          |
|      | TD_BrokerType_None                |               |
|      | TD_BrokerType_dongwu              |               |
|      | TD_BrokerType_guangda             |               |
|      | TD_BrokerType_guotai              |               |
|      | TD_BrokerType_guoxin              |               |
|      | TD_BrokerType_haitong             |               |
|      | TD_BrokerType_shenwan             |               |
|      | TD_BrokerType_yinhe               |               |
|      | TD_BrokerType_zhaoshang           |               |
|      | TD_BrokerType_fangzheng           |               |
|      | TD_BrokerType_AC                  |               |
|      | TD_BrokerType_zhongxin            |               |
|      | TD_BrokerType_anxin               |               |
|      | TD_BrokerType_dongbei             |               |
|      | TD_BrokerType_huataiwang          |               |
|      | TD_BrokerType_hengtai             |               |
|      | TD_BrokerType_zhongjing           |               |
|      | TD_BrokerType_guangfa             |               |
|      | TD_BrokerType_huabao              |               |
|      | TD_BrokerType_xuntou              |               |
|      | TD_BrokerType_xibu                |               |
|      | TD_BrokerType_IMSWT               |               |
|      | TD_BrokerType_huatai              |               |
| 7    | TD_ErrorCode                      |               |
|      | TD_ErrorCodeEnum_None             |               |
|      | TD_ErrorCodeEnum_NoOrder          |               |
|      | TD_ErrorCodeEnum_FinishedOrder    |               |
|      | TD_ErrorCodeEnum_WrongOrder       |               |
|      | TD_ErrorCodeEnum_WrongModifyOrder |               |
|      | TD_ErrorCodeEnum_SendFailed = 100 |               |
|      | TD_ErrorCodeEnum_NOT_TRADING_TIME |               |
|      | TD_ErrorCodeEnum_Unknown          |               |
| 8    | TD_OrderType_Limit                | 限价单           |
|      | TD_OrderType_Market               | 市价单           |
| 9    | TD_TradeType_Sell                 | 普通卖出          |
|      | TD_TradeType_SellBySecuLending    | 融券卖出          |
|      | TD_TradeType_SellSecurityRtnCash  | 卖券还款          |
|      | TD_TradeType_None                 |               |
|      | TD_TradeType_RtnSecurity          | 直接还券          |
|      | TD_TradeType_RtnCash              | 直接还款          |
|      | TD_TradeType_Buy                  | 普通买入          |
|      | TD_TradeType_BuyOnMargin          | 融资买入          |
|      | TD_TradeType_BuySecurityRtnSecu   | 买券还券          |
| 10   | TD_OffsetType_Open                | 开仓            |
|      | TD_OffsetType_Close               | 平仓            |
| 11   | TD_OrderStatusType_fail           | 指令失败          |
|      | TD_OrderStatusType_partRemoved    | 部分撤单          |
|      | TD_OrderStatusType_removed        | 撤单成功          |
|      | TD_OrderStatusType_allDealed      | 全部成交          |
|      | TD_OrderStatusType_unAccpet       | 未接受           |
|      | TD_OrderStatusType_accpeted       | 已接受未受理        |
|      | TD_OrderStatusType_queued         | 正在排队	(已受理状态)  |
|      | TD_OrderStatusType_toModify       | 待报改单          |
|      | TD_OrderStatusType_modifing       | 已报改单          |
|      | TD_OrderStatusType_modified       | 改单受理          |
|      | TD_OrderStatusType_toRemove       | 待报撤单          |
|      | TD_OrderStatusType_removing       | 已报待撤          |
|      | TD_OrderStatusType_partDealed     | 部分成交          |
| 12   | TD_OffsetType                     |               |
|      | TD_OffsetType_None                |               |
|      | TD_OffsetType_Open                | 开仓            |
|      | TD_OffsetType_Close               | 平仓            |
| 13   | GD_ErrorType                      |               |
|      | none_GD_ErrorType                 | 无             |
|      | userError_GD_ErrorType            | 用户不存在或用户名密码错误 |
|      | overLoginNumError_GD_ErrorType    | 登录数超限         |
|      | serverConnectedError_GD_ErrorType | 服务器连接错误       |
|      |                                   |               |

#### 数据字典 2

| 序号   | 字典项                           | 字典名称         |
| ---- | ----------------------------- | ------------ |
| 14   | GD_PlaybackSpeedType          | 请求历史数据模拟回测类型 |
|      | fast_GD_PlaybackSpeedType     | 快速模式         |
|      | normal_GD_PlaybackSpeedType   | 正常模式         |
|      | x2Spped_GD_PlaybackSpeedType  | 2倍速模式        |
|      | x3Spped_GD_PlaybackSpeedType  | 3倍速模式        |
|      | x5Spped_GD_PlaybackSpeedType  | 5倍速模式        |
|      | x10Spped_GD_PlaybackSpeedType | 10倍速模式       |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
