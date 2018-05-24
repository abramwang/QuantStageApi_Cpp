| 项目名称 |            |      |      |      |      |
| ---- | :--------: | :--: | ---- | ---- | ---- |
| 文档名称 |  QuantApi  |      |      |      |      |
| 文档状态 |    编辑中     |      |      |      |      |
| 时间   | 2018-05-08 |      |      |      |      |

# 1 QuantApi接口说明

## 1.1 系统接口说明

### 1.1.1 获取API版本 

接口原型：

```c++
static char* getVersion()
```

参数说明：

| 参数名称 | 数据类型  | 说明       |
| ---- | ----- | -------- |
| 返回值  | char* | 返回 API版本 |

### 1.1.2 创建实例 

接口原型：

```c++
static PT_QuantApi* createApi(PT_QuantSpi* spi, bool bEnableLog, PT_QuantTdAppEType nTdType, PT_QuantMdAppEType nMdType)
```

参数说明：

| 参数名称       | 数据类型               | 说明                      |
| ---------- | ------------------ | ----------------------- |
| spi        | PT_QuantSpi*       | 回调指针                    |
| bEnableLog | bool               | 是否开启日志                  |
| nTdType    | PT_QuantTdAppEType | 交易环境 类型（参考数据字典2）        |
| nMdType    | PT_QuantMdAppEType | 行情环境 类型（参考数据字典1）        |
| 返回值        | PT_QuantApi        | 返回  TradeDataApi类型的对象实例 |

----------------------------------------------------------------------------------------------------------------------------------------------------------

接口原型：

```c++
static PT_QuantApi* createApi(PT_QuantSpi* spi, bool bEnableLog, PT_QuantTdAppEType nTdType, bool bTdConnect, PT_QuantMdAppEType nMdType, bool bMdConnect, bool bIfSyn)
```

参数说明：

| 参数名称       | 数据类型               | 说明                      |
| ---------- | ------------------ | ----------------------- |
| spi        | PT_QuantSpi*       | 回调指针                    |
| bEnableLog | bool               | 是否开启日志                  |
| nTdType    | PT_QuantTdAppEType | 交易环境 类型（参考数据字典2）        |
| bTdConnect | bool               | 是否激活交易环境                |
| nMdType    | PT_QuantMdAppEType | 行情环境 类型（参考数据字典1）        |
| bMdConnect | bool               | 是否激活行情环境                |
| bIfSyn     | bool               | 是否同步（当前版本未用到）           |
| 返回值        | PT_QuantApi        | 返回  TradeDataApi类型的对象实例 |

### 1.1.3 删除实例 

接口原型：

```c++
static void deleteApi(PT_QuantApi* api) 
```

参数说明：

| 参数名称 | 数据类型         | 说明        |
| ---- | ------------ | --------- |
| api  | PT_QuantApi* | 需要删除的对象实例 |
| 返回值  | void         |           |

### 1.1.4 初始化环境 

接口原型：

```c++
static void Init()
```

参数说明：

| 参数名称 | 数据类型 | 说明   |
| ---- | ---- | ---- |
| 返回值  | void |      |

### 1.1.5 解析错误码 

接口原型：

```c++
static void GetErrMsg(int nErrCode, char* szErrmsg, int len)
```

参数说明：

| 参数名称     | 数据类型  | 说明           |
| -------- | ----- | ------------ |
| nErrCode | int   | 代码号          |
| szErrmsg | char* | 错误码          |
| len      | int   | szErrmsg内存长度 |
| 返回值      | void  |              |

[注]: 使用此接口前需调用Init()才能获取完整的错误码解析，否则只能解析系统级别错误

### 1.1.6 设置回测记录 

接口原型：

```c++
int SetNewBackTest(PT_BackTestReq* pReq)
```

参数说明：

| 参数名称 | 数据类型            | 说明                       |
| ---- | --------------- | ------------------------ |
| pReq | PT_BackTestReq* | 设置回测限制                   |
| 返回值  | int             | 返回不为0，请求失败，错误码（参考数据字典11） |

PT_BackTestReq结构说明：

| 字段名           | 数据类型    | 说明     |
| ------------- | ------- | ------ |
| nSimAccountId | int64_t | 模拟资金账号 |
[注]: 此接口仅在回测环境中调用才会生效，否则无效！


###1.1.7 登录

接口原型：

```c++
bool Login(char* szUseName, char* szPasswd) 
```

参数说明：

| 参数名称      | 数据类型  | 说明                 |
| --------- | ----- | ------------------ |
| szUseName | char* | 登录帐号               |
| szPasswd  | char* | 登录密码               |
| 返回值       | bool  | 返回true:登录成功，否则登录失败 |

### 1.1.8 获取股票代码表

接口原型：

```c++
int GetCode()
```

参数说明：

| 参数名称 | 数据类型 | 说明                       |
| ---- | ---- | ------------------------ |
| 返回值  | int  | 返回不为0，请求失败，错误码（参考数据字典11） |

### 1.1.9 同步执行函数

接口原型：

```c++
void Run()
```

参数说明：

| 参数名称 | 数据类型 | 说明   |
| ---- | ---- | ---- |
| 返回值  | void |      |
[注]: 此接口在beta 5.1.3.版本中无效

### 1.1.10 退出同步执行

接口原型：

```c++
int BreakExec()
```

参数说明：

| 参数名称 | 数据类型 | 说明   |
| ---- | ---- | ---- |
| 返回值  | void |      |
[注]: 此接口在beta 5.1.3.版本中无效

## 1.2 交易接口说明

### 	1.2.1 下单

接口原型：

```c++
int reqOrderInsert(TD_ReqOrderInsert* req)
```

参数说明：

| 参数名称 | 数据类型               | 说明                       |
| ---- | ------------------ | ------------------------ |
| req  | TD_ReqOrderInsert* | 下单数据信息                   |
| 返回值  | int                | 返回不为0，请求失败，错误码（参考数据字典11） |

TD_ReqOrderInsert结构说明：

| 字段名            | 数据类型                                     | 说明                                       |
| -------------- | ---------------------------------------- | ---------------------------------------- |
| nReqId         | int                                      | 请求ID（由用户维护的ID）                           |
| nStragetyId    | int64_t                                  | 保留字段                                     |
| nUserInt       | int                                      | 保留字段                                     |
| nUserDouble    | double                                   | 保留字段                                     |
| szUseStr       | [TD_Text]( typedef char TD_Text[128])    | 保留字段                                     |
| nUserId        | int64_t                                  | 用户帐号Id(API自动内部赋值)                        |
| szClientId     | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号(由服务器生成并赋值)                         |
| szContractCode | [TD_CodeType](typedef char TD_CodeType[32]) | 证券合约代码                                   |
| szContractName | [TD_CodeName]( typedef char TD_CodeName[32] ) | 证券合约名称                                   |
| nTradeType     | TD_TradeType                             | 交易类型（参考数据字典8）                            |
| nOffsetType    | TD_OffsetType                            | 开平仓类型（ 参考数据字典9 ）                         |
| nOrderPrice    | int                                      | 委托价                                      |
| nOrderVol      | int                                      | 委托量                                      |
| nOrderNum      | int                                      | 订单分笔数                                    |
| pOrderDetail   | TD_OrderDetail*                          | 订单明细（ 如需指定资金账号下单，需要填对应的资金账号id以及下到该资金账号的委托数量 ） |
| nCloseR        | int                                      | 是否是风控强平（ 0正常平仓,1为风控干预平仓,2为服务器风控策略达到强平位平仓 ） |

TD_OrderDetail结构说明

| 字段名               | 数据类型                                     | 说明                              |
| ----------------- | ---------------------------------------- | ------------------------------- |
| szOrderStreamId   | [TD_OrderIdType]( typedef char TD_OrderIdType[64] ) | 委托编号（broker 或交易所的唯一编号）          |
| nAccountId        | int                                      | 券商资金账户Id                        |
| szAccountNickName | [TD_AccountType]( typedef char TD_AccountType[64]) | 资金账户别名                          |
| nOrderVol         | int                                      | 委托申报量                           |
| nDealedPrice      | int                                      | 成交均价  * 10000                   |
| nDealedVol        | int                                      | 成交量                             |
| nWithDrawnVol     | int                                      | 撤单数量                            |
| szOrderTime       | [TD_ISODateTimeType]( typedef char TD_ISODateTimeType[21] ) | 委托时间 ( 格式 yyyy-MM-dd hh:mm:ss ) |
| nStatus           | TD_OrderStatusType                       | 状态                              |
| szText            | [TD_Text]( typedef char TD_Text[128] )   | 备注                              |
| nFee              | double                                   | 手续费                             |

### 1.2.2 撤单

接口原型：

```c++
int reqOrderDelete(TD_ReqOrderDelete* req)
```

参数说明：

| 参数名称 | 数据类型               | 说明                        |
| ---- | ------------------ | ------------------------- |
| req  | TD_ReqOrderDelete* | 撤单数据信息                    |
| 返回值  | int                | 返回不为0，请求失败， 错误码（参考数据字典11） |
|      |                    |                           |

TD_ReqOrderDelete结构说明：

| 字段名             | 数据类型                                     | 说明                     |
| --------------- | ---------------------------------------- | ---------------------- |
| nReqId          | int                                      | 请求ID（由用户维护的ID）         |
| nStragetyId     | int64_t                                  | 保留字段                   |
| nUserInt        | int                                      | 保留字段                   |
| nUserDouble     | double                                   | 保留字段                   |
| szUseStr        | [TD_Text](%20typedef%20char%20TD_Text%5B128%5D) | 保留字段                   |
| nUserId         | int64_t                                  | 用户帐号Id(API自动内部赋值)      |
| szClientId      | [TD_ClientIdType](typedef%20char%20TD_ClientIdType%5B128%5D) | 客户端编号(由服务器生成并赋值)       |
| nOrderId        | int64_t                                  | 原始订单服务器唯一Id            |
| szOrderStreamId | [TD_OrderIdType]( typedef char TD_OrderIdType[64] ) | 委托编号（broker 或交易所的唯一编号） |
[注]: szOrderStreamId允许为空，为空时默认撤nOrderId下所有子单

### 1.2.3 查询委托

接口原型：

```c++
int reqQryOrder(TD_ReqQryOrder* req) 
```

参数说明：

| 参数名称 | 数据类型            | 说明                        |
| ---- | --------------- | ------------------------- |
| req  | TD_ReqQryOrder* | 查询委托数据信息                  |
| 返回值  | int             | 返回不为0，请求失败， 错误码（参考数据字典11） |
|      |                 |                           |

TD_ReqQryOrder结构说明：

| 字段名            | 数据类型                                     | 说明                |
| -------------- | ---------------------------------------- | ----------------- |
| nReqId         | int                                      | 请求ID（由用户维护的ID）    |
| nStragetyId    | int64_t                                  | 保留字段              |
| nUserInt       | int                                      | 保留字段              |
| nUserDouble    | double                                   | 保留字段              |
| szUseStr       | [TD_Text](%20typedef%20char%20TD_Text%5B128%5D) | 保留字段              |
| nUserId        | int64_t                                  | 用户帐号Id(API自动内部赋值) |
| szClientId     | [TD_ClientIdType](typedef%20char%20TD_ClientIdType%5B128%5D) | 客户端编号(由服务器生成并赋值)  |
| szContractCode | [TD_CodeType]( typedef char TD_CodeType[32] ) | 证券合约代码            |
| nIndex         | int                                      | 起始位置(不填默认从头开始)    |
| nNum           | int                                      | 数量（不填默认查全部）       |

### 1.2.4 查询成交明细

接口原型：

```c++
int reqQryMatch(TD_ReqQryMatch* req) 
```

参数说明：

| 参数名称 | 数据类型            | 说明                        |
| ---- | --------------- | ------------------------- |
| req  | TD_ReqQryMatch* | 查询成交数据信息                  |
| 返回值  | int             | 返回不为0，请求失败， 错误码（参考数据字典11） |
|      |                 |                           |

TD_ReqQryMatch结构说明：

| 字段名            | 数据类型                                     | 说明                |
| -------------- | ---------------------------------------- | ----------------- |
| nReqId         | int                                      | 请求ID（由用户维护的ID）    |
| nStragetyId    | int64_t                                  | 保留字段              |
| nUserInt       | int                                      | 保留字段              |
| nUserDouble    | double                                   | 保留字段              |
| szUseStr       | [TD_Text](%20typedef%20char%20TD_Text%5B128%5D) | 保留字段              |
| nUserId        | int64_t                                  | 用户帐号Id(API自动内部赋值) |
| szClientId     | [TD_ClientIdType](typedef%20char%20TD_ClientIdType%5B128%5D) | 客户端编号(由服务器生成并赋值)  |
| szContractCode | [TD_CodeType]( typedef char TD_CodeType[32] ) | 证券合约代码            |
| nIndex         | int                                      | 起始位置(不填默认从头开始)    |
| nNum           | int                                      | 数量（不填默认查全部）       |

### 1.2.5 查询持仓

接口原型：

```c++
int reqQryPosition(TD_ReqQryPosition* req) 
```

参数说明：

| 参数名称 | 数据类型               | 说明                        |
| ---- | ------------------ | ------------------------- |
| req  | TD_ReqQryPosition* | 查询持仓数据信息                  |
| 返回值  | int                | 返回不为0，请求失败， 错误码（参考数据字典11） |
|      |                    |                           |

TD_ReqQryPosition结构说明：

| 字段名            | 数据类型                                     | 说明                |
| -------------- | ---------------------------------------- | ----------------- |
| nReqId         | int                                      | 请求ID（由用户维护的ID）    |
| nStragetyId    | int64_t                                  | 保留字段              |
| nUserInt       | int                                      | 保留字段              |
| nUserDouble    | double                                   | 保留字段              |
| szUseStr       | [TD_Text](%20typedef%20char%20TD_Text%5B128%5D) | 保留字段              |
| nUserId        | int64_t                                  | 用户帐号Id(API自动内部赋值) |
| szClientId     | [TD_ClientIdType](typedef%20char%20TD_ClientIdType%5B128%5D) | 客户端编号(由服务器生成并赋值)  |
| szContractCode | [TD_CodeType]( typedef char TD_CodeType[32] ) | 证券合约代码            |

### 1.2.6 查询最大可委托量 

接口原型：

```c++
int reqQryMaxEntrustCount(TD_ReqQryMaxEntrustCount* req) 
```

参数说明：

| 参数名称 | 数据类型                      | 说明                        |
| ---- | ------------------------- | ------------------------- |
| req  | TD_ReqQryMaxEntrustCount* |                           |
| 返回值  | int                       | 返回不为0，请求失败， 错误码（参考数据字典11） |
|      |                           |                           |

TD_ReqQryMaxEntrustCount结构说明：

| 字段名            | 数据类型                                     | 说明                |
| -------------- | ---------------------------------------- | ----------------- |
| nReqId         | int                                      | 请求ID（由用户维护的ID）    |
| nStragetyId    | int64_t                                  | 保留字段              |
| nUserInt       | int                                      | 保留字段              |
| nUserDouble    | double                                   | 保留字段              |
| szUseStr       | [TD_Text](%20typedef%20char%20TD_Text%5B128%5D) | 保留字段              |
| nUserId        | int64_t                                  | 用户帐号Id(API自动内部赋值) |
| szClientId     | [TD_ClientIdType](typedef%20char%20TD_ClientIdType%5B128%5D) | 客户端编号(由服务器生成并赋值)  |
| szContractCode | [TD_CodeType]( typedef char TD_CodeType[32] ) | 证券合约代码            |

### 1.2.7 查询资金账号最大可委托量  

接口原型：

```c++
int reqQryAccountMaxEntrustCount(TD_ReqQryAccountMaxEntrustCount* req) 
```

参数说明：

| 参数名称 | 数据类型                             | 说明                        |
| ---- | -------------------------------- | ------------------------- |
| req  | TD_ReqQryAccountMaxEntrustCount* |                           |
| 返回值  | int                              | 返回不为0，请求失败， 错误码（参考数据字典11） |
|      |                                  |                           |

TD_ReqQryAccountMaxEntrustCount结构说明：

| 字段名            | 数据类型                                     | 说明                |
| -------------- | ---------------------------------------- | ----------------- |
| nReqId         | int                                      | 请求ID（由用户维护的ID）    |
| nStragetyId    | int64_t                                  | 保留字段              |
| nUserInt       | int                                      | 保留字段              |
| nUserDouble    | double                                   | 保留字段              |
| szUseStr       | [TD_Text](%20typedef%20char%20TD_Text%5B128%5D) | 保留字段              |
| nUserId        | int64_t                                  | 用户帐号Id(API自动内部赋值) |
| szClientId     | [TD_ClientIdType](typedef%20char%20TD_ClientIdType%5B128%5D) | 客户端编号(由服务器生成并赋值)  |
| szContractCode | [TD_CodeType]( typedef char TD_CodeType[32] ) | 股票代码              |
| nAccountId     | int                                      | 资金账号              |

### 1.2.8 订阅最大可委托量推送 

接口原型：

```c++
int reqSubscribeMaxEntrustCount() 
```

参数说明：

| 参数名称 | 数据类型 | 说明                        |
| ---- | ---- | ------------------------- |
| 返回值  | int  | 返回不为0，请求失败， 错误码（参考数据字典11） |
|      |      |                           |

## 1.3 行情接口说明 
### 1.3.1 请求交易日列表   

接口原型：

```c++
int ReqTradingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, MD_ISODateTimeType szBeginDay, MD_ISODateTimeType szEndDay)
```

参数说明：

| 参数名称         | 数据类型                                     | 说明                                       |
| ------------ | ---------------------------------------- | ---------------------------------------- |
| nReqID       | [MD_ReqID]( typedef long MD_ReqID )      | 消息请求序号                                   |
| pWindCode    | const [MD_CodeType]( typedef char MD_CodeType[32] )  * | 指定的股票代码列表 ( 如果调用者为pWindCode插入的是动态内存, 由调用者负责释放, 本接口内部不作释放处理 ) |
| nWindCodeNum | long                                     | 指定的股票代码数量                                |
| szBeginDay   | [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] ) | 指定的起始日期 (格式 yyyy-MM-dd hh:mm:ss)         |
| szEndDay     | [MD_ISODateTimeType](typedef char MD_ISODateTimeType[21]) | 指定的结束日期 (格式 yyyy-MM-dd hh:mm:ss)         |
| 返回值          | int                                      |                                          |
|              |                                          |                                          |

### 1.3.2 请求停牌日列表    

接口原型：

```c++
int ReqHaltingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, MD_ISODateTimeType szBeginDay, MD_ISODateTimeType szEndDay)
```

参数说明：

| 参数名称         | 数据类型                                     | 说明                                       |
| ------------ | ---------------------------------------- | ---------------------------------------- |
| nReqID       | [MD_ReqID]( typedef long MD_ReqID )      | 消息请求序号                                   |
| pWindCode    | const [MD_CodeType]( typedef char MD_CodeType[32] )  * | 指定的股票代码列表 ( 如果调用者为pWindCode插入的是动态内存, 由调用者负责释放, 本接口内部不作释放处理 ) |
| nWindCodeNum | long                                     | 指定的股票代码数量                                |
| szBeginDay   | [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] ) | 指定的起始日期 (格式 yyyy-MM-dd hh:mm:ss)         |
| szEndDay     | [MD_ISODateTimeType](typedef char MD_ISODateTimeType[21]) | 指定的结束日期 (格式 yyyy-MM-dd hh:mm:ss)         |
| 返回值          | int                                      |                                          |
|              |                                          |                                          |

### 1.3.3 请求订阅行情 

接口原型：

```c++
int ReqSubQuote(MD_ReqID nReqID, MD_SubType nSubType, MD_CycType nCycType, const MD_CodeType *pSubWindCode, long nSubWindCodeNum, MD_ISODateTimeType szBeginTime, MD_ISODateTimeType szEndTime)
```

参数说明：

| 参数名称            | 数据类型                                     | 说明                                       |
| --------------- | ---------------------------------------- | ---------------------------------------- |
| nReqID          | [MD_ReqID]( typedef long MD_ReqID )      | 消息请求序号                                   |
| nSubType        | MD_SubType                               | 订阅行情类型 (参照数据字典7)                         |
| nCycType        | MD_CycType                               | K线周期类型 (参照数据字典6)                         |
| pSubWindCode    | const [MD_CodeType]( typedef char MD_CodeType[32] )  * | 指定的股票代码列表 ( 如果调用者为pWindCode插入的是动态内存, 由调用者负责释放, 本接口内部不作释放处理 ) |
| nSubWindCodeNum | long                                     | 指定的股票代码数量                                |
| szBeginTime     | [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] ) | 指定的起始时间  (格式 yyyy-MM-dd hh:mm:ss)        |
| szEndTime       | [MD_ISODateTimeType](typedef char MD_ISODateTimeType[21]) | 指定的结束时间  (格式 yyyy-MM-dd hh:mm:ss)        |
| 返回值             | int                                      | 返回不为0，请求失败，错误码（参考数据字典11）                 |
|                 |                                          |                                          |



## 1.4 系统回调接口说明

### 1.4.1 业务服务器连接通知  

接口原型：

```c++
void OnConnect(int nSrvType) 
```

参数说明：

| 参数名称     | 数据类型 | 说明                |
| -------- | ---- | ----------------- |
| nSrvType | int  | 业务服务器类型 （参考数据字典3） |
| 返回值      | void |                   |

[^注]: 业务服务器连通时主动通知 



### 1.4.2 业务服务器断开通知 

接口原型：

```c++
void OnDisconnect(int nSrvType)
```

参数说明：

| 参数名称     | 数据类型 | 说明                |
| -------- | ---- | ----------------- |
| nSrvType | int  | 业务服务器类型 （参考数据字典3） |
| 返回值      | void |                   |

[^注]: 业务服务器断开时主动通知 

### 1.4.3 通知用户信息 

接口原型：

```c++
void onRtnUserInfo(const PT_QuantUserBase* pInfo)
```

参数说明：

| 参数名称  | 数据类型                    | 说明   |
| ----- | ----------------------- | ---- |
| pInfo | const PT_QuantUserBase* | 用户信息 |
| 返回值   | void                    |      |

PT_QuantUserBase 结构说明

| 参数名称          | 数据类型             | 说明             |
| ------------- | ---------------- | -------------- |
| nId           | int64_t          |                |
| szUserName    | char[128]        | 用户名            |
| szNickName    | char[128]        | 用户别名           |
| nGroupId      | int              | 组ID            |
| nUserRole     | PT_QuantUserType | 用户角色 (参照数据字典4) |
| nStampTax     | double           | 印花税            |
| nTransferFees | double           | 过户费            |
| nCommissions  | double           | 佣金             |
|               |                  |                |

## 1.5 交易回调接口说明

### 1.5.1 下单回调 

接口原型：

```c++
void onRspOrderInsert(const TD_RspOrderInsert *rsp, int error)
```

参数说明：

| 参数名称  | 数据类型                     | 说明                          |
| ----- | ------------------------ | --------------------------- |
| rsp   | const TD_RspOrderInsert* | 回调信息                        |
| error | int                      | 下单是否成功，非0代表失败，错误码参考（数据字典11） |
| 返回值   | void                     |                             |

TD_RspOrderInsert结构说明

| 字段名                | 数据类型                                     | 说明                                       |
| ------------------ | ---------------------------------------- | ---------------------------------------- |
| nReqId             | int                                      | 请求ID（由用户维护的ID）                           |
| nStragetyId        | int64_t                                  | 保留字段                                     |
| nUserInt           | int                                      | 保留字段                                     |
| nUserDouble        | double                                   | 保留字段                                     |
| szUseStr           | [TD_Text]( typedef char TD_Text[128])    | 保留字段                                     |
| nUserId            | int64_t                                  | 用户帐号Id                                   |
| szClientId         | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号                                    |
| szContractCode     | [TD_CodeType](typedef char TD_CodeType[32]) | 证券合约代码                                   |
| szContractName     | [TD_CodeName]( typedef char TD_CodeName[32] ) | 证券合约名称                                   |
| nTradeType         | TD_TradeType                             | 交易类型（参考数据字典8）                            |
| nOffsetType        | TD_OffsetType                            | 开平仓类型（参考数据字典9）                           |
| nOrderPrice        | int                                      | 委托价                                      |
| nOrderVol          | int                                      | 委托量                                      |
| nOrderNum          | int                                      | 订单分笔数                                    |
| pOrderDetail       | TD_OrderDetail*                          | 订单明细（参照1.2.1数据结构说明）                      |
| nCloseR            | int                                      | 是否是风控强平（ 0正常平仓,1为风控干预平仓,2为服务器风控策略达到强平位平仓 ） |
| nOrderOwnerId      | int64_t                                  | 订单所属用户UserId                             |
| nOrderId           | int64_t                                  | 委托单号（服务器生成，当日唯一）                         |
| nSubmitVol         | int                                      | 提交申报量（已报到券商的数量）                          |
| nDealedPrice       | int                                      | 成交均价  * 10000                            |
| nDealedVol         | int                                      | 成交总量                                     |
| nTotalWithDrawnVol | int                                      | 撤单总量                                     |
| nInValid           | int                                      | 废单数量                                     |
| nStatus            | TD_OrderStatusType                       | 状态 （参考数据字典10）                            |
| szInsertTime       | TD_ISODateTimeType                       | 下单时间 （ 格式 yyyy-MM-dd hh:mm:ss ）          |
| nFee               | double                                   | 手续费                                      |

### 1.5.2 撤单回调 

接口原型：

```c++
void onRspOrderDelete(const TD_RspOrderDelete *rsp, int error)
```

参数说明：

| 参数名称  | 数据类型                       | 说明                          |
| ----- | -------------------------- | --------------------------- |
| rsp   | const  TD_RspOrderDelete * | 回调信息                        |
| error | int                        | 撤单是否成功，非0代表失败，错误码参考（数据字典11） |
| 返回值   | void                       |                             |

TD_RspOrderDelete 结构说明

| 字段名             | 数据类型                                     | 说明                     |
| --------------- | ---------------------------------------- | ---------------------- |
| nReqId          | int                                      | 请求ID（由用户维护的ID）         |
| nStragetyId     | int64_t                                  | 保留字段                   |
| nUserInt        | int                                      | 保留字段                   |
| nUserDouble     | double                                   | 保留字段                   |
| szUseStr        | [TD_Text](%20typedef%20char%20TD_Text%5B128%5D) | 保留字段                   |
| nUserId         | int64_t                                  | 用户帐号Id                 |
| szClientId      | [TD_ClientIdType](typedef%20char%20TD_ClientIdType%5B128%5D) | 客户端编号                  |
| nOrderId        | int64_t                                  | 原始订单服务器唯一Id            |
| szOrderStreamId | [TD_OrderIdType]( typedef char TD_OrderIdType[64] ) | 委托编号（broker 或交易所的唯一编号） |



### 1.5.3 查询委托回调 

接口原型：

```c++
void onRspQryOrder(const TD_RspQryOrder *rsp, int error, bool isEnd)
```

[^注]: 该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息 

参数说明：

| 参数名称  | 数据类型                   | 说明                          |
| ----- | ---------------------- | --------------------------- |
| rsp   | const  TD_RspQryOrder* | 回调信息                        |
| error | int                    | 查询是否成功，非0代表失败，错误码参考（数据字典11） |
| isEnd | bool                   | 是否是最后一条                     |
| 返回值   | void                   |                             |

TD_RspQryOrder结构说明

| 字段名                | 数据类型                                     | 说明                                       |
| ------------------ | ---------------------------------------- | ---------------------------------------- |
| nReqId             | int                                      | 请求ID（由用户维护的ID）                           |
| nStragetyId        | int64_t                                  | 保留字段                                     |
| nUserInt           | int                                      | 保留字段                                     |
| nUserDouble        | double                                   | 保留字段                                     |
| szUseStr           | [TD_Text]( typedef char TD_Text[128])    | 保留字段                                     |
| nUserId            | int64_t                                  | 用户帐号Id                                   |
| szClientId         | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号                                    |
| szContractCode     | [TD_CodeType](typedef char TD_CodeType[32]) | 证券合约代码                                   |
| szContractName     | [TD_CodeName]( typedef char TD_CodeName[32] ) | 证券合约名称                                   |
| nTradeType         | TD_TradeType                             | 交易类型（参考数据字典8）                            |
| nOffsetType        | TD_OffsetType                            | 开平仓类型（参考数据字典9）                           |
| nOrderPrice        | int                                      | 委托价                                      |
| nOrderVol          | int                                      | 委托量                                      |
| nOrderNum          | int                                      | 订单分笔数                                    |
| pOrderDetail       | TD_OrderDetail*                          | 订单明细（参照1.1.8数据结构说明）                      |
| nCloseR            | int                                      | 是否是风控强平（ 0正常平仓,1为风控干预平仓,2为服务器风控策略达到强平位平仓 ） |
| nOrderOwnerId      | int64_t                                  | 订单所属用户UserId                             |
| nOrderId           | int64_t                                  | 委托单号                                     |
| nSubmitVol         | int                                      | 提交申报量                                    |
| nDealedPrice       | int                                      | 成交均价  * 10000                            |
| nDealedVol         | int                                      | 成交总量                                     |
| nTotalWithDrawnVol | int                                      | 撤单总量                                     |
| nInValid           | int                                      | 废单数量                                     |
| nStatus            | TD_OrderStatusType                       | 状态 （参考数据字典10）                            |
| szInsertTime       | TD_ISODateTimeType                       | 下单时间 （ 格式 yyyy-MM-dd hh:mm:ss ）          |
| nFee               | double                                   | 手续费                                      |
| nIndex             | int                                      |                                          |

### 1.5.4 查询成交明细回调 

接口原型：

```c++
void onRspQryMatch(const TD_RspQryMatch *rsp, int error, bool isEnd)
```

[^注]: 该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息 

参数说明：

| 参数名称  | 数据类型                   | 说明                          |
| ----- | ---------------------- | --------------------------- |
| rsp   | const  TD_RspQryOrder* | 回调信息                        |
| error | int                    | 查询是否成功，非0代表失败，错误码参考（数据字典11） |
| isEnd | bool                   | 是否是最后一条                     |
| 返回值   | void                   |                             |

TD_RspQryMatch结构说明

| 字段名               | 数据类型                                     | 说明                             |
| ----------------- | ---------------------------------------- | ------------------------------ |
| nReqId            | int                                      | 请求ID（由用户维护的ID）                 |
| nStragetyId       | int64_t                                  | 保留字段                           |
| nUserInt          | int                                      | 保留字段                           |
| nUserDouble       | double                                   | 保留字段                           |
| szUseStr          | [TD_Text]( typedef char TD_Text[128])    | 保留字段                           |
| nUserId           | int64_t                                  | 用户帐号Id                         |
| szClientId        | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号                          |
| nOrderId          | int64_t                                  | 委托单号（服务器唯一ID）                  |
| szOrderStreamId   | [TD_OrderIdType]( typedef char TD_OrderIdType[64] ) | 委托编号（broker 或交易所的唯一编号）         |
| nMatchStreamId    | int64_t                                  | 系统编号                           |
| nMatchPrice       | double                                   | 成交价 * 10000                    |
| nMatchVol         | int                                      | 成交量                            |
| szContractCode    | [TD_CodeType]( typedef char TD_CodeType[32] ) | 证券合约代码                         |
| szContractName    | [TD_CodeName]( typedef char TD_CodeName[32] ) | 证券合约名称                         |
| szMatchTime       | [TD_ISODateTimeType]( typedef char TD_ISODateTimeType[21] ) | 成交时间 ( 格式 yyyy-MM-dd hh:mm:ss) |
| nTradeType        | TD_TradeType                             | 交易类型 (参照数据字典8)                 |
| nAccountId        | int                                      | 券商资金账户Id                       |
| szAccountNickName | [TD_AccountType]( typedef char TD_AccountType[64] ) | 资金账户别名                         |
| nIndex            | int                                      |                                |

### 1.5.5 查询持仓回调 

接口原型：

```c++
void onRspQryPosition(const TD_RspQryPosition *rsp, int error, bool isEnd)
```

[^注]: 该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息 

参数说明：

| 参数名称  | 数据类型                      | 说明                          |
| ----- | ------------------------- | --------------------------- |
| rsp   | const  TD_RspQryPosition* | 回调信息                        |
| error | int                       | 查询是否成功，非0代表失败，错误码参考（数据字典11） |
| isEnd | bool                      | 是否是最后一条                     |
| 返回值   | void                      |                             |

TD_RspQryPosition结构说明

| 字段名            | 数据类型                                     | 说明             |
| -------------- | ---------------------------------------- | -------------- |
| nReqId         | int                                      | 请求ID（由用户维护的ID） |
| nStragetyId    | int64_t                                  | 保留字段           |
| nUserInt       | int                                      | 保留字段           |
| nUserDouble    | double                                   | 保留字段           |
| szUseStr       | [TD_Text]( typedef char TD_Text[128])    | 保留字段           |
| nUserId        | int64_t                                  | 用户帐号Id         |
| szClientId     | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号          |
| szContractCode | [TD_CodeType]( typedef char TD_CodeType[32] ) | 证券合约代码         |
| nPosition      | int                                      | 持仓总量           |
| nPrice         | double                                   | 持仓均价 * 10000   |
| nProfit        | double                                   | 浮盈             |
| nSelltleProfit | double                                   | 已结算的盈利         |

### 1.5.6 查询最大可委托量回调 

接口原型：

```c++
void onRspQryMaxEntrustCount(const TD_RspQryMaxEntrustCount* rsp, int error, bool isEnd)
```

[^注]: 该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息 

参数说明：

| 参数名称  | 数据类型                             | 说明                          |
| ----- | -------------------------------- | --------------------------- |
| rsp   | const  TD_RspQryMaxEntrustCount* | 回调信息                        |
| error | int                              | 查询是否成功，非0代表失败，错误码参考（数据字典11） |
| isEnd | bool                             | 是否是最后一条                     |
| 返回值   | void                             |                             |

TD_RspQryMaxEntrustCount结构说明

| 字段名                   | 数据类型                                     | 说明             |
| --------------------- | ---------------------------------------- | -------------- |
| nReqId                | int                                      | 请求ID（由用户维护的ID） |
| nStragetyId           | int64_t                                  | 保留字段           |
| nUserInt              | int                                      | 保留字段           |
| nUserDouble           | double                                   | 保留字段           |
| szUseStr              | [TD_Text]( typedef char TD_Text[128])    | 保留字段           |
| nUserId               | int64_t                                  | 用户帐号Id         |
| szClientId            | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号          |
| pStockMaxEntrustCount | StockMaxEntrustCount                     | 可委托数量          |

StockMaxEntrustCount 结构说明

| 字段名            | 数据类型                                     | 说明      |
| -------------- | ---------------------------------------- | ------- |
| szContractCode | [TD_CodeType]( typedef char TD_CodeType[32] ) | 证券合约代码  |
| nMaxBuyCaptial | double                                   | 最大可买资金量 |
| nMaxSellVol    | int                                      | 最大可卖    |

### 1.5.7 查询资金账号最大可委托量回调 

接口原型：

```c++
void onRspQryAccountMaxEntrustCount(const TD_RspQryAccountMaxEntrustCount* rsp, int error, bool isEnd)
```

[^注]: 该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息 

参数说明：

| 参数名称  | 数据类型                                    | 说明                          |
| ----- | --------------------------------------- | --------------------------- |
| rsp   | const  TD_RspQryAccountMaxEntrustCount* | 回调信息                        |
| error | int                                     | 查询是否成功，非0代表失败，错误码参考（数据字典11） |
| isEnd | bool                                    | 是否是最后一条                     |
| 返回值   | void                                    |                             |

TD_RspQryAccountMaxEntrustCount结构说明

| 字段名                   | 数据类型                                     | 说明                   |
| --------------------- | ---------------------------------------- | -------------------- |
| nReqId                | int                                      | 请求ID（由用户维护的ID）       |
| nStragetyId           | int64_t                                  | 保留字段                 |
| nUserInt              | int                                      | 保留字段                 |
| nUserDouble           | double                                   | 保留字段                 |
| szUseStr              | [TD_Text]( typedef char TD_Text[128])    | 保留字段                 |
| nUserId               | int64_t                                  | 用户帐号Id               |
| szClientId            | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号                |
| nAccountId            | int                                      | 资金账号                 |
| szAccountNickName     | [TD_AccountType]( typedef char TD_AccountType[64] ) | 资金账户别名               |
| nNum                  | int                                      | 可用股票数                |
| pStockMaxEntrustCount | StockMaxEntrustCount *                   | 指针偏移 (参照1.2.8数据结构说明) |
| bStatus               | bool                                     | 资金通道是否可用             |
| nAvailableCaptial     | int                                      | 资金账号层面可用资金           |

### 1.5.8 订单状态改变推送

接口原型：

```c++
void onRtnOrderStatusChangeNotice(const TD_RtnOrderStatusChangeNotice *notice)
```

[^注]: 该接口在订单状态改变时被调用 

参数说明：

| 参数名称 | 数据类型                                  | 说明           |
| ---- | ------------------------------------- | ------------ |
| rsp  | const  TD_RtnOrderStatusChangeNotice* | 回调信息（参照数据字典） |
| 返回值  | void                                  |              |

TD_RtnOrderStatusChangeNotice结构说明

| 字段名                | 数据类型                                     | 说明                                       |
| ------------------ | ---------------------------------------- | ---------------------------------------- |
| nReqId             | int                                      | 请求ID（由用户维护的ID）                           |
| nStragetyId        | int64_t                                  | 保留字段                                     |
| nUserInt           | int                                      | 保留字段                                     |
| nUserDouble        | double                                   | 保留字段                                     |
| szUseStr           | [TD_Text]( typedef char TD_Text[128])    | 保留字段                                     |
| nUserId            | int64_t                                  | 用户帐号Id                                   |
| szClientId         | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号                                    |
| szContractCode     | [TD_CodeType](typedef char TD_CodeType[32]) | 证券合约代码                                   |
| szContractName     | [TD_CodeName]( typedef char TD_CodeName[32] ) | 证券合约名称                                   |
| nTradeType         | TD_TradeType                             | 交易类型（参考数据字典8）                            |
| nOffsetType        | TD_OffsetType                            | 开平仓类型（参考数据字典9）                           |
| nOrderPrice        | int                                      | 委托价                                      |
| nOrderVol          | int                                      | 委托量                                      |
| nOrderNum          | int                                      | 订单分笔数                                    |
| pOrderDetail       | TD_OrderDetail*                          | 订单明细（参照1.1.8数据结构说明）                      |
| nCloseR            | int                                      | 是否是风控强平（ 0正常平仓,1为风控干预平仓,2为服务器风控策略达到强平位平仓 ） |
| nOrderOwnerId      | int64_t                                  | 订单所属用户UserId                             |
| nOrderId           | int64_t                                  | 委托单号                                     |
| nSubmitVol         | int                                      | 提交申报量                                    |
| nDealedPrice       | int                                      | 成交均价  * 10000                            |
| nDealedVol         | int                                      | 成交总量                                     |
| nTotalWithDrawnVol | int                                      | 撤单总量                                     |
| nInValid           | int                                      | 废单数量                                     |
| nStatus            | TD_OrderStatusType                       | 状态 （参考数据字典10）                            |
| szInsertTime       | TD_ISODateTimeType                       | 下单时间 （ 格式 yyyy-MM-dd hh:mm:ss ）          |
| nFee               | double                                   | 手续费                                      |



### 1.5.9 成交明细推送

接口原型：

```c++
void onRtnOrderMatchNotice(const TD_RtnOrderMatchNotice *notice)
```

[^注]: 该接口在订单发生成交时被调用，推送成交明细 

参数说明：

| 参数名称 | 数据类型                           | 说明   |
| ---- | ------------------------------ | ---- |
| rsp  | const  TD_RtnOrderMatchNotice* | 回调信息 |
| 返回值  | void                           |      |

TD_RtnOrderMatchNotice结构说明

| 字段名               | 数据类型                                     | 说明                             |
| ----------------- | ---------------------------------------- | ------------------------------ |
| nReqId            | int                                      | 请求ID（由用户维护的ID）                 |
| nStragetyId       | int64_t                                  | 保留字段                           |
| nUserInt          | int                                      | 保留字段                           |
| nUserDouble       | double                                   | 保留字段                           |
| szUseStr          | [TD_Text]( typedef char TD_Text[128])    | 保留字段                           |
| nUserId           | int64_t                                  | 用户帐号Id                         |
| szClientId        | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号                          |
| nOrderId          | int64_t                                  | 委托编号（原始订单服务器唯一Id）              |
| szOrderStreamId   | [TD_OrderIdType]( typedef char TD_OrderIdType[64] ) | 委托编号（broker 或交易所的唯一编号）         |
| nMatchStreamId    | int64_t                                  | 系统编号                           |
| nMatchPrice       | double                                   | 成交价 * 10000                    |
| nMatchVol         | int                                      | 成交量                            |
| szContractCode    | [TD_CodeType]( typedef char TD_CodeType[32] ) | 证券合约代码                         |
| szContractName    | [TD_CodeName]( typedef char TD_CodeName[32] ) | 证券合约名称                         |
| szMatchTime       | [TD_ISODateTimeType]( typedef char TD_ISODateTimeType[21] ) | 成交时间 ( 格式 yyyy-MM-dd hh:mm:ss) |
| nTradeType        | TD_TradeType                             | 交易类型 (参照数据字典8)                 |
| nAccountId        | int                                      | 券商资金账户Id                       |
| szAccountNickName | [TD_AccountType]( typedef char TD_AccountType[64] ) | 资金账户别名                         |

### 1.5.10 持仓浮盈推送

接口原型：

```c++
void onRtnProfit(const TD_RtnProfit *notice)
```

[^注]: 该接口频率与Tick数据同步，推送持仓的的浮盈信息 

参数说明：

| 参数名称 | 数据类型                 | 说明   |
| ---- | -------------------- | ---- |
| rsp  | const  TD_RtnProfit* | 回调信息 |
| 返回值  | void                 |      |

TD_RtnProfit结构说明

| 字段名            | 数据类型                                     | 说明             |
| -------------- | ---------------------------------------- | -------------- |
| nReqId         | int                                      | 请求ID（由用户维护的ID） |
| nStragetyId    | int64_t                                  | 保留字段           |
| nUserInt       | int                                      | 保留字段           |
| nUserDouble    | double                                   | 保留字段           |
| szUseStr       | [TD_Text]( typedef char TD_Text[128])    | 保留字段           |
| nUserId        | int64_t                                  | 用户帐号Id         |
| szClientId     | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号          |
| szContractCode | [TD_CodeType]( typedef char TD_CodeType[32] ) | 证券合约代码         |
| nPosition      | int                                      | 持仓总量           |
| nPrice         | double                                   | 持仓均价 * 10000   |
| nProfit        | double                                   | 浮盈             |
| nSelltleProfit | double                                   | 已结算的盈利         |

### 1.5.11 用户权限信息推送 

接口原型：

```c++
void onRtnUserAuthen(const TD_QuantUserAuthen* notice)
```

[^注]: 当用户权限信息被修改时推送；登陆时也会推送一次 

参数说明：

| 参数名称 | 数据类型                       | 说明   |
| ---- | -------------------------- | ---- |
| rsp  | const  TD_QuantUserAuthen* | 回调信息 |
| 返回值  | void                       |      |

TD_QuantUserAuthen结构说明

| 字段名                        | 数据类型                                     | 说明              |
| -------------------------- | ---------------------------------------- | --------------- |
| nReqId                     | int                                      | 请求ID（由用户维护的ID）  |
| nStragetyId                | int64_t                                  | 保留字段            |
| nUserInt                   | int                                      | 保留字段            |
| nUserDouble                | double                                   | 保留字段            |
| szUseStr                   | [TD_Text]( typedef char TD_Text[128])    | 保留字段            |
| nUserId                    | int64_t                                  | 用户帐号Id          |
| szClientId                 | [TD_ClientIdType](typedef char TD_ClientIdType[128]) | 客户端编号           |
| nId                        | int64_t                                  |                 |
| nGroupId                   | int                                      | 组ID             |
| ifStopTrade                | bool                                     | 是否停机            |
| nStopTradePostion          | int                                      | 停机位(亏算资金量)      |
| nStopPercentTradePostion   | double                                   | 停机位(亏损比例)       |
| nSinglePositionHoldTime    | int                                      | 单笔持仓时间阈值        |
| nSinglePositionLoss        | int                                      | 单笔持仓亏损阈值(亏算资金量) |
| nSinglePercentPositionLoss | double                                   | 单笔持仓亏损阈值(亏损比例)  |

### 1.5.12 最大可委托量推送

接口原型：

```c++
void onRtnMaxEntrustCount(const TD_RspQryMaxEntrustCount* notice)
```

[^注]: 当用户可委托量被改变时推送 

参数说明：

| 参数名称 | 数据类型                             | 说明                  |
| ---- | -------------------------------- | ------------------- |
| rsp  | const  TD_RspQryMaxEntrustCount* | 回调信息（参照1.2.8数据结构说明） |
| 返回值  | void                             |                     |


## 1.6 行情回调接口说明
### 1.6.1 响应请求交易日列表 

接口原型：

```c++
void OnRspTradingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, MD_ISODateTimeType szBeginDay, MD_ISODateTimeType szEndDay, int nErrNo, const char *szErrMsg)
```

参数说明：

| 参数名称         | 数据类型                                     | 说明                               |
| ------------ | ---------------------------------------- | -------------------------------- |
| nReqID       | [MD_ReqID]( typedef long MD_ReqID )      | 消息请求序号                           |
| pWindCode    | const [MD_CodeType]( typedef char MD_CodeType[32] )  * | 指定的股票代码列表                        |
| nWindCodeNum | long                                     | 指定的股票代码数量                        |
| szBeginDay   | [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] ) | 指定的起始日期 (格式 yyyy-MM-dd hh:mm:ss) |
| szEndDay     | [MD_ISODateTimeType](typedef char MD_ISODateTimeType[21]) | 指定的结束日期 (格式 yyyy-MM-dd hh:mm:ss) |
| nErrNo       | int                                      | 响应失败的错误码                         |
| szErrMsg     | const char *                             | 响应失败的错误描述                        |
| 返回值          | void                                     |                                  |

### 1.6.2 响应请求停牌日列表 

接口原型：

```c++
void OnRspHaltingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, MD_ISODateTimeType szBeginDay, MD_ISODateTimeType szEndDay, int nErrNo, const char *szErrMsg)
```

[^注]: 该信号会在请求停牌日列表后主动通知

参数说明：

| 参数名称         | 数据类型                                     | 说明                               |
| ------------ | ---------------------------------------- | -------------------------------- |
| nReqID       | [MD_ReqID]( typedef long MD_ReqID )      | 消息请求序号                           |
| pWindCode    | const [MD_CodeType]( typedef char MD_CodeType[32] )  * | 指定的股票代码列表                        |
| nWindCodeNum | long                                     | 指定的股票代码数量                        |
| szBeginDay   | [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] ) | 指定的起始日期 (格式 yyyy-MM-dd hh:mm:ss) |
| szEndDay     | [MD_ISODateTimeType](typedef char MD_ISODateTimeType[21]) | 指定的结束日期 (格式 yyyy-MM-dd hh:mm:ss) |
| nErrNo       | int                                      | 响应失败的错误码                         |
| szErrMsg     | const char *                             | 响应失败的错误描述                        |
| 返回值          | void                                     |                                  |

### 1.6.3 响应请求订阅行情 

接口原型：

```c++
void OnRspSubQuote(MD_ReqID nReqID, MD_SubType nSubType, MD_CycType nCycType, const MD_CodeType *pSubWindCode, long nSubWindCodeNum, MD_ISODateTimeType szBeginTime, MD_ISODateTimeType szEndTime, int nErrNo, const char *szErrMsg)
```

[^注]: 该信号会在请求订阅行情后主动通知 

参数说明：

| 参数名称         | 数据类型                                     | 说明                               |
| ------------ | ---------------------------------------- | -------------------------------- |
| nReqID       | [MD_ReqID]( typedef long MD_ReqID )      | 消息请求序号                           |
| nSubType     | MD_SubType                               | 订阅行情类型 (参照数据字典7)                 |
| nCycType     | MD_CycType                               | K线周期类型 (参照数据字典6)                 |
| pWindCode    | const [MD_CodeType]( typedef char MD_CodeType[32] )  * | 指定的股票代码列表                        |
| nWindCodeNum | long                                     | 指定的股票代码数量                        |
| szBeginDay   | [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] ) | 指定的起始日期 (格式 yyyy-MM-dd hh:mm:ss) |
| szEndDay     | [MD_ISODateTimeType](typedef char MD_ISODateTimeType[21]) | 指定的结束日期 (格式 yyyy-MM-dd hh:mm:ss) |
| nErrNo       | int                                      | 响应失败的错误码                         |
| szErrMsg     | const char *                             | 响应失败的错误描述                        |
| 返回值          | void                                     |                                  |

### 1.6.4 通知交易代码表

接口原型：

```c++
void OnRtnTradingCode(const MD_DATA_CODE *pWindCode, long nWindCodeNum, const MD_DATA_OPTION_CODE *pOptionCode, long nOptionCodeNum)
```

参数说明：

| 参数名称           | 数据类型                        | 说明        |
| -------------- | --------------------------- | --------- |
| pWindCode      | const MD_DATA_CODE*         | 指定的股票代码表  |
| nWindCodeNum   | long                        | 指定的股票代码数量 |
| pOptionCode    | const MD_DATA_OPTION_CODE * | 指定的期权代码表  |
| nOptionCodeNum | long                        | 指定的期权代码数量 |
| 返回值            | void                        |           |

MD_DATA_CODE结构说明：

| 字段名        | 数据类型     | 说明   |
| ---------- | -------- | ---- |
| szWindCode | char[32] |      |
| szMarket   | char[8]  |      |
| szCode     | char[32] |      |
| szENName   | char[32] |      |
| szCNName   | char[32] |      |
| nType      | int      |      |

MD_DATA_OPTION_CODE 结构说明

| 字段名                     | 数据类型         | 说明                                       |
| ----------------------- | ------------ | ---------------------------------------- |
| basicCode               | MD_DATA_CODE |                                          |
| szContractID            | char[32]     | 期权合约代码                                   |
| szUnderlyingSecurityID  | char[32]     | 标的证券代码                                   |
| chCallOrPut             | char         | 认购认沽C1(认购:C”；认沽:“P” )                    |
| nExerciseDate           | int          | 期权行权日(格式：YYYYMMDD）                       |
| chUnderlyingType        | char         | 标的证券类型C3 （ 0-A股 ，1-ETF (EBS – ETF， ASH – A 股) ） |
| chOptionType            | char         | 欧式美式C1 （欧式期权：E”；美式期权：“A” ）               |
| chPriceLimitType        | char         | 跌幅限制类型C1（‘N’表示有涨跌幅限制类型, ‘R’表示无涨跌幅限制类型 ）  |
| nContractMultiplierUnit | int          | 合约单位（经过除权除息调整后的合约单位, 一定是整数 ）             |
| nExercisePrice          | int          | 期权行权价（经过除权除息调整后的期权行权价，右对齐，精确到厘 ）         |
| nStartDate              | int          | 期权首个交易日（格式：YYYYMMDD ）                    |
| nEndDate                | int          | 期权最后交易日/行权日（格式：YYYYMMDD ）                |
| nExpireDate             | int          | 期权到期日（格式：YYYYMMDD ）                      |

### 1.6.5 通知交易日列表

接口原型：

```c++
void OnRtnTradingDay(MD_ReqID nReqID, const char *szWindCode, const MD_ISODateTimeType *pDay, long nDayNum)
```

[^注]: 该信号会在请求交易日列表后主动通知 

参数说明：

| 参数名称       | 数据类型                                     | 说明                                      |
| ---------- | ---------------------------------------- | --------------------------------------- |
| nReqID     | [MD_ReqID]( typedef long MD_ReqID )      | 消息请求序号                                  |
| szWindCode | const char*                              | 指定的股票代码表  (该指针若为nullptr, 则表示整个市场的交易日列表) |
| pDay       | const [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] )* | 交易日列表  (格式 yyyy-MM-dd hh:mm:ss)         |
| nDayNum    | long                                     | 交易日个数                                   |
| 返回值        | void                                     |                                         |

### 1.6.6 通知停牌日列表

接口原型：

```c++
void OnRtnHaltingDay(MD_ReqID nReqID, const char *szWindCode, const MD_ISODateTimeType *pDay, long nDayNum)
```

[^注]: 该信号会在请求停牌日列表后主动通知 

参数说明：

| 参数名称       | 数据类型                                     | 说明                              |
| ---------- | ---------------------------------------- | ------------------------------- |
| nReqID     | [MD_ReqID]( typedef long MD_ReqID )      | 消息请求序号                          |
| szWindCode | const char*                              | 指定的股票代码表                        |
| pDay       | const [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] )* | 交易日列表  (格式 yyyy-MM-dd hh:mm:ss) |
| nDayNum    | long                                     | 交易日个数                           |
| 返回值        | void                                     |                                 |

### 1.6.7 通知个股行情

接口原型：

```c++
void OnRtnMarket(MD_ReqID nReqID, MD_DATA_MARKET *pMarket)
```

[^注]: 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知 

参数说明：

| 参数名称    | 数据类型                                | 说明        |
| ------- | ----------------------------------- | --------- |
| nReqID  | [MD_ReqID]( typedef long MD_ReqID ) | 消息请求序号    |
| pMarket | MD_DATA_MARKET*                     | 个股的行情数据地址 |
| 返回值     | void                                |           |

MD_DATA_MARKET结构说明：

| 字段名                  | 数据类型             | 说明                           |
| -------------------- | ---------------- | ---------------------------- |
| szWindCode           | char[32]         |                              |
| szCode               | char[32]         | 原始Code                       |
| nActionDay           | int              | 业务发生日(自然日)                   |
| nTime                | int              | 时间(HHMMSSmmm)                |
| nStatus              | int              | 状态                           |
| nPreClose            | unsigned int     | 前收盘价=实际价格(单位: 元/手)x10000     |
| nOpen                | unsigned int     | 开盘价=实际价格(单位: 元/手)x10000      |
| nHigh                | unsigned int     | 最高价=实际价格(单位: 元/手)x10000      |
| nLow                 | unsigned int     | 最低价=实际价格(单位: 元/手)x10000      |
| nMatch               | unsigned int     | 最新价=实际价格(单位: 元/手)x10000      |
| nAskPrice            | unsigned int[10] | 申卖价=实际价格(单位: 元/手)x10000      |
| nAskVol              | unsigned int[10] | 申卖量=实际手数(单位: 手)              |
| nBidPrice            | unsigned int[10] | 申买价=实际价格(单位: 元/手)x10000      |
| nBidVol              | unsigned int[10] | 申买量=实际手数(单位: 手)              |
| nNumTrades           | unsigned int     | 成交笔数=实际笔数(单位: 笔)             |
| iVolume              | int64_t          | 成交总量=实际手数(单位: 手)             |
| iTurnover            | int64_t          | 成交总金额=实际金额(单位: 元)            |
| nTotalBidVol         | int64_t          | 委托买入总量=实际手数(单位: 手)           |
| nTotalAskVol         | int64_t          | 委托卖出总量=实际手数(单位: 手)           |
| nWeightedAvgBidPrice | unsigned int     | 加权平均委买价格=实际价格(单位: 元/手)x10000 |
| nWeightedAvgAskPrice | unsigned int     | 加权平均委卖价格=实际价格(单位: 元/手)x10000 |
| nIOPV                | int              | IOPV净值估值                     |
| nYieldToMaturity     | int              | 到期收益率                        |
| nHighLimited         | unsigned int     | 涨停价=实际价格(单位: 元/手)x10000      |
| nLowLimited          | unsigned int     | 跌停价=实际价格(单位: 元/手)x10000      |

### 1.6.8 通知K线行情

接口原型：

```c++
void OnRtnKLine(MD_ReqID nReqID, MD_DATA_KLINE *pKLine)
```

[^注]: 该信号会在请求历史K线行情或订阅实时K线行情后主动通知 

参数说明：

| 参数名称   | 数据类型                                | 说明       |
| ------ | ----------------------------------- | -------- |
| nReqID | [MD_ReqID]( typedef long MD_ReqID ) | 消息请求序号   |
| pKLine | MD_DATA_KLINE *                     | K线行情数据地址 |
| 返回值    | void                                |          |

MD_DATA_KLINE结构说明：

| 字段名        | 数据类型                                     | 说明                           |
| ---------- | ---------------------------------------- | ---------------------------- |
| nType      | MD_CycType                               | 周期类型（参照数据字典6）                |
| szWindCode | char[32]                                 | 股票代码                         |
| szCode     | char[32]                                 | 原始Code                       |
| szDatetime | [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] ) | 时间  (格式 yyyy-MM-dd hh:mm:ss) |
| nDate      | int                                      | 日期 （格式 yyyyMMdd ）            |
| nTime      | int                                      | 时间 （格式 hhmmsszzz ）           |
| nOpen      | double                                   | 开盘价=实际价格(单位: 元/手)            |
| nHigh      | double                                   | 最高价=实际价格(单位: 元/手)            |
| nLow       | double                                   | 最低价=实际价格(单位: 元/手)            |
| nClose     | double                                   | 今收价=实际价格(单位: 元/手)            |
| nPreClose  | double                                   | 昨收价=实际价格(单位: 元/手)            |
| nHighLimit | double                                   | 涨停价=实际价格(单位: 元/手)            |
| nLowLimit  | double                                   | 跌停价=实际价格(单位: 元/手)            |
| iVolume    | int64_t                                  | 成交数量=实际手数(单位: 手)             |
| nTurover   | int64_t                                  | 成交金额=实际金额(单位: 元)             |
|            |                                          |                              |

### 1.6.9 通知指数行情

接口原型：

```c++
void OnRtnIndex(MD_ReqID nReqID, MD_DATA_INDEX *pIndex)
```

[^注]: 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知 

参数说明：

| 参数名称   | 数据类型                                | 说明       |
| ------ | ----------------------------------- | -------- |
| nReqID | [MD_ReqID]( typedef long MD_ReqID ) | 消息请求序号   |
| pIndex | MD_DATA_INDEX*                      | 指数行情数据地址 |
| 返回值    | void                                |          |

MD_DATA_INDEX数据结构说明：

| 字段名            | 数据类型     | 说明                        |
| -------------- | -------- | ------------------------- |
| szWindCode     | char[32] | 股票代码                      |
| szCode         | char[32] | 原始Code                    |
| nActionDay     | int      | 业务发生日(自然日)                |
| nTime          | int      | 时间(HHMMSSmmm)             |
| nOpenIndex     | int      | 今开盘指数=实际价格(单位: 元/手)x10000 |
| nHighIndex     | int      | 最高指数=实际价格(单位: 元/手)x10000  |
| nLowIndex      | int      | 最低指数=实际价格(单位: 元/手)x10000  |
| nLastIndex     | int      | 最新指数=实际价格(单位: 元/手)x10000  |
| iTotalVolume   | int64_t  | 参与计算相应指数的交易数量=实际手数(单位: 手) |
| iTurnover      | int64_t  | 参与计算相应指数的成交金额=实际金额(单位: 元) |
| nPreCloseIndex | int      | 前盘指数=实际价格(单位: 元/手)x10000  |

### 1.6.10 通知逐笔成交

接口原型：

```c++
void OnRtnTransaction(MD_ReqID nReqID, MD_DATA_TRANSACTION *pTrans)
```

[^注]: 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知 

参数说明：

| 参数名称   | 数据类型                                | 说明       |
| ------ | ----------------------------------- | -------- |
| nReqID | [MD_ReqID]( typedef long MD_ReqID ) | 消息请求序号   |
| pTrans | MD_DATA_TRANSACTION*                | 委托队列数据地址 |
| 返回值    | void                                |          |

MD_DATA_TRANSACTION结构说明：

| 字段名        | 数据类型     | 说明                       |
| ---------- | -------- | ------------------------ |
| szWindCode | char[32] | 股票代码                     |
| szCode     | char[32] | 原始Code                   |
| nActionDay | int      | 自然日                      |
| nTime      | int      | 时间(HHMMSSmmm)            |
| nSide      | int      | 买卖方向('B':Bid 'A':Ask)    |
| nPrice     | int      | 委托价格=实际价格(单位: 元/手)x10000 |
| nOrders    | int      | 订单数量                     |
| nABItems   | int      | 明细个数                     |
| nABVolume  | int[200] | 订单明细=实际手数(单位: 手)         |

### 1.6.11 通知委托队列

接口原型：

```c++
void OnRtnOrderQueue(MD_ReqID nReqID, MD_DATA_ORDER_QUEUE *pQueue)
```

[^注]: 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知 

参数说明：

| 参数名称   | 数据类型                                | 说明       |
| ------ | ----------------------------------- | -------- |
| nReqID | [MD_ReqID]( typedef long MD_ReqID ) | 消息请求序号   |
| pQueue | MD_DATA_ORDER_QUEUE*                | 委托队列数据地址 |
| 返回值    | void                                |          |

MD_DATA_ORDER_QUEUE结构说明：

| 字段名         | 数据类型     | 说明                         |
| ----------- | -------- | -------------------------- |
| szWindCode  | char[32] | 股票代码                       |
| szCode      | char[32] | 原始Code                     |
| nActionDay  | int      | 自然日                        |
| nTime       | int      | 成交时间(HHMMSSmmm)            |
| nIndex      | int      | 成交编号                       |
| nPrice      | int      | 成交价格=实际价格(单位: 元/手)x10000   |
| nVolume     | int      | 成交数量=实际手数(单位: 手)           |
| nTurnover   | int      | 成交金额=实际金额(单位: 元)           |
| nBSFlag     | int      | 买卖方向(买：'B', 卖：'A', 不明：' ') |
| chOrderKind | char     | 成交类别                       |
| nAskOrder   | int      | 叫卖方委托序号                    |
| nBidOrder   | int      | 叫买方委托序号                    |

### 1.6.12 通知逐笔委托

接口原型：

```c++
void OnRtnOrder(MD_ReqID nReqID, MD_DATA_ORDER *pOrder)
```

[^注]: 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知 

参数说明：

| 参数名称   | 数据类型                                | 说明       |
| ------ | ----------------------------------- | -------- |
| nReqID | [MD_ReqID]( typedef long MD_ReqID ) | 消息请求序号   |
| pOrder | MD_DATA_ORDER*                      | 逐笔委托数据地址 |
| 返回值    | void                                |          |

MD_DATA_ORDER结构说明：

| 字段名            | 数据类型     | 说明                       |
| -------------- | -------- | ------------------------ |
| szWindCode     | char[32] | 股票代码                     |
| szCode         | char[32] | 原始Code                   |
| nActionDay     | int      | 委托日期(YYYYMMDD)           |
| nTime          | int      | 委托时间(HHMMSSmmm)          |
| nOrder         | int      | 委托号                      |
| nPrice         | int      | 委托价格=实际价格(单位: 元/手)x10000 |
| nVolume        | int      | 委托数量=实际手数(单位: 手)         |
| chOrderKind    | char     | 委托类别                     |
| chFunctionCode | char     | 委托代码('B','S','C')        |

### 1.6.13 通知期货行情

接口原型：

```c++
void OnRtnFuture(MD_ReqID nReqID, MD_DATA_FUTURE *pFuture)
```

[^注]: 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知 

参数说明：

| 参数名称    | 数据类型                                | 说明       |
| ------- | ----------------------------------- | -------- |
| nReqID  | [MD_ReqID]( typedef long MD_ReqID ) | 消息请求序号   |
| pFuture | MD_DATA_FUTURE*                     | 期货行情数据地址 |
| 返回值     | void                                |          |

MD_DATA_FUTURE结构说明：

| 字段名              | 数据类型         | 说明                       |
| ---------------- | ------------ | ------------------------ |
| szWindCode       | char[32]     | 股票代码                     |
| szCode           | char[32]     | 原始Code                   |
| nActionDay       | int          | 自然日                      |
| nTime            | int          | 时间(HHMMSSmmm)            |
| nStatus          | int          | 状态                       |
| iPreOpenInterest | int64_t      | 昨持仓                      |
| nPreClose        | unsigned int | 昨收盘价=实际价格(单位: 元/手)x10000 |
| nPreSettlePrice  | unsigned int | 昨结算=实际价格(单位: 元/手)x10000  |
| nOpen            | unsigned int | 开盘价=实际价格(单位: 元/手)x10000  |
| nHigh            | unsigned int | 最高价=实际价格(单位: 元/手)x10000  |
| nLow             | unsigned int | 最低价=实际价格(单位: 元/手)x10000  |
| nMatch           | unsigned int | 最新价=实际价格(单位: 元/手)x10000  |
| iVolume          | int64_t      | 成交总量=实际手数(单位: 手)         |
| iTurnover        | int64_t      | 成交总金额=实际金额(单位: 元)        |
| iOpenInterest    | int64_t      | 持仓总量=实际手数(单位: 手)         |
| nClose           | unsigned int | 今收盘=实际价格(单位: 元/手)x10000  |
| nSettlePrice     | unsigned int | 今结算=实际价格(单位: 元/手)x10000  |
| nHighLimited     | unsigned int | 涨停价=实际价格(单位: 元/手)x10000  |
| nLowLimited      | unsigned int | 跌停价=实际价格(单位: 元/手)x10000  |
| nAskPrice        | unsigned int | 申卖价=实际价格(单位: 元/手)x10000  |
| nAskVol          | unsigned int | 申卖量=实际手数(单位: 手)          |
| nBidPrice        | unsigned int | 申买价=实际价格(单位: 元/手)x10000  |
| nBidVol          | unsigned int | 申买量=实际手数(单位: 手)          |

### 1.6.14 通知期权行情

接口原型：

```c++
void OnRtnFutureOption(MD_ReqID nReqID, MD_DATA_FUTURE *pOption)
```

[^注]: 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知 

参数说明：

| 参数名称    | 数据类型                                | 说明                        |
| ------- | ----------------------------------- | ------------------------- |
| nReqID  | [MD_ReqID]( typedef long MD_ReqID ) | 消息请求序号                    |
| pOption | MD_DATA_FUTURE *                    | 期货行情数据地址 （参照1.2.27数据结构说明） |
| 返回值     | void                                |                           |

### 1.6.15 通知开市消息

接口原型：

```c++
void OnRtnDayBegin(MD_ReqID nReqID, MD_ISODateTimeType pDate)
```

[^注]: 该信号会在请求历史行情或订阅实时行情后主动通知 

参数说明：

| 参数名称   | 数据类型                                     | 说明                              |
| ------ | ---------------------------------------- | ------------------------------- |
| nReqID | [MD_ReqID]( typedef long MD_ReqID )      | 消息请求序号                          |
| pDate  | [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] ) | 开市日期地址 (格式 yyyy-MM-dd hh:mm:ss) |
| 返回值    | void                                     |                                 |

### 1.6.16 通知闭市消息

接口原型：

```c++
void OnRtnDayEnd(MD_ReqID nReqID, MD_ISODateTimeType pDate)
```

[^注]: 该信号会在请求历史行情或订阅实时行情后主动通知 

参数说明：

| 参数名称   | 数据类型                                     | 说明                               |
| ------ | ---------------------------------------- | -------------------------------- |
| nReqID | [MD_ReqID]( typedef long MD_ReqID )      | 消息请求序号                           |
| pDate  | [MD_ISODateTimeType]( typedef char MD_ISODateTimeType[21] ) | 闭市日期地址  (格式 yyyy-MM-dd hh:mm:ss) |
| 返回值    | void                                     |                                  |

### 1.6.17 通知实效性消息 

接口原型：

```c++
void OnRtnTimeless(MD_ReqID nReqID)
```

[^注]: 该信号只在请求实时行情时出现, 用于表示之后的数据为实时推送行情数据 

参数说明：

| 参数名称   | 数据类型                                | 说明     |
| ------ | ----------------------------------- | ------ |
| nReqID | [MD_ReqID]( typedef long MD_ReqID ) | 消息请求序号 |
| 返回值    | void                                |        |

# 2 数据字典 

| 序号   | 字典项                                      | 字典项名称            | 值    |
| ---- | ---------------------------------------- | :--------------- | ---- |
| 1    | PT_QuantMdAppEType                       | 行情环境类型           |      |
|      | PT_QuantMdAppEType_Test                  | 测试环境             | 0    |
|      | PT_QuantMdAppEType_Real                  | 生产环境             | 1    |
| 2    | PT_QuantTdAppEType                       | 交易环境 类型          |      |
|      | PT_QuantTdAppEType_Real                  | 生产环境             | 0    |
|      | PT_QuantTdAppEType_Test                  | 测试环境             | 1    |
|      | PT_QuantTdAppEType_Simulation            | 模拟环境             | 2    |
| 3    | PT_Quant_APPServerType                   | 业务服务器类型          |      |
|      | PT_Quant_APPServerType_RealMdServer      | 实时行情服务器          | 0    |
|      | PT_Quant_APPServerType_HisrotyMdServer   | 历史行情服务器          | 1    |
|      | PT_Quant_APPServerType_CacheMdServer     | 实时缓存服务器          | 2    |
|      | PT_Quant_APPServerType_TDServer          | 交易服务器            | 10   |
| 4    | PT_QuantUserType                         | 用户角色类型           |      |
|      | PT_QuantUserType_Risk                    | 风控员              | 1    |
|      | PT_QuantUserType_Trade                   | 交易员              | 2    |
| 5    | MD_SrvType                               | 服务器类型            |      |
|      | MD_SrvType_none                          | 未知类型             | 0    |
|      | MD_SrvType_history                       | 历史缓存行情服务器        | 1    |
|      | MD_SrvType_cache                         | 实时缓存行情服务器        | 2    |
|      | MD_SrvType_realtime                      | 实时推送行情服务器        | 4    |
| 6    | MD_CycType                               | 周期类型             |      |
|      | MD_CycType_none                          | 未知类型             | 0    |
|      | MD_CycType_second_10                     | 10秒              | 1    |
|      | MD_CycType_minute                        | 分                | 2    |
|      | MD_CycType_minute_5                      | 5分               | 4    |
|      | MD_CycType_minute_15                     | 15分              | 8    |
|      | MD_CycType_minute_30                     | 30分              | 16   |
|      | MD_CycType_hour                          | 小时               | 32   |
|      | MD_CycType_day                           | 日                | 64   |
| 7    | MD_SubType                               | 订阅类型             |      |
|      | MD_SubType_none                          | 未知类型             | 0    |
|      | MD_SubType_market                        | 个股行情             | 1    |
|      | MD_SubType_index                         | 指数行情             | 2    |
|      | MD_SubType_trans                         | 逐笔成交             | 4    |
|      | MD_SubType_order                         | 逐笔委托             | 8    |
|      | MD_SubType_order_queue                   | 委托队列             | 16   |
|      | MD_SubType_future                        | 期货行情             | 32   |
|      | MD_SubType_future_option                 | 期权行情             | 64   |
|      | MD_SubType_kline                         | K线行情             | 128  |
| 8    | TD_TradeType                             | 交易类型             |      |
|      | TD_TradeType_None                        | 未知类型             | 0    |
|      | TD_TradeType_Sell                        | 卖出               | 1    |
|      | TD_TradeType_Buy                         | 买入               | 2    |
| 9    | TD_OffsetType                            | 开平仓类型            |      |
|      | TD_OffsetType_None                       | 未知类型             | 0    |
|      | TD_OffsetType_Open                       | 开仓               | 1    |
|      | TD_OffsetType_Close                      | 平仓               | 2    |
| 10   | TD_OrderStatusType                       | 状态类型             |      |
|      | TD_OrderStatusType_fail                  | 指令失败             | -10  |
|      | TD_OrderStatusType_removed               | 撤单成功             | -9   |
|      | TD_OrderStatusType_allDealed             | 全部成交             | -8   |
|      | TD_OrderStatusType_unAccpet              | 未接受              | 0    |
|      | TD_OrderStatusType_accpeted              | 已接受未受理           | 1    |
|      | TD_OrderStatusType_queued                | 正在排队  (已受理状态)    | 2    |
|      | TD_OrderStatusType_toRemove              | 待报撤单             | 3    |
|      | TD_OrderStatusType_removing              | 已报待撤             | 4    |
|      | TD_OrderStatusType_partRemoved           | 部分撤单             | 5    |
|      | TD_OrderStatusType_partDealed            | 部分成交             | 6    |
| 11   | TQuantErrorType                          | 错误码              |      |
|      | EQuantErrorType_None                     | 执行正常, 没有错误       | 0    |
|      | EQuantErrorType_NotConnect               | 网络尚未连通           | 1    |
|      | EQuantErrorType_ParamInvalid             | 指定参数无效           | 2    |
|      | EQuantErrorType_LimitFunction            | 指定功能受限           | 3    |
|      | EQuantErrorType_HttpServerConnectError   | http服务器连接失败      | 4    |
|      | EQuantErrorType_HttpRequestError         | http请求失败         | 5    |
|      | EQuantErrorType_ParseError               | 通信包解析失败          | 6    |
|      | EQuantErrorType_SerializeError           | 通信包打包失败          | 7    |
|      | EQuantErrorType_NoTavailableFuction      | 暂不支持此函数          | 8    |
|      | EQuantErrorType_Logout                   | 未登录              | 9    |
|      | EQuantErrorType_AppServerDisconnect      | 业务服务器已断开         | 10   |
|      | EQuantErrorType_TooHighFrequency         | 指令太频繁            | 200  |
|      | EQuantErrorType_OrderNotFound            | 无此订单             | 201  |
|      | EQuantErrorType_NotTradingTime           | 非交易时间            | 202  |
|      | EQuantErrorType_OverHighOrLow            | 超过涨跌停价           | 203  |
|      | EQuantErrorType_InvalidVol               | 非法委托量            | 204  |
|      | EQuantErrorType_Cannotselfdeal           | 无法自成交            | 205  |
|      | EQuantErrorType_CannotWithDrawn          | 无法撤单(订单已经处于终结状态) | 206  |
|      | EQuantErrorType_NotEnoughLendingAmoutOrCaptial | 没有足够的券或钱         | 207  |
|      | EQuantErrorType_StopTrade                | 停机               | 208  |
|      | EQuantErrorType_NoSuchTradeType          | 无此交易类型           | 209  |
|      | EQuantErrorType_RiskCantTrade            | 风控无法开仓交易         | 210  |
|      | EQuantErrorType_StrategyRiskCantWithDrawn | 策略强平无法撤单         | 211  |
|      | EQuantErrorType_WithoutthisAuthority     | 无此权限             | 212  |
|      | EQuantErrorType_InvalidCode              | 非法证券代码           | 213  |
|      | EQuantErrorType_NoPisitionToClose        | 无仓可以平            | 214  |
|      | EQuantErrorType_MDNotConnect             | 尚未连接行情服务器        | 600  |
|      | EQuantErrorType_TDNotConnect             | 尚未连接交易服务器        | 601  |
|      | EQuantErrorType_MDNotAvaliable           | 无法正常使用行情         | 602  |
|      | EQuantErrorType_TDNotAvaliable           | 无法正常使用交易         | 603  |
|      |                                          |                  |      |
|      |                                          |                  |      |
|      |                                          |                  |      |
|      |                                          |                  |      |
|      |                                          |                  |      |
|      |                                          |                  |      |
|      |                                          |                  |      |
|      |                                          |                  |      |
|      |                                          |                  |      |



