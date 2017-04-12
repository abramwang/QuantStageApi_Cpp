#ifndef GETDATAAPI_H
#define GETDATAAPI_H

#ifdef WIN32
#ifndef API_EXPORT  
#define API_EXPORT _declspec(dllexport)  
#else  
#define API_EXPORT _declspec(dllimport)  
#endif
#endif

namespace PT_QuantPlatform{
	class TradeDataApi;
	class GetDataSpi{
	public:
		///代码表,登录成功后即会马上调用该回调
		virtual void OnRecvCode(TDF_CODE* pCode, int codeNum, TDF_OPTION_CODE* pOptionCode, int optionCodeNum){};
		///10档股票深度行情快照数据回调
		virtual void OnRecvMarket(TDF_MARKET_DATA* pMarket){};
		///5档期货行情快照数据回调
		virtual void OnRecvFuture(TDF_FUTURE_DATA* pFuture){};
		///5档期权行情快照数据回调
		virtual void OnRecvFutureOption(TDF_FUTURE_DATA* pFuture){};
		///指数行情快照数据回调
		virtual void OnRecvIndex(TDF_INDEX_DATA* pIndex){};
		///股票level2逐笔成交数据回调
		virtual void OnRecvTransaction(TDF_TRANSACTION* pTransaction){};
		///股票买一卖一委托队列数据回调
		virtual void OnRecvOrderQueue(TDF_ORDER_QUEUE* pOrderQueue){};
		///股票逐笔委托数据（仅深市有）回调
		virtual void OnRecvOrder(TDF_ORDER* pOrder){};
		///各周期K线数据统一回调（含股票、指数、期货、期权）
		virtual void OnRecvGDKLine(GD_Kline_Data* pKline){};									
	public:
		///模拟时间线确认回调
		virtual void OnRecvRspSimulationTimelineConfirmed(GD_SimulationTimelineConfirmed_Rsp* pConfirmed){};
		///当前数据交易日开始通知回调	
		virtual void OnRecvDayBegin(GD_ISODateTimeType pDate){};
		///当前数据交易日结束通知回调，在实时行情中即为闭市信号	
		virtual void OnRecvDayEnd(GD_ISODateTimeType pDate){};
		///历史数据发送结束每次历史数据请求结束都会调用这个接口
		virtual void OnRecvRspOver(){};												
	public:
		///交易日查询确认回调
		virtual void OnRspTradingDay(GD_ISODateTimeType* pDay, int dayNum){};			
		///服务器连接成功通知
		virtual void OnConnect(PT_ServerTypeCD serverType){};
		///服务器断线通知
		virtual void OnDisconnect(PT_ServerTypeCD serverType){};
		///服务器自动断线重连状态变化通知
		virtual void OnReconnectStatus(PT_ServerTypeCD serverType, const bool successed){};
	public:
		///数据时效性状态切换通知，通过这个
		virtual void OnRecvDataTimeless(GD_Stock_Timeliness_Notification* pData){};	
		///错误信息通知
		virtual void OnError(string error){};											
		GetDataSpi(){};
		~GetDataSpi(){};
	};
#ifdef WIN32
	class API_EXPORT GetDataApi{
#else
	class GetDataApi{
#endif
	public:
		/// 登录成功时会立收到即 OnRecvCode 回调
		/// @param [char*] user		用户名 
		/// @param [char*] pass		密码
		/// @see OnRecvCode
		bool Login(char* user, char* pass, int &err);
	public:
		/// 请求订阅实时行情推送，实盘中可以多次重复调用，多次调用之后继承最后一次调用时所采用的参数
		/// @param [std::vector<char*>] &subCodes			订阅行情代码表，支持一般格式 600000 或wind代码 600000.SH 
		/// @param [bool] isAllMarket						是否订阅全市场
		/// @param [int] beginTime							补齐从该时间点开始接受当日的数据，时间格式为hhmmsszzzz, 当0时从当前时刻开始接收，当为-1时从开盘开始接收
		/// @param [int] subDataType						订阅的数据类型，参见 GD_SubDataType， 例：	market_GD_SubDataType | transaction_GD_SubDataType 订阅快照和逐笔成交数据
		void ReqRealtimeData(std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int subDataType, int &err);
		/// 请求订阅实时k线推送，实盘中可以多次重复调用，多次调用之后继承最后一次调用时所采用的参数
		/// @param [int] &cycType							订阅k线周期类型，参见 GD_CycType, 可以用或运算同时订阅多种周期，例 minute_GD_CycType | minute_5_GD_CycType 为同时订阅分钟线和5分钟线
		/// @param [std::vector<char*>] &subCodes			订阅行情代码表，支持一般格式 600000 或wind代码 600000.SH 
		/// @param [bool] isAllMarket						是否订阅全市场
		/// @param [int] beginTime							补齐从该时间点开始接受当日的数据，时间格式为hhmmsszzzz, 当0时从当前时刻开始接收，当为-1时从开盘开始接收
		void ReqRealtimeGDKlineData(int cycType, std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int &err);				//请求实时k线 type 为k线周期类型，一次只能订阅一种周期，其他参数同上。数据回调为 OnRecvGDKLine
		/// 更新实时订阅代码表，可以增加、替换和删除订阅的代码
		/// 在调用了 ReqRealtimeData 和 ReqRealtimeGDKlineData 之后该接口才会生效， ReqRealtimeData 和 ReqRealtimeGDKlineData可以同时调用，并共享同一份代码吧 
		/// @param [GD_UpdateSubCodeType] &cycType			更新订阅代码表，可增加订阅、删除订阅、替换订阅三种更新模式
		/// @param [std::vector<char*>] &subCodes			订阅行情代码表，支持一般格式 600000 或wind代码 600000.SH 
		/// @param [bool] isAllMarket						是否订阅全市场
		void ReqUpdateSubStockCode(GD_UpdateSubCodeType reqType, std::vector<char*> &subCodes, bool isAllMarket, int &err);
	public:
		/// 请求模拟时间线。在非交易时间内，实时行情服务器会进行维护，所以提供了该接口进行替代模拟订阅实时行情的功能模式，在该模式下
		/// 可以选择任意回放速度进行历史中某天行情数据进行回放，并提供与实时行情一致的更新订阅的方法
		/// @param [GD_ISODateTimeType] beginTime			开始进行数据回放的时间点
		/// @param [GD_PlaybackSpeedType] speadTyp			行情回放速度, 参加 GD_PlaybackSpeedType
		void ReqSimulationTimeline(GD_ISODateTimeType beginTime, GD_PlaybackSpeedType speadTyp, int &err);

		/// 仅在 ReqSimulationTimeline 被调用之后有效
		/// @see ReqRealtimeData
		void ReqSimulationTickData(std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int subDataType, int &err);

		/// 仅在 ReqSimulationTimeline 被调用之后有效
		/// @see ReqRealtimeGDKlineData
		void ReqSimulationGDKlineData(int type, std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int &err);

		/// 仅在 ReqSimulationTimeline 被调用之后有效
		/// @see ReqUpdateSubStockCode
		void ReqSimulationUpdateSubStockCode(GD_UpdateSubCodeType reqType, std::vector<char*> &subCodes, bool isAllMarket, int &err);

		/// 请求历史行情数据
		/// @param [GD_ISODateTimeType] beginTime			开始进行数据回放的时间点
		/// @param [GD_ISODateTimeType] endTime				结束回放的时间点
		/// @param [GD_PlaybackSpeedType] speadTyp			行情回放速度, 参加 GD_PlaybackSpeedType
		/// @param [std::vector<char*>] &subCodes			订阅行情代码表，支持一般格式 600000 或wind代码 600000.SH 
		/// @param [bool] isAllMarket						是否订阅全市场
		int ReqHistoryData(GD_ISODateTimeType beginTime, GD_ISODateTimeType endTime, GD_PlaybackSpeedType speadTyp, std::vector<char*> &subCodes, bool isAllMarket, int &err);	//请求历史level2 tick行情 GD_SimuModelType为数据回放速度选择, fast为最快速，normal为与真实行情同样的速度
		
		/// 请求历史k线数据数据
		/// @param [int] &cycType							订阅k线周期类型，参见 GD_CycType, 可以用或运算同时订阅多种周期，例 minute_GD_CycType | minute_5_GD_CycType 为同时订阅分钟线和5分钟线
		/// @param [GD_ISODateTimeType] beginTime			开始进行数据回放的时间点
		/// @param [GD_ISODateTimeType] endTime				结束回放的时间点
		/// @param [GD_PlaybackSpeedType] speadTyp			行情回放速度, 参加 GD_PlaybackSpeedType
		/// @param [std::vector<char*>] &subCodes			订阅行情代码表，支持一般格式 600000 或wind代码 600000.SH 
		/// @param [bool] isAllMarket						是否订阅全市场
		int ReqHistoryGDKLineData(GD_CycType cycType, GD_ISODateTimeType beginTime, GD_ISODateTimeType endTime, std::vector<char*> &subCodes, bool isAllMarket, int &err);						//请求历史K线数据行情	。数据回调为 OnRecvGDKLine
		
		/// 请求历史交易日，给定一段时间，给出这段时间的所有交易日信息
		/// @param [GD_ISODateTimeType] beginDay			开始日期
		/// @param [GD_ISODateTimeType] endDay				结束日期
		/// @see OnRspTradingDay
		int ReqTradingDay(GD_ISODateTimeType beginDay, GD_ISODateTimeType endDay, int &err);		//查询的交易日列表
	public:
		//////////////////////////////////////////////////////////////////////////
		/// 通过行情数据计算k线, 这里提供了一种模式, 即在请求行情数据的同时，可以激活api内部的k线计算模块实时计算k线
		/// 改接口可以在登录成功之后任意位置调用，调用成功之后任何实时的、模拟时间线、历史的行情快照接口都会激活k线的计算
		/// 支持同时多个周期的计算
		void calculateKLineByTick(std::vector<GD_CycType> cycs);

		/// 同步查询股票基本信息
		/// @param [GD_CodeType] code						查询代码
		/// @param [GD_ListStatusType] listType				股票上市状态，在不明确的情况下填 ALL_GD_ListStatusType
		/// @param [GD_EquTypeCD] equType					股票类型，现仅支持A、B股的查询 
		std::vector<GD_StockBaseInfo> getStockBaseInfo(GD_CodeType code, GD_ListStatusType listType, GD_EquTypeCD equType, int &err);

		/// 同步查询某一段时间内某只股票的前复权因子
		/// @param [GD_CodeType] code						查询代码
		/// @param [GD_ISODateTimeType] beginDate			开始日期
		/// @param [GD_ISODateTimeType] endDate				结束日期
		std::vector<GD_RestorationFactor> getRestorationFactor(GD_CodeType code, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);

		/// 同步查询某一段时间内某只股票的后复权因子
		/// @param [GD_CodeType] code						查询代码
		/// @param [GD_ISODateTimeType] beginDate			开始日期
		/// @param [GD_ISODateTimeType] endDate				结束日期
		std::vector<GD_RestorationFactor> getAFRestorationFactor(GD_CodeType code, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);

		/// 同步查询某一段时间内某只股票的详细日k线，这个日k线的数据来源于通联数据，
		/// @param [GD_CodeType] code						查询代码
		/// @param [GD_ISODateTimeType] beginDate			开始日期
		/// @param [GD_ISODateTimeType] endDate				结束日期
		std::vector<GD_DetailMarketDayKline> getDetailMarketDayKline(GD_CodeType code, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);

		/// 同步查询某一段时间内某只股票因子数据
		/// @param [GD_CodeType] code						查询代码
		/// @param [vector<char*>] factorKeys				因子代码
		/// @param [GD_ISODateTimeType] beginDate			开始日期
		/// @param [GD_ISODateTimeType] endDate				结束日期
		std::vector<GD_StockFactors> getStockFactors(GD_CodeType code, vector<char*> &factorKeys, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);
	public:
		/// 构造行情数据连接API对象实例
		/// 在该模式下会在api内部创建两个回调线程，实时行情一个、历史行情一个，分别对应两个不同的行情服务器连接。所以在同时请求实时行情和历史行情时，在回调函数中需要主要资源竞争的问题
		/// @param [PT_QuantPlatform::GetDataSpi*] spi		用户创建的回调对象实例指针
		/// @param [autoRecon] autoRecon					是否启自动用断线重连
		/// @param [int] reconTimeOut						断线重连时间间隔，单位毫秒
		/// @param [bool] endDate							断线重连后是否接着发送请求，接着之前的数据继续发送
		static GetDataApi* CreateGetDataApi(PT_QuantPlatform::GetDataSpi* spi, bool autoRecon, int reconTimeOut, bool autoReq = false);

		/// 构造行情数据连接API对象实例，且启用模拟撮合的交易API
		/// 在该模式下，需要传入模拟撮合的交易api实例，这样在利用模拟撮合引擎的时候能够精确的定位下单的行情时刻以及当时真实的行情状态
		/// @param [PT_QuantPlatform::TradeDataApi*] tApi	用户创建的模拟交易连接对象实例指针
		/// @param [PT_QuantPlatform::GetDataSpi*] spi		用户创建的回调对象实例指针
		/// @param [autoRecon] autoRecon					是否启自动用断线重连
		/// @param [int] reconTimeOut						断线重连时间间隔，单位毫秒
		/// @param [int&] err								错误码
		/// @param [bool&] autoReq							断线重连成功后是否理解补发订阅请求
		/// @see TradeDataApi* TradeDataApi::CreateSimulationTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut);
		static GetDataApi* CreateGetDataApiEnableSimulationTrade(PT_QuantPlatform::TradeDataApi* tApi, PT_QuantPlatform::GetDataSpi* spi, bool autoRecon, int reconTimeOut, int &err, bool autoReq = false);
		
		/// 构造线程安全模式行情数据连接API对象实例，且启用模拟撮合的交易API
		/// 在该模式下所有数据回调只会Exec所在的线程，用户可以选择用自己启动一个线程进行数据回调。同时在该线程模式下，行情连接对象与交易连接对象有切仅能创建一个（含启用模拟交易）
		/// @param [PT_QuantPlatform::GetDataSpi*] spi		用户创建的回调对象实例指针
		/// @param [int&] err								错误码
		static GetDataApi* CreateThreadSafeGetDataApi(PT_QuantPlatform::GetDataSpi* spi, int& err);
		
		/// 构造线程安全模式行情数据连接API对象实例，且启用模拟撮合的交易API
		/// 在该模式下，需要传入模拟撮合的交易api实例，这样在利用模拟撮合引擎的时候能够精确的定位下单的行情时刻以及当时真实的行情状态
		/// @param [PT_QuantPlatform::TradeDataApi*] tApi	用户创建的线程安全模式模拟交易连接对象实例指针
		/// @param [PT_QuantPlatform::GetDataSpi*] spi		用户创建的回调对象实例指针
		/// @param [int&] err								错误码
		static GetDataApi* CreateThreadSafeGetDataApiEnableSimulationTrade(PT_QuantPlatform::TradeDataApi* tApi, PT_QuantPlatform::GetDataSpi* spi, int& err);

		/// 析构数据连接对象
		static void DelGetDataApi(PT_QuantPlatform::GetDataApi* pAPI);
	};
	
	extern "C"
	{
#ifdef WIN32
		/// 获取api版本号
		API_EXPORT const char* GetQuantPlatformApiVersion();
		/// 启用日志
		API_EXPORT void EnableLog();
		/// 线程安全模式下进入数据回调循环
		API_EXPORT int Exec();
		/// 线程安全模式下强制退出数据回调循环
		API_EXPORT void Terminate();
#else
		const char* GetQuantPlatformApiVersion();
		void EnableLog();
		int Exec();
		void Terminate();
#endif
	}
};
#endif // GETDATAAPI_H