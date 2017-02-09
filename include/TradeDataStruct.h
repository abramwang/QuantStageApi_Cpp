#ifndef TRADEDATASTRUCT_H
#define TRADEDATASTRUCT_H

//#include "GetDataStruct.h"
/* 按一个字节补齐*/
#pragma pack(push)
#pragma pack(1)

#ifndef GETDATASTRUCT_H
typedef char GD_CodeType[32];
typedef char GD_CodeName[32];
typedef char GD_ISODateTimeType[21];	//日期和时间类型(格式 yyyy-MM-dd hh:mm:ss)
#endif

typedef char TD_OrderIdType[32];
typedef char TD_AccountType[32];
typedef char TD_Text[128];

enum TD_BrokerType			//券商类型
{
	TD_BrokerType_None,
	TD_BrokerType_dongwu,
	TD_BrokerType_guangda,
	TD_BrokerType_guotai,
	TD_BrokerType_guoxin,
	TD_BrokerType_haitong,
	TD_BrokerType_shenwan,
	TD_BrokerType_yinhe,
	TD_BrokerType_zhaoshang,
	TD_BrokerType_fangzheng,
	TD_BrokerType_AC,
	TD_BrokerType_zhongxin,
	TD_BrokerType_anxin,
	TD_BrokerType_dongbei,
	TD_BrokerType_huataiwang,
	TD_BrokerType_hengtai,
	TD_BrokerType_zhongjing,
	TD_BrokerType_guangfa,
	TD_BrokerType_huabao,
	TD_BrokerType_xuntou,
	TD_BrokerType_xibu,
	TD_BrokerType_IMSWT,
	TD_BrokerType_huatai
};

enum TD_OrderType
{
	TD_OrderType_Limit,		//限价单
	TD_OrderType_Market		//市价单
};

enum TD_TradeType
{
	// 卖方向
	TD_TradeType_Sell					= -200,		//普通卖出
	TD_TradeType_SellBySecuLending,					//融券卖出
	TD_TradeType_SellSecurityRtnCash,				//卖券还款

	TD_TradeType_None					= 0,
	TD_TradeType_RtnSecurity			= 1,		//直接还券
	TD_TradeType_RtnCash,							//直接还款

	// 买方向
	TD_TradeType_Buy					= 100,		//普通买入
	TD_TradeType_BuyOnMargin,						//融资买入
	TD_TradeType_BuySecurityRtnSecu,				//买券还券
};

enum TD_OffsetType
{
	TD_OffsetType_None,
	TD_OffsetType_Open,					//开仓
	TD_OffsetType_Close,				//平仓
};

enum TD_OrderStatusType
{
	TD_OrderStatusType_fail			= -10,	//指令失败
	TD_OrderStatusType_partRemoved,			//部分撤单
	TD_OrderStatusType_removed,				//撤单成功
	TD_OrderStatusType_allDealed,			//全部成交

	TD_OrderStatusType_unAccpet		= 0,	//未接受
	TD_OrderStatusType_accpeted,			//已接受未受理
	TD_OrderStatusType_queued,				//正在排队	(已受理状态)
	TD_OrderStatusType_toModify,			//待报改单
	TD_OrderStatusType_modifing,			//已报改单
	TD_OrderStatusType_modified,			//改单受理
	TD_OrderStatusType_toRemove,			//待报撤单
	TD_OrderStatusType_removing,			//已报待撤
	TD_OrderStatusType_partDealed,			//部分成交
};

/// 交易市场
enum TD_MarketType
{
	TD_MarketType_NULL,		//未指定
	TD_MarketType_SZ_A,		//深圳A
	TD_MarketType_SZ_B,		//深圳B
	TD_MarketType_SH_A,		//上海A
	TD_MarketType_SH_B,		//上海B
	TD_MarketType_XSB		//新三板
};

//服务器连接类型代码
typedef char PT_ServerTypeCD;
const PT_ServerTypeCD		Production_PT_ServerTypeCD = 20;		//生产环境交易服务器
const PT_ServerTypeCD		Test_PT_ServerTypeCD = 22;				//测试环境交易服务器

// 请求
struct TD_Base_Msg
{
	int		nReqId;						//请求ID（有客户端API维护的唯一ID）

	int		nUserInt;					//用户保留字段
	double	nUserDouble;
	TD_Text szUseStr;

	int		nUserId;					//客户端编号
	int		nAccountId;					//券商资金账户Id

	TD_Base_Msg()
	{
		nReqId = 0;

		nUserInt = 0;
		nUserDouble = 0;
		memset(szUseStr, 0, sizeof(TD_Text));

		nUserId = 0;
		nAccountId = 0;
	}
	virtual ~TD_Base_Msg()
	{

	}
};

// 下单
struct TD_OrderInsert_Req : TD_Base_Msg
{
	__int64         nOrderId;							//服务器维护（服务唯一）
	TD_OrderIdType	szOrderStreamId;		//委托编号（broker 或交易所的唯一编号）

	GD_CodeType		szContractCode;			//证券合约代码
	GD_CodeName		szContractName;			//证券合约名称
	TD_OrderType	nOrderType;				//市价限价单
	TD_TradeType	nTradeType;				//交易类型 买、卖、融券等
	TD_OffsetType	nOffsetType;			//开平仓类型

	double			nOrderPrice;			//申报价
	int				nOrderVol;				//申报量

	GD_ISODateTimeType szInsertTime;		//接收委托时间

	TD_OrderInsert_Req()
	{
		nOrderId = 0;
		memset(szOrderStreamId, 0, sizeof(TD_OrderIdType));

		memset(szContractCode, 0, sizeof(GD_CodeType));
		memset(szContractName, 0, sizeof(GD_CodeName));
		nTradeType = TD_TradeType_None;
		nOrderType = TD_OrderType_Limit;
		nOffsetType = TD_OffsetType_None;

		nOrderPrice = 0;
		nOrderVol= 0;

		memset(szInsertTime, 0, sizeof(GD_ISODateTimeType));
	}
	virtual ~TD_OrderInsert_Req()
	{

	}
};

//修改订单请求
struct TD_OrderModify_Req : TD_Base_Msg		
{
	__int64			nOrderId;				//订单Id
	double			nPrice;					//修改申报价
	int				nVol;					//修改申报量

	TD_OrderModify_Req()
	{
		nOrderId = 0;
		nPrice = 0;
		nVol = 0;
	}
	virtual ~TD_OrderModify_Req()
	{

	}
};

// 撤单
struct TD_OrderDelete_Req : TD_Base_Msg
{
	__int64 nOrderId;
	TD_OrderDelete_Req()
	{
		nOrderId = 0;
	}
	virtual ~TD_OrderDelete_Req()
	{

	}
};

//委托查询请求
struct TD_QryOrder_Req : TD_Base_Msg
{
	__int64					nOrderId;				//委托编号
	GD_CodeType			szContractCode;			//证券合约代码
	TD_QryOrder_Req()
	{
		nOrderId = 0;

		memset(szContractCode, 0, sizeof(GD_CodeType));
	}
	virtual ~TD_QryOrder_Req()
	{

	}
};

//成交查询请求
struct TD_QryMatch_Req : TD_Base_Msg
{
	GD_CodeType		szContractCode;			    //证券合约代码
	TD_QryMatch_Req()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
	}
	virtual ~TD_QryMatch_Req()
	{

	}
};

//持仓查询请求
struct TD_QryPosition_Req : TD_Base_Msg
{
	GD_CodeType		szContractCode;			    //证券合约代码
	TD_QryPosition_Req()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
	}
	virtual ~TD_QryPosition_Req()
	{

	}
};

//最大可委托量查询请求
struct TD_QryMaxEntrustCount_Req : TD_Base_Msg
{
	GD_CodeType szContractCode;       // 股票代码
	double      nPrice;		          // 价格
	TD_TradeType nTraderType;         // 交易行为
	TD_QryMaxEntrustCount_Req()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
		nPrice = 0;
		nTraderType = TD_TradeType_None;
	}
	virtual ~TD_QryMaxEntrustCount_Req()
	{

	}
};

//可融券查询请求
struct TD_QrySecuritiesLendingAmount_Req : TD_Base_Msg  
{
	GD_CodeType szContractCode;       // 股票代码
	TD_QrySecuritiesLendingAmount_Req()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
	}
	virtual ~TD_QrySecuritiesLendingAmount_Req()
	{

	}
};

typedef TD_Base_Msg TD_QryCapital_Req;				//资金查询请求
typedef TD_Base_Msg TD_QrySecuDebt_Req;				//融券负债查询请求
typedef TD_Base_Msg TD_Base_Req;						//基本无参数请求

//订单状态变化通知
struct TD_OrderStatusChangeNotice : TD_OrderInsert_Req
{
	TD_OrderStatusType	nStatus;				//状态
	double				nDealedPrice;			//成交均价
	int					nDealedVol;				//成交总量

	TD_Text             szText;

	TD_OrderStatusChangeNotice()
	{
		nStatus = TD_OrderStatusType_unAccpet;
		nDealedPrice = 0;
		nDealedVol = 0;

		memset(szText, 0, sizeof(szText));
	}
	virtual ~TD_OrderStatusChangeNotice()
	{

	}
};

//成交回调通知
struct TD_OrderMatchNotice : TD_Base_Msg
{
	__int64     		nOrderId;				//对于委托编号
	__int64  			nMatchStreamId;			//成交系统编号
	double				nMatchPrice;			//成交价
	int					nMatchVol;				//成交量

	GD_CodeType szContractCode;				    // 股票代码
	GD_ISODateTimeType  szMatchTime;			//成交时间

	TD_OrderMatchNotice()
	{
		nOrderId = 0;
		nMatchStreamId = 0;
		nMatchPrice = 0;
		nMatchVol = 0;

		memset(szContractCode, 0, sizeof(GD_CodeType));
		memset(szMatchTime, 0, sizeof(GD_ISODateTimeType));
	}
	virtual ~TD_OrderMatchNotice()
	{

	}
};

typedef TD_OrderStatusChangeNotice TD_OrderInsert_Rsp;	//插入订单响应	
typedef TD_OrderDelete_Req		 TD_OrderDelete_Rsp;	//撤销订单响应
typedef TD_OrderModify_Req		 TD_OrderModify_Rsp;	//修改订单响应

//订单查询响应
typedef TD_OrderStatusChangeNotice TD_QryOrder_Rsp;
//成交查询响应
typedef TD_OrderMatchNotice TD_QryMatch_Rsp;

//持仓查询回调
struct TD_QryPosition_Rsp : TD_Base_Msg
{
	GD_CodeType		szContractCode;			//证券合约代码

	int     nPosition;                       //  持仓总量
	double      nPrice;                      //  持仓均价

	double  nProfit;                         //  浮盈
	TD_QryPosition_Rsp()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
		nPosition = 0;
		nPrice = 0;
		nProfit = 0;
	}
	virtual ~TD_QryPosition_Rsp()
	{

	}
};

//  查询资金帐号回调
struct TD_QryCapital_Rsp : TD_Base_Msg
{
	double m_fundbal;                     //  资金负债总额
	double m_fundavl;	                  //  资金可用金额  
	TD_QryCapital_Rsp()
	{
		m_fundbal = 0;
		m_fundavl = 0;
	}
	virtual ~TD_QryCapital_Rsp()
	{

	}
};

//  查询融券负债回调
struct TD_QrySecuDebt_Rsp : TD_Base_Msg
{
	GD_CodeType szContractCode;       // 股票代码
	int  m_dstkbal;                   // 负债总股数 
	TD_QrySecuDebt_Rsp()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
		m_dstkbal = 0;
	}
	virtual ~TD_QrySecuDebt_Rsp()
	{

	}
};

//  查询最大可委托数量回调
struct TD_QryMaxEntrustCount_Rsp : TD_Base_Msg
{
	int m_maxStkqty;                    //  最大可委托数量
	TD_QryMaxEntrustCount_Rsp()
	{
		m_maxStkqty = 0;
	}
	virtual ~TD_QryMaxEntrustCount_Rsp()
	{

	}
};

//  查询可融券列表回调
struct TD_QrySecuritiesLendingAmount_Rsp : TD_Base_Msg
{
	GD_CodeType szContractCode;       // 股票代码
	int   m_sepremQty;                // 余券
	TD_QrySecuritiesLendingAmount_Rsp()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
		m_sepremQty = 0;
	}
	virtual ~TD_QrySecuritiesLendingAmount_Rsp()
	{

	}
};

//////////////////////////////////////////////////////////////////////////
// 系统方面

enum TD_AccountAttr
{
	TD_AccountAttr_noTrading = 0,			//非交易实盘账户
	TD_AccountAttr_productionTrading = 1,	//实盘交易账户
	TD_AccountAttr_simulationTrading = 2,	//模拟交易账户
	TD_AccountAttr_testTrading = 3			//测试交易账户
};

struct TD_AccountInfo
{
	int nAccountId;					//Id
	char szAccountName[32];			//账户别名
	char szAccountNo[32];			//账户登录名
	TD_AccountAttr nAccountAttr;	//账户属性  //实盘账户、模拟账户、测试账户

	double nStampTax;			//印花税
	double nTransferFees;		//过户费
	double nCommissions;		//佣金
};

struct TD_UserTradeInfoRsp
{
	int nUserId;
	char szUserName[32];					//登录名
	char szUserNickName[32];				//用户昵称
	char szSecurityCode[32];				//安全码
	
	TD_AccountInfo* m_account;				//实盘交易账户列表首地址
	int nAccountCount;							//实盘交易账户列表
}; 


#pragma pack(pop)
#endif //TRADEDATASTRUCT_H