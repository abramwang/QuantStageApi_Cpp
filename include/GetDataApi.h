#ifndef GETDATAAPI_H
#define GETDATAAPI_H

#ifndef API_EXPORT  
#ifdef WIN32
#define API_EXPORT _declspec(dllexport)
#else
#define API_EXPORT
#endif
#endif

namespace PT_QuantPlatform{
	class TradeDataApi;
	class GetDataSpi{
	public:
		virtual void OnRecvCode(TDF_CODE* pCode, int codeNum, TDF_OPTION_CODE* pOptionCode, int optionCodeNum){};		//代码表,登录成功后即会马上调用该回调
		//实时数据
		virtual void OnRecvMarket(TDF_MARKET_DATA* pMarket){};									//行情
		virtual void OnRecvFuture(TDF_FUTURE_DATA* pFuture){};									//期货
		virtual void OnRecvFutureOption(TDF_FUTURE_DATA* pFuture){};							//期权
		virtual void OnRecvIndex(TDF_INDEX_DATA* pIndex){};										//指数
		virtual void OnRecvTransaction(TDF_TRANSACTION* pTransaction){};						//逐笔
		virtual void OnRecvOrderQueue(TDF_ORDER_QUEUE* pOrderQueue){};							//委托队列
		virtual void OnRecvOrder(TDF_ORDER* pOrder){};											//逐笔委托数据（仅深市有）
		virtual void OnRecvGDKLine(GD_Kline_Data* pKline){};									//K线数据

		//每次数据日期变更都会通知这两个接口，无论是历史还是实时
		virtual void OnRecvRspSimulationTimelineConfirmed(GD_SimulationTimelineConfirmed_Rsp* pConfirmed){}; //模拟时间线确认回调
		virtual void OnRecvDayBegin(GD_ISODateTimeType pDate){};						//接收当前交易日		
		virtual void OnRecvDayEnd(GD_ISODateTimeType pDate){};							//接收到闭市消息
		virtual void OnRecvRspOver(){};													//每次历史数据请求结束都会调用这个接口

		//指标数据
		virtual void OnRspTradingDay(GD_ISODateTimeType* pDay, int dayNum){};
		//系统信息
		virtual void OnConnect(PT_ServerTypeCD serverType){};
		virtual void OnDisconnect(PT_ServerTypeCD serverType){};
		virtual void OnReconnectStatus(PT_ServerTypeCD serverType, const bool successed){};

		virtual void OnRecvDataTimeless(GD_Stock_Timeliness_Notification* pData){};		//数据时效性状态切换通知，通过这个
		virtual void OnError(string error){};	//错误信息
		GetDataSpi(){};
		~GetDataSpi(){};
	};

	class API_EXPORT GetDataApi{
	public:
		bool Login(char* user, char* pass, int &err);
		//请求实时行情
		//tick数据和k线可以同时请求，ReqUpdateSubStockCode可以同时修改k线和tick的订阅代码
		void ReqRealtimeData(std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int subDataType, int &err);				//请求实时tick, isAllMarket = true 订阅所有代码, isFromOpening = true 补全开盘至当前时刻的数据，subDataType 为枚举值选择订阅所包含的数据类型
		void ReqRealtimeGDKlineData(int type, std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int &err);				//请求实时k线 type 为k线周期类型，一次只能订阅一种周期，其他参数同上。数据回调为 OnRecvGDKLine
		void ReqUpdateSubStockCode(GD_UpdateSubCodeType reqType, std::vector<char*> &subCodes, bool isAllMarket, int &err);			//更新订阅代码，可以增加、替换和删除订阅的代码 
		//请求模拟行情时间线
		void ReqSimulationTimeline(GD_ISODateTimeType beginTime, GD_PlaybackSpeedType speadTyp, int &err);
		void ReqSimulationTickData(std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int subDataType, int &err);
		void ReqSimulationGDKlineData(int type, std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int &err);
		void ReqSimulationUpdateSubStockCode(GD_UpdateSubCodeType reqType, std::vector<char*> &subCodes, bool isAllMarket, int &err);
		//请求历史行情
		//请求历史Level2 tick数据
		void ReqHistoryData(GD_ISODateTimeType beginTime, GD_ISODateTimeType endTime, GD_PlaybackSpeedType modelType, std::vector<char*> &subCodes, bool isAllMarket, int &err);	//请求历史level2 tick行情 GD_SimuModelType为数据回放速度选择, fast为最快速，normal为与真实行情同样的速度
		void ReqHistoryGDKLineData(GD_CycType type, GD_ISODateTimeType beginTime, GD_ISODateTimeType endTime, std::vector<char*> &subCodes, bool isAllMarket, int &err);						//请求历史K线数据行情	。数据回调为 OnRecvGDKLine
		void ReqTradingDay(GD_ISODateTimeType beginDay, GD_ISODateTimeType endDay, int &err);		//查询的交易日列表
		//指标接口
		void calculateKLineByTick(std::vector<GD_CycType> cycs);
		std::vector<GD_StockBaseInfo> getStockBaseInfo(GD_CodeType code, GD_ListStatusType listType, GD_EquTypeCD equType, int &err);
		std::vector<GD_RestorationFactor> getRestorationFactor(GD_CodeType code, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);			//前复权因子
		std::vector<GD_RestorationFactor> getAFRestorationFactor(GD_CodeType code, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);			//后复权因子
		std::vector<GD_DetailMarketDayKline> getDetailMarketDayKline(GD_CodeType code, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);
		std::vector<GD_StockFactors> getStockFactors(GD_CodeType code, vector<char*> &factorKeys, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);
	};

	extern "C"
	{
		API_EXPORT const char* GetQuantPlatformApiVersion();
		API_EXPORT void Init(GD_API_InitSetting &initSetting);

		API_EXPORT PT_QuantPlatform::GetDataApi* CreateGetDataApi(PT_QuantPlatform::GetDataSpi* spi);
		API_EXPORT PT_QuantPlatform::GetDataApi* CreateGetDataApiEnableSimulationTrade(PT_QuantPlatform::TradeDataApi* tApi, PT_QuantPlatform::GetDataSpi* spi, int &err);
		API_EXPORT void DelGetDataApi(PT_QuantPlatform::GetDataApi* pAPI);
	}
};
#endif // GETDATAAPI_H