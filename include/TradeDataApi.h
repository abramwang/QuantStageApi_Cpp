#ifndef TRADEDATAAPI_H
#define TRADEDATAAPI_H

#ifdef WIN32
#ifndef API_EXPORT  
	#define API_EXPORT _declspec(dllexport)
#endif
#endif

namespace PT_QuantPlatform{
	class TradeDataSpi
	{
	public: //系统回调
		virtual void OnRspUserTradeInfo(const TD_UserTradeInfoRsp *rsp) = 0;		//用户登录回调
		virtual void OnTDConnect(PT_ServerTypeCD serverType) = 0;									//连接成功
		virtual void OnTDDisConnect(PT_ServerTypeCD serverType) = 0;								//断开
		virtual void OnTDReconnectStatus(PT_ServerTypeCD serverType, const bool successed) = 0;		//断线重连尝试状态
	
	public: //业务逻辑回调

		virtual void OnRspOrderInsert(const TD_OrderInsert_Rsp *rsp, int error) = 0;				//插入订单回调
		virtual void OnRspOrderModify(const TD_OrderModify_Rsp *rsp, int error) = 0;				//修改订单回调
		virtual void OnRspOrderDelete(const TD_OrderDelete_Rsp *rsp, int error) = 0;				//删除订单回调

		virtual void OnRspQryOrder(const TD_QryOrder_Rsp *rsp, int error, bool isEnd) = 0;					//查询订单回调
		virtual void OnRspQryMatch(const TD_QryMatch_Rsp *rsp, int error, bool isEnd) = 0;					//查询成交回调
		virtual void OnRspQryPosition(const TD_QryPosition_Rsp *rsp, int error, bool isEnd) = 0;			//查询持仓回调

		virtual void OnRspQryCapitalAccount(const TD_QryCapital_Rsp* rsp, int error, bool isEnd) = 0;                           // 查询资金帐号回调
		virtual void OnRspQrySecuDebt(const TD_QrySecuDebt_Rsp* rsp, int error, bool isEnd) = 0;                                // 查询融券负债回调
		virtual void OnRspQryMaxEntrustCount(const TD_QryMaxEntrustCount_Rsp* rsp, int error) = 0;								// 查询最大可委托量回调
		virtual void OnRspQrySecuritiesLendingAmount(const TD_QrySecuritiesLendingAmount_Rsp* rsp, int error, bool isEnd) = 0;	// 查询可融券列表回调

		virtual void OnRtnOrderStatusChangeNotice(const TD_OrderStatusChangeNotice *notice) = 0;    	//订单状态变化通知
		virtual void OnRtnOrderMatchNotice(const TD_OrderMatchNotice *notice) = 0;						//成交状态更新通知

	public:
		TradeDataSpi(){};
		~TradeDataSpi(){};
	};
#ifdef WIN32
	class API_EXPORT TradeDataApi{
#else
	class TradeDataApi{
#endif
	public:
		bool Login(char* user, char* pass, int &err);
		void SetNewBackTest(double stampTax, double transferFees, double commissions, char* szComment, int &err);

		virtual int OrderInsert(TD_OrderInsert_Req* req);				//插入订单
		virtual int OrderModify(TD_OrderModify_Req* req);				//修改订单
		virtual int OrderDelete(TD_OrderDelete_Req* req);				//删除订单

		virtual void QryOrder(TD_QryOrder_Req* req);											//查询当日所有订单
		virtual void QryMatch(TD_QryMatch_Req* req);											//查询所有成交
		virtual void QryPosition(TD_QryPosition_Req* req);										//查询头寸

		virtual void QryCapitalAccount(TD_QryCapital_Req* req);									// 查询资金帐号
		virtual void QrySecuDebt(TD_QrySecuDebt_Req* req);										// 查询融券负债
		virtual void QryMaxEntrustCount(TD_QryMaxEntrustCount_Req* req);						// 查询最大可委托量
		virtual void QrySecuritiesLendingAmount(TD_QrySecuritiesLendingAmount_Req* req);		// 查询可融券列表
	};
};

extern "C"
{
#ifdef WIN32
	API_EXPORT PT_QuantPlatform::TradeDataApi* CreateTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool enableLog = true);
	API_EXPORT PT_QuantPlatform::TradeDataApi* CreateSimulationTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool enableLog = true);
	API_EXPORT void DelTradeDataApi(PT_QuantPlatform::TradeDataApi* pAPI);
#else
	PT_QuantPlatform::TradeDataApi* CreateTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool enableLog = true);
	PT_QuantPlatform::TradeDataApi* CreateSimulationTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool enableLog = true);
	void DelTradeDataApi(PT_QuantPlatform::TradeDataApi* pAPI);
#endif
}

#endif // TRADEDATAAPI_H