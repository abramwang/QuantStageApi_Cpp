#ifndef GETDATASTRUCT_H
#define GETDATASTRUCT_H

#pragma pack(push)
#pragma pack(1)

//////////////////////////////////////////////////////////////////////////
//TDF 结构体
//////////////////////////////////////////////////////////////////////////
#ifndef __TDF_API_STRUCT_H__
#define __TDF_API_STRUCT_H__
struct TDF_MARKET_CLOSE
{
	char    szMarket[8];        //交易所名称
	int		nTime;				//时间(HHMMSSmmm)
	char	chInfo[64];			//闭市信息
};

struct TDF_CODE
{
	char szWindCode[32];		//Wind Code: AG1302.SHF
	char szMarket[8];			//market code: SHF
	char szCode[32];			//original code:ag1302
	char szENName[32];
	char szCNName[32];			//chinese name: 沪银1302
	int nType;
};

struct TDF_OPTION_CODE
{
	TDF_CODE basicCode;

	char szContractID[32];			// 期权合约代码
	char szUnderlyingSecurityID[32];//// 标的证券代码
	char chCallOrPut;               // 认购认沽C1        认购，则本字段为“C”；若为认沽，则本字段为“P”
	int  nExerciseDate;             // 期权行权日，YYYYMMDD

	//扩充字段
	char chUnderlyingType;			// 标的证券类型C3    0-A股 1-ETF (EBS – ETF， ASH – A 股)
	char chOptionType;              // 欧式美式C1        若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”

	char chPriceLimitType;          // 涨跌幅限制类型C1 ‘N’表示有涨跌幅限制类型, ‘R’表示无涨跌幅限制类型
	int  nContractMultiplierUnit;	// 合约单位,         经过除权除息调整后的合约单位, 一定是整数
	int  nExercisePrice;            // 期权行权价,       经过除权除息调整后的期权行权价，右对齐，精确到厘
	int  nStartDate;                // 期权首个交易日,YYYYMMDD
	int  nEndDate;                  // 期权最后交易日/行权日，YYYYMMDD
	int  nExpireDate;               // 期权到期日，YYYYMMDD
};

//数据消息：MSG_DATA_MARKET 对应的结构
struct TDF_MARKET_DATA
{
	char        szWindCode[32];         //600001.SH 
	char        szCode[32];             //原始Code
	int         nActionDay;             //业务发生日(自然日)
	int         nTradingDay;            //交易日
	int			 nTime;					//时间(HHMMSSmmm)
	int			 nStatus;				//状态
	unsigned int nPreClose;				//前收盘价
	unsigned int nOpen;					//开盘价
	unsigned int nHigh;					//最高价
	unsigned int nLow;					//最低价
	unsigned int nMatch;				//最新价
	unsigned int nAskPrice[10];			//申卖价
	unsigned int nAskVol[10];			//申卖量
	unsigned int nBidPrice[10];			//申买价
	unsigned int nBidVol[10];			//申买量
	unsigned int nNumTrades;			//成交笔数
	__int64		 iVolume;				//成交总量
	__int64		 iTurnover;				//成交总金额
	__int64		 nTotalBidVol;			//委托买入总量
	__int64		 nTotalAskVol;			//委托卖出总量
	unsigned int nWeightedAvgBidPrice;	//加权平均委买价格
	unsigned int nWeightedAvgAskPrice;  //加权平均委卖价格
	int			 nIOPV;					//IOPV净值估值
	int			 nYieldToMaturity;		//到期收益率
	unsigned int nHighLimited;			//涨停价
	unsigned int nLowLimited;			//跌停价
	char		 chPrefix[4];			//证券信息前缀
	int			 nSyl1;					//市盈率1
	int			 nSyl2;					//市盈率2
	int			 nSD2;					//升跌2（对比上一笔）
};

//数据消息：MSG_DATA_INDEX 对应的结构
struct TDF_INDEX_DATA
{
	char        szWindCode[32];         //600001.SH 
	char        szCode[32];             //原始Code
	int         nActionDay;             //业务发生日(自然日)
	int         nTradingDay;            //交易日
	int         nTime;			//时间(HHMMSSmmm)
	int		    nOpenIndex;		//今开盘指数
	int 	    nHighIndex;		//最高指数
	int 	    nLowIndex;		//最低指数
	int 	    nLastIndex;		//最新指数
	__int64	    iTotalVolume;	//参与计算相应指数的交易数量
	__int64	    iTurnover;		//参与计算相应指数的成交金额
	int		    nPreCloseIndex;	//前盘指数
};

//数据消息：MSG_DATA_FUTURE 对应的结构
struct TDF_FUTURE_DATA
{
	char        szWindCode[32];         //600001.SH 
	char        szCode[32];             //原始Code
	int         nActionDay;             //业务发生日(自然日)
	int         nTradingDay;            //交易日
	int			 nTime;					//时间(HHMMSSmmm)	
	int			 nStatus;				//状态
	__int64		 iPreOpenInterest;		//昨持仓
	unsigned int nPreClose;				//昨收盘价
	unsigned int nPreSettlePrice;		//昨结算
	unsigned int nOpen;					//开盘价	
	unsigned int nHigh;					//最高价
	unsigned int nLow;					//最低价
	unsigned int nMatch;				//最新价
	__int64		 iVolume;				//成交总量
	__int64		 iTurnover;				//成交总金额
	__int64		 iOpenInterest;			//持仓总量
	unsigned int nClose;				//今收盘
	unsigned int nSettlePrice;			//今结算
	unsigned int nHighLimited;			//涨停价
	unsigned int nLowLimited;			//跌停价
	int			 nPreDelta;			    //昨虚实度
	int			 nCurrDelta;            //今虚实度
	unsigned int nAskPrice[5];			//申卖价
	unsigned int nAskVol[5];			//申卖量
	unsigned int nBidPrice[5];			//申买价
	unsigned int nBidVol[5];			//申买量

	//Add 20140605
	int	lAuctionPrice;		//波动性中断参考价
	int	lAuctionQty;		//波动性中断集合竞价虚拟匹配量
};

//数据消息：MSG_DATA_ORDERQUEUE 对应的结构
struct TDF_ORDER_QUEUE
{
	char    szWindCode[32]; //600001.SH 
	char    szCode[32];     //原始Code
	int     nActionDay;     //自然日
	int 	nTime;			//时间(HHMMSSmmm)
	int     nSide;			//买卖方向('B':Bid 'A':Ask)
	int		nPrice;			//委托价格
	int 	nOrders;		//订单数量
	int 	nABItems;		//明细个数
	int 	nABVolume[200];	//订单明细
};

//数据消息：MSG_DATA_TRANSACTION 对应的结构
struct TDF_TRANSACTION
{
	char    szWindCode[32]; //600001.SH 
	char    szCode[32];     //原始Code
	int     nActionDay;     //自然日
	int 	nTime;		    //成交时间(HHMMSSmmm)
	int 	nIndex;		    //成交编号
	int		nPrice;		    //成交价格
	int 	nVolume;	    //成交数量
	int		nTurnover;	    //成交金额
	int     nBSFlag;        //买卖方向(买：'B', 卖：'A', 不明：' ')
	char    chOrderKind;    //成交类别
	char    chFunctionCode; //成交代码
	int	    nAskOrder;	    //叫卖方委托序号
	int	    nBidOrder;	    //叫买方委托序号
};

//数据消息：MSG_DATA_ORDER 对应的结构
struct TDF_ORDER
{
	char    szWindCode[32]; //600001.SH 
	char    szCode[32];     //原始Code
	int 	nActionDay;	    //委托日期(YYMMDD)
	int 	nTime;			//委托时间(HHMMSSmmm)
	int 	nOrder;	        //委托号
	int		nPrice;			//委托价格
	int 	nVolume;		//委托数量
	char    chOrderKind;	//委托类别
	char    chFunctionCode;	//委托代码('B','S','C')
};
#endif // __TDF_API_STRUCT_H__

typedef char GD_CodeType[32];
typedef char GD_CodeName[32];
typedef char GD_ISODateTimeType[21];	//日期和时间类型(格式 yyyy-MM-dd hh:mm:ss)
typedef char GD_ShortText[128];
typedef char GD_Text[1024];

enum GD_TimelinessType				//数据效性
{
	historyData_GD_TimelinessType,		//历史数据
	realtimeData_GD_TimelinessType		//实时数据
};

enum GD_StockType{
	stock_GD_StockType = 0,			//股票
	index_GD_StockType,				//指数
	future_GD_StockType,			//期货
	option_GD_StockType,			//期权

	none_GD_StockType = -1
};

enum GD_CycType				//
{
	none_GD_CycType			= 0x0000,		//空
	second_10_GD_CycType	= 0x0001,		//10秒
	minute_GD_CycType		= 0x0002,		//分
	minute_5_GD_CycType		= 0x0004,		//5分
	minute_15_GD_CycType	= 0x0008,		//15分
	minute_30_GD_CycType	= 0x0010,		//30分
	hour_GD_CycType			= 0x0020,		//小时
	day_GD_CycType			= 0x0040,		//日
};

enum GD_UpdateSubCodeType
{
	add_GD_UpdateSubCodeType = 0,		//添加订阅代码
	remove_GD_UpdateSubCodeType,		//移除已有订阅代码
	replace_GD_UpdateSubCodeType		//替换全部订阅代码
};

enum GD_ServerType		//服务器所属类型
{
	realTime_GD_ServerType = 0,			//实时行情服务器
	simulation_GD_ServerType,			//模拟行情服务器
	history_GD_ServerType				//历史数据服务器
};

enum GD_PlaybackSpeedType	//请求历史数据模拟回测类型
{
	fast_GD_PlaybackSpeedType,				//快速模式
	normal_GD_PlaybackSpeedType,			//正常模式
	x2Spped_GD_PlaybackSpeedType,			//2倍速模式
	x3Spped_GD_PlaybackSpeedType,			//3倍速模式
	x5Spped_GD_PlaybackSpeedType,			//5倍速模式
	x10Spped_GD_PlaybackSpeedType			//10倍速模式
};

enum GD_SubDataType		//订阅数据类型
{
	all_GD_SubDataType			= 0x0000,	//所有数据类型
	market_GD_SubDataType		= 0x0001,	//行情数据
	transaction_GD_SubDataType	= 0x0002,	//逐笔成交数据
	orderQueue_GD_SubDataType	= 0x0004,	//委托队列数据
	order_GD_SubDataType		= 0x0008,	//逐笔委托数据
};

enum GD_ListStatusType	//上市状态
{
	ALL_GD_ListStatusType,	//所有
	L_GD_ListStatusType,	//上市
	S_GD_ListStatusType,	//暂停
	DE_GD_ListStatusType,	//终止上市
	UN_GD_ListStatusType,	//未上市
};

//股票分类代码
typedef char GD_EquTypeCD;
const GD_EquTypeCD		Whole_GD_EquTypeCD = 'W';	//全部
const GD_EquTypeCD		A_GD_EquTypeCD = 'A';		//A股
const GD_EquTypeCD		B_GD_EquTypeCD = 'B';		//B股

struct GD_StockBaseInfo	//股票基本信息 
{
	GD_CodeType szWindCode;				//证券代码
	GD_ShortText szListSector;			//上市板块
	GD_ShortText szTransCurrCD;			//交易货币
	GD_ShortText szSecShortName;		//证券简称
	GD_ShortText szSecFullName;			//全称
	GD_ListStatusType nListStatusCD;	//上市状态
	GD_ISODateTimeType szListDate;		//上市日期
	GD_ISODateTimeType szDelistDate;	//摘牌日期
	GD_EquTypeCD szEquTypeCD;			//股票分类代码
	GD_ShortText szEquType;				//股票类别
	int			nPartyId;				//机构内部ID
	double		nTotalShares;			//总股本（最新）
	double		nNonrestFloatShares;	//公司无限售流通股发合计（最新）
	double		nNonrestFloatA;			//无限售流通股本(最新)。如果为A股，该列为最新无限售流通A股股本数量；如果为B股，该列为最新流通B股股本数量
	GD_ShortText szOfficeAddr;			//办公地址
	GD_Text		szPrimeOperating;		//主营业务范围
	GD_ISODateTimeType szFinancialReportDate;		//财务报告日期
	double		nTShEquity;				//所有者权益合计
};

struct GD_RestorationFactor				//复权因子
{
	GD_CodeType szWindCode;				//证券代码
	GD_ISODateTimeType szExDivDate;		//除权除息日
	double nPerCashDiv;					//每股派现
	double nPerShareDivRatio;			//每股送股比例
	double nPerShareTransRatio;			//每股转增股比例
	double nAllotmentRatio;				//每股配股比例
	double nAllotmentPrice;				//配股价
	double nRestorationFactor;			//复权因子(前复权)
	double nAccumRestorationFactor;		//累积复权因子
	GD_ISODateTimeType szEndDate;		//累积复权因子截止日期
};

struct GD_DetailMarketDayKline			//详细日k线
{
	GD_CodeType szWindCode;				//证券代码
	GD_ISODateTimeType szTradeDate;		//交易日
	char szCodeCNName[32];				//证券中文名
	double nPreClose;					//昨收盘，即交易所给出的复权前收
	double nActPreClose;				//实际昨收盘
	double nOpen;						//今开盘
	double nHigh;						//最高价
	double nLow;						//最低价
	double nClose;						//今收盘
	double nVolume;						//成交量
	double nTurover;					//成交金额
	unsigned int nDealAmount;			//成交笔数
	double nTurnoverRate;				//日换手率
	double nAccumRestorationFactor;		//累计前复权因子 前复权是对历史行情进行调整，除权除息日的行情不受本次除权除息影响，不需进行调整。最新一次除权除息日至最新行情期间的价格不需要进行任何的调整，该期间前复权因子都是1。
	double nNegMarketValue;				//流通市值
	double nMarketValue;				//总市值
	double nChgPct;						//涨跌幅
	bool bIsOpen;						//是否开盘， false 未开盘，true 开盘
};

struct GD_StockFactors					//股票因子
{
	GD_CodeType szWindCode;						//证券代码
	GD_ISODateTimeType szTradeDate;				//交易日

	std::map<std::string, double> m_factors;
	/* factor key 说明
	ACD20							double	20日收集派发指标（Accumulative Distribution），将市场分为两股收集（买入）及派发（估出）的力量。属于均线型因子。
	ACD6							double	6日收集派发指标（Accumulative Distribution）。将市场分为两股收集（买入）及派发（估出）的力量。属于均线型因子
	AD								double	累积/派发线（Accumulation / Distribution Line，该指标将每日的成交量通过价格加权累计，用以计算成交量的动量。属于趋势型因子
	AD20							double	累积/派发线（Accumulation / Distribution Line，该指标将每日的成交量通过价格加权累计，用以计算成交量的动量。属于趋势型因子
	AD6								double	累积/派发线（Accumulation / Distribution Line，该指标将每日的成交量通过价格加权累计，用以计算成交量的动量。属于趋势型因子
	ADTM							double	动态买卖气指标，用开盘价的向上波动幅度和向下波动幅度的距离差值来描述人气高低的指标。属于超买超卖型因子。
	ADX								double	平均动向指数，DMI因子的构成部分。属于趋势型因子
	ADXR							double	相对平均动向指数，DMI因子的构成部分。属于趋势型因子
	APBMA							double	绝对偏差移动平均（Absolute Price Bias Moving Average）。考察一段时期内价格偏离均线的移动平均。属于均线型因子。
	AR								double	人气指标，是以当天开市价为基础，即以当天市价分别比较当天最高，最低价，通过一定时期内开市价在股价中的地位，反映市场买卖人气。属于能量型因子。
	ARBR							double	人气指标（AR）和意愿指标（BR）都是以分析历史股价为手段的技术指标，ARBR使用AR减去BR得到的值。属于能量型因子。
	ARC								double	变化率指数均值，股票的价格变化率RC指标的均值，用以判断前一段交易周期内股票的平均价格变化率。属于超买超卖型因子。
	Aroon							double	Aroon通过计算自价格达到近期最高值和最低值以来所经过的期间数，帮助投资者预测证券价格从趋势到区域区域或反转的变化，Aroon指标分为Aroon、AroonUp和AroonDown3个具体指标。属于趋势型因子
	AroonDown						double	计算Aroon因子的中间变量。属于趋势型因子
	AroonUp							double	计算Aroon因子的中间变量。属于趋势型因子
	ASI								double	累计振动升降指标（Accumulation Swing Index），又称实质线，ASI企图以开盘、最高、最低、收盘价构筑成一条幻想线，以便取代目前的走势，形成最能表现当前市况的真实市场线（Real Market）。
	ATR14							double	14日均幅指标（Average TRUE Ranger），取一定时间周期内的股价波动幅度的移动平均值，是显示市场变化率的指标，主要用于研判买卖时机。属于超买超卖型因子。
	ATR6							double	6日均幅指标（Average TRUE Ranger），取一定时间周期内的股价波动幅度的移动平均值，是显示市场变化率的指标，主要用于研判买卖时机。属于超买超卖型因子。
	BBI								double	多空指数（Bull and Bear Index）。是一种将不同日数移动平均线加权平均之后的综合指标。属于均线型因子。
	BBIC							double	因子BBI除以收盘价得到。属于均线型因子。
	BearPower						double	空头力道，是计算Elder因子的中间变量。属于能量型因子。
	BIAS10							double	10日乖离率，简称Y值，是移动平均原理派生的一项技术指标，表示股价偏离趋向指标斩百分比值。属于超买超卖型因子。
	BIAS20							double	20日乖离率，简称Y值，是移动平均原理派生的一项技术指标，表示股价偏离趋向指标斩百分比值。属于超买超卖型因子。
	BIAS5							double	5日乖离率，简称Y值，是移动平均原理派生的一项技术指标，表示股价偏离趋向指标斩百分比值。属于超买超卖型因子。
	BIAS60							double	60日乖离率，简称Y值，是移动平均原理派生的一项技术指标，表示股价偏离趋向指标斩百分比值。属于超买超卖型因子。
	BollDown						double	下轨线（布林线）指标（Bollinger Bands），它是研判股价运动趋势的一种中长期技术分析工具。属于超买超卖型因子。
	BollUp							double	上轨线（布林线）指标（Bollinger Bands），它是研判股价运动趋势的一种中长期技术分析工具。属于超买超卖型因子。
	BR								double	意愿指标，是以昨日收市价为基础，分别与当日最高，最低价相比，通过一定时期收市收在股价中的地位，反映市场买卖意愿的程度。属于能量型因子。
	BullPower						double	多头力道，是计算Elder因子的中间变量。属于能量型因子。
	CCI10							double	10日顺势指标（Commodity Channel Index），专门测量股价是否已超出常态分布范围。属于超买超卖型因子。
	CCI20							double	20日顺势指标（Commodity Channel Index），专门测量股价是否已超出常态分布范围。属于超买超卖型因子。
	CCI5							double	5日顺势指标（Commodity Channel Index），专门测量股价是否已超出常态分布范围。属于超买超卖型因子。
	CCI88							double	88日顺势指标（Commodity Channel Index），专门测量股价是否已超出常态分布范围。属于超买超卖型因子。
	ChaikinOscillator				double	佳庆指标（Chaikin Oscillator），该指标基于AD曲线的指数移动均线而计算得到。属于趋势型因子
	ChaikinVolatility				double	佳庆离散指标（Chaikin Volatility，简称CVLT，VCI，CV），又称“佳庆变异率指数”，是通过测量一段时间内价格幅度平均值的变化来反映价格的离散程度。属于趋势型因子
	ChandeSD						double	计算CMO因子的中间变量，SD是今日收盘价与昨日收盘价（下跌日）差值的绝对值加总。若当日上涨，则增加值为0。属于超买超卖型因子。
	ChandeSU						double	计算CMO因子的中间变量，SU是今日收盘价与昨日收盘价（上涨日）差值加总。若当日下跌，则增加值为0。属于超买超卖型因子。
	CMO								double	钱德动量摆动指标（Chande Momentum Osciliator），与其他动量指标摆动指标如相对强弱指标（RSI）和随机指标（KDJ）不同，钱德动量指标在计算公式的分子中采用上涨日和下跌日的数据。属于超买超卖型因子。
	CoppockCurve					double	估波指标（Coppock Curve），又称“估波曲线”，该指标通过计算月度价格的变化速率的加权平均值来测量市场的动量，属于长线指标，这里我们改为日间的指标。属于趋势型因子
	CR20							double	CR指标以上一个计算周期（这里为20日）的中间价比较当前周期的最高价、最低价，计算出一段时期内股价的“强弱”。属于能量型因子。
	DBCD							double	异同离差乖离率，先计算乖离率BIAS，然后计算不同日的乖离率之间的离差，最后对离差进行指数移动平滑处理。优点是能够保持指标的紧密同步，并且线条光滑，信号明确，能够有效的过滤掉伪信号。属于超买超卖型因子。
	DDI								double	方向标准离差指数，观察一段时间内股价相对于前一天向上波动和向下波动的比例，并对其进行移动平均分析，DDI指标倾向于显示一种长波段趋势的方向改变。属于趋势型因子
	DEA								double	计算MACD因子的中间变量。属于趋势型因子
	DIF								double	计算DDI因子的中间变量。属于趋势型因子
	DIFF							double	计算MACD因子的中间变量。属于趋势型因子
	DIZ								double	计算DDI因子的中间变量。属于趋势型因子
	DownRVI							double	计算RVI因子的中间变量。属于超买超卖型因子。
	Elder							double	艾达透视指标（Elder-ray Index），交易者可以经由该指标，观察市场表面之下的多头与空头力道。属于能量型因子。
	EMA12							double	12日指数移动均线（Exponential moving average）。属于均线型因子。
	EMA26							double	26日指数移动均线（Exponential moving average）。属于均线型因子。
	EMV14							double	简易波动指标（Ease of Movement Value），EMV将价格与成交量的变化结合成一个波动指标来反映股价或指数的变动状况，由于股价的变化和成交量的变化都可以引发该指标数值的变动，EMV实际上也是一个量价合成指标。属于趋势型因子
	EMV6							double	简易波动指标（Ease of Movement Value），EMV将价格与成交量的变化结合成一个波动指标来反映股价或指数的变动状况，由于股价的变化和成交量的变化都可以引发该指标数值的变动，EMV实际上也是一个量价合成指标。属于趋势型因子
	Hurst							double	赫斯特指数（Hurst exponent）。是由英国水文专家H．E．Hurst提出了用重标极差(R/S)分析方法来建立赫斯特指数(H)，作为判断时间序列数据遵从随机游走还是有偏的随机游走过程的指标。属于趋势型因子
	JDQS20							double	阶段强势指标，该指标计算一定周期N日内，大盘下跌时，个股上涨的比例。属于能量型因子。
	KDJ_D							double	随机指标。它综合了动量观念、强弱指标及移动平均线的优点，用来度量股价脱离价格正常范围的变异程度。属于超买超卖型因子。
	KDJ_J							double	随机指标。它综合了动量观念、强弱指标及移动平均线的优点，用来度量股价脱离价格正常范围的变异程度。属于超买超卖型因子。
	KDJ_K							double	随机指标。它综合了动量观念、强弱指标及移动平均线的优点，用来度量股价脱离价格正常范围的变异程度。属于超买超卖型因子。
	KlingerOscillator				double	成交量摆动指标，该指标在决定长期资金流量趋势的同时保持了对于短期资金流量的敏感性，因而可以用于预测短期价格拐点。属于成交量型因子
	MA10Close						double	均线价格比。由于股票的成交价格有响起均线回归的趋势，计算均线价格比可以预测股票在未来周期的运动趋势。属于均线型因子。
	MA10RegressCoeff12				double	10日价格平均线12日线性回归系数。属于趋势型因子
	MA10RegressCoeff6				double	10日价格平均线6日线性回归系数。属于趋势型因子
	MassIndex						double	梅斯线（Mass Index），本指标是Donald Dorsey累积股价波幅宽度之后所设计的震荡曲线。其最主要的作用，在于寻找飙涨股或者极度弱势股的重要趋势反转点。属于能量型因子。
	minusDI							double	下降指标，DMI因子的构成部分。属于趋势型因子
	MoneyFlow20						double	20日资金流量，用收盘价、最高价及最低价的均值乘以当日成交量即可得到该交易日的资金流量。属于成交量型因子
	MTM								double	动量指标（Momentom Index），动量指数以分析股价波动的速度为目的，研究股价在波动过程中各种加速，减速，惯性作用以及股价由静到动或由动转静的现象。属于趋势型因子
	MTMMA							double	因子MTM的10日均值。属于趋势型因子
	NVI								double	负成交量指标（Negative Volume Index），本指标的主要作用是辨别目前市场行情是处于多头行情还是空头行情，并追踪市场资金流向。属于能量型因子。
	OBV								double	能量潮指标（On Balance Volume，OBV），以股市的成交量变化来衡量股市的推动力，从而研判股价的走势。属于成交量型因子
	OBV20							double	20日能量潮指标（On Balance Volume，OBV），以股市的成交量变化来衡量股市的推动力，从而研判股价的走势。属于成交量型因子
	OBV6							double	6日能量潮指标（On Balance Volume，OBV），以股市的成交量变化来衡量股市的推动力，从而研判股价的走势。属于成交量型因子
	PLRC12							double	12日收盘价格价格线性回归系数（Price Linear Regression Coefficient）。属于趋势型因子
	PLRC6							double	6日收盘价格线性回归系数（Price Linear Regression Coefficient）。属于趋势型因子
	plusDI							double	上升指标，DMI因子的构成部分。属于趋势型因子
	PVI								double	正成交量指标（Positive Volume Index），本指标的主要作用是辨别目前市场行情是处于多头行情还是空头行情，并追踪市场资金流向。属于能量型因子。
	PVT								double	价量趋势（Price and Volume Trend）指标，把能量变化与价格趋势有机地联系到了一起，从而构成了量价趋势指标。属于趋势型因子
	PVT12							double	因子PVT的12日均值。属于趋势型因子
	PVT6							double	因子PVT的6日均值。属于趋势型因子
	RC12							double	12日变化率指数（Rate of Change），类似于动力指数，如果价格始终是上升的，则变化率指数始终在100%线以上，且如果变化速度指数在向上发展时，说明价格上升的速度在加快。属于能量型因子。
	RC24							double	24日变化率指数（Rate of Change），类似于动力指数，如果价格始终是上升的，则变化率指数始终在100%线以上，且如果变化速度指数在向上发展时，说明价格上升的速度在加快。属于能量型因子。
	ROC20							double	6日变动速率（Price Rate of Change），以当日的收盘价和N天前的收盘价比较，通过计算股价某一段时间内收盘价变动的比例，应用价格的移动比较来测量价位动量。属于超买超卖型因子。
	ROC6							double	6日变动速率（Price Rate of Change），以当日的收盘价和N天前的收盘价比较，通过计算股价某一段时间内收盘价变动的比例，应用价格的移动比较来测量价位动量。属于超买超卖型因子。
	RVI								double	相对离散指数（Relative Volatility Index），又称“相对波动性指标”，用于测量价格的发散趋势，主要用作辅助的确认指标，即配合均线系统、动量指标或其它趋势指标使用。属于超买超卖型因子。
	SBM								double	计算ADTM因子的中间变量。属于超买超卖型因子。
	SRMI							double	修正动量指标。属于超买超卖型因子。
	STM								double	计算ADTM因子的中间变量。属于超买超卖型因子。
	SwingIndex						double	振动升降指标，计算ASI因子的中间变量。属于趋势型因子
	TEMA10							double	10日三重指数移动平均线（Triple Exponential Moving Average），取时间N内的收盘价分别计算其一至三重指数加权平均。属于均线型因子。
	TEMA5							double	5日三重指数移动平均线（Triple Exponential Moving Average），取时间N内的收盘价分别计算其一至三重指数加权平均。属于均线型因子。
	TRIX10							double	10日收盘价三重指数平滑移动平均指标（Triple Exponentially Smoothed Average），TRIX根据移动平均线理论，对一条平均线进行三次平滑处理，再根据这条移动平均线的变动情况来预测股价的长期走势。属于趋势型因子
	TRIX5							double	5日收盘价三重指数平滑移动平均指标（Triple Exponentially Smoothed Average），TRIX根据移动平均线理论，对一条平均线进行三次平滑处理，再根据这条移动平均线的变动情况来预测股价的长期走势。属于趋势型因子
	TVMA20							double	20日成交金额的移动平均值（Turnover Value Moving Average）。属于成交量型因子
	TVMA6							double	6日成交金额的移动平均值（Turnover Value Moving Average）。属于成交量型因子
	TVSTD20							double	20日成交金额的标准差（Turnover Value Standard Deviation）。属于成交量型因子
	TVSTD6							double	20日成交金额的标准差（Turnover Value Standard Deviation）。属于成交量型因子
	Ulcer10							double	由Peter Martin于1987年提出，1989年发表于Peter Martin和Byron McCann的著作The Investors Guide to Fidelity Funds，用于考察向下的波动性。属于趋势型因子
	Ulcer5							double	由Peter Martin于1987年提出，1989年发表于Peter Martin和Byron McCann的著作The Investors Guide to Fidelity Funds，用于考察向下的波动性。属于趋势型因子
	UOS								double	终极指标（Ultimate Oscillator），现行使用的各种振荡指标，对于周期参数的选择相当敏感，不同市况、不同参数设定的振荡指标，产生的结果截然不同，因此，选择最佳的参数组合，成为使用振荡指标之前最重要的一道手续。属于趋势型因子
	UpRVI							double	计算RVI因子的中间变量。属于超买超卖型因子。
	VDEA							double	计算VMACD因子的中间变量（Volume Difference Exponential Average）。属于成交量型因子
	VDIFF							double	计算VMACD因子的中间变量。属于成交量型因子
	VEMA10							double	成交量的10日指数移动平均。属于成交量型因子
	VEMA12							double	成交量的12日指数移动平均。属于成交量型因子
	VEMA26							double	成交量的26日指数移动平均。属于成交量型因子
	VEMA5							double	成交量的5日指数移动平均。属于成交量型因子
	VMACD							double	成交量量指数平滑异同移动平均线（Volume Moving Average Convergence and Divergence），VMACD的意义和MACD基本相同, 但VMACD取用的数据源是成交量，MACD取用的数据源是成交价格。属于成交量型因子
	VOSC							double	成交量震荡（Volume Oscillator），又称移动平均成交量指标，但它并非仅仅计算成交量的移动平均线，而是通过对成交量的长期移动平均线和短期移动平均线之间的比较，分析成交量的运行趋势和及时研判趋势转变方向。属于成交量型因子
	VR								double	成交量比率（Volume Ratio），通过分析股价上升日成交额（或成交量，下同）与股价下降日成交额比值，从而掌握市场买卖气势的中期技术指标。属于成交量型因子
	VROC12							double	12日量变动速率指标（Volume Rate of Change），以今天的成交量和N天前的成交量比较，通过计算某一段时间内成交量变动的幅度，应用成交量的移动比较来测量成交量运动趋向，达到事先探测成交量供需的强弱，进而分析成交量的发展趋势及其将来是否有转势的意愿，属于成交量的反趋向指标。属于成交量型因子
	VROC6							double	6日量变动速率指标（Volume Rate of Change），以今天的成交量和N天前的成交量比较，通过计算某一段时间内成交量变动的幅度，应用成交量的移动比较来测量成交量运动趋向，达到事先探测成交量供需的强弱，进而分析成交量的发展趋势及其将来是否有转势的意愿，属于成交量的反趋向指标。属于成交量型因子
	VSTD10							double	10日成交量标准差（Volume Standard Deviation），考察成交量的波动程度。属于成交量型因子
	VSTD20							double	20日成交量标准差（Volume Standard Deviation），考察成交量的波动程度。属于成交量型因子
	AccountsPayablesTDays			double	应付账款周转天数（Accounts payable turnover days）。计算方法：应付账款周转天数=360/应付账款周转率。属于营运能力类因子。
	AccountsPayablesTRate			double	应付账款周转率（Accounts payable turnover rate）。计算方法：应付账款周转率=营业成本（TTM）/应付账款+应付票据+预付款项。属于营运能力类因子。
	AdminiExpenseRate				double	管理费用与营业总收入之比（Administrative expense rate）。计算方法：管理费用与营业总收入之比=管理费用（TTM）/营业总收入（TTM）。属于盈利能力和收益质量类因子。
	ARTDays							double	应收账款周转天数（Accounts receivable turnover days）。计算方法：应收账款周转天数=360/应收账款周转率。属于营运能力类因子。
	ARTRate							double	应收账款周转率（Accounts receivable turnover rate）。计算方法：应收账款周转率=营业收入（TTM）/应收账款+应收票据+预收账款。属于营运能力类因子。
	ASSI							double	对数总资产（Natural logarithm of total assets）。计算方法：对数总资产=总资产的对数。属于估值与市值类因子。
	BLEV							double	账面杠杆（Book leverage）。计算方法：账面杠杆=非流动负债合计/股东权益。属于偿债能力和资本结构类因子。
	BondsPayableToAsset				double	应付债券与总资产之比（Bonds payable to total assets）。计算方法：应付债券与总资产之比=应付债券/总资产。属于偿债能力和资本结构类因子。
	CashRateOfSales					double	经营活动产生的现金流量净额与营业收入之比（Cash rate of sales）。计算方法：经营活动产生的现金流量净额与营业收入之比=经营活动产生的现金流量净额（TTM）/营业收入（TTM）。属于现金流指标因子。
	CashToCurrentLiability			double	现金比率（Cash to current liability）。计算方法：现金比率=期末现金及现金等价物余额（TTM）/流动负债合计。属于现金流指标因子。
	CMRA							double	24 月累计收益（Monthly cumulative return range over the past 24 months）。属于超买超卖型因子。
	CTOP							double	现金流市值比（Cash flow to price）。计算方法：现金流市值比=每股派现（税前）×分红前总股本/总市值。属于现金流指标因子。
	CTP5							double	5年平均现金流市值比（Five-year average cash flow to price）。计算方法：5年平均现金流市值比=近五年每股派现（税前）×分红前总股本/近五年总市值。属于现金流指标因子。
	CurrentAssetsRatio				double	流动资产比率（Current assets ratio）。计算方法：流动资产比率=流动资产合计/总资产。属于偿债能力和资本结构类因子。
	CurrentAssetsTRate				double	流动资产周转率（Current assets turnover rate）计算方法：流动资产周转率=营业收入（TTM）/流动资产合计。属于营运能力类因子。
	CurrentRatio					double	流动比率（Current ratio），计算方法：流动比率=流动资产合计/流动负债合计。属于偿债能力和资本结构类因子。
	DAVOL10							double	10日平均换手率与120日平均换手率（Turnover Rate）之比。属于成交量型因子
	DAVOL20							double	20日平均换手率与120日平均换手率（Turnover Rate）之比。属于成交量型因子
	DAVOL5							double	5日平均换手率与120日平均换手率（Turnover Rate）之比。属于成交量型因子
	DDNBT							double	下跌贝塔（Downside beta），过往12 个月中，市场组合日收益为负时，个股日收益关于市场组合日收益的回归系数。属于超买超卖型因子。
	DDNCR							double	下跌相关系数（Downside correlation），过往12个月中，市场组合日收益为负时，个股日收益关于市场组合日收益的相关系数。属于超买超卖型因子。
	DDNSR							double	下跌波动（Downside standard deviations ratio），过往12个月中，市场组合日收益为负时，个股日收益标准差和市场组合日收益标准差之比。属于超买超卖型因子。
	DebtEquityRatio					double	产权比率（Debt equity ratio），计算方法：产权比率=负债合计/归属母公司所有者权益合计。属于偿债能力和资本结构类因子。
	DebtsAssetRatio					double	债务总资产比（Debt to total assets）。计算方法：债务总资产比=负债合计/总资产。属于偿债能力和资本结构类因子。
	DHILO							double	波幅中位数（median of volatility），每日对数最高价和对数最低价差值的3月内中位数。属于趋势型因子
	DilutedEPS						double	稀释每股收益（Diluted earnings per share）。属于每股指标因子
	DVRAT							double	收益相对波动（Daily returns variance ratio-serial dependence in daily returns）。属于超买超卖型因子。
	EBITToTOR						double	息税前利润与营业总收入之比。计算方法: 息税前利润与营业总收入之比=(利润总额+利息支出-利息收入)/ 营业总收入，如果没有利息支出，用财务费用代替，以上科目使用的都是TTM的数值。属于盈利能力和收益质量类因子。
	EGRO							double	5年收益增长率（Five-year earnings growth）。计算方法：5 年收益增长率= 5年收益关于时间（年）进行线性回归的回归系数/5 年收益均值的绝对值。属于盈利能力和收益质量类因子。
	EMA10							double	10日指数移动均线（Exponential moving average）。属于均线型因子。
	EMA120							double	120日指数移动均线（Exponential moving average）。属于均线型因子。
	EMA20							double	20日指数移动均线（Exponential moving average）。属于均线型因子。
	EMA5							double	5日指数移动均线（Exponential moving average）。属于均线型因子。
	EMA60							double	60日指数移动均线（Exponential moving average）。属于均线型因子。
	EPS								double	基本每股收益（Earnings per share）。属于每股指标因子
	EquityFixedAssetRatio			double	股东权益与固定资产比率（Equity fixed assets ratio）。计算方法：股东权益与固定资产比率=股东权益/(固定资产+工程物资+在建工程)。属于偿债能力和资本结构类因子。
	EquityToAsset					double	股东权益比率（Equity to total assets）。计算方法：股东权益比率=股东权益/总资产。属于偿债能力和资本结构类因子。
	EquityTRate						double	因子描述：股东权益周转率（Equity turnover rate） 计算方式：股东权益周转率=营业收入/股东权益
	ETOP							double	收益市值比（Earnings to price）。计算方法：收益市值比=净利润（TTM）/总市值。属于盈利能力和收益质量类因子。
	ETP5							double	5年平均收益市值比（Five-year average earnings to price）。计算方法：5年平均收益市值比=近五年净利润（TTM）/近五年总市值。属于盈利能力和收益质量类因子。
	FinancialExpenseRate			double	财务费用与营业总收入之比（Financial expense rate）。计算方法：财务费用与营业总收入之比=财务费用（TTM）/营业总收入（TTM）。属于盈利能力和收益质量类因子。
	FinancingCashGrowRate			double	筹资活动产生的现金流量净额增长率。计算方法：筹资活动产生的现金流量净额增长率=(今年筹资活动产生的现金流量净额（TTM）/去年筹资活动产生的现金流量净额（TTM）)-1。属于现金流指标因子。
	FixAssetRatio					double	固定资产比率（Fixed assets ratio）。计算方法：固定资产比率=(固定资产+工程物资+在建工程)/总资产。属于偿债能力和资本结构类因子。
	FixedAssetsTRate				double	固定资产周转率（Fixed assets turnover rate）。计算方法：固定资产周转率=营业收入（TTM）/固定资产+工程物资+在建工程。属于营运能力类因子。
	GrossIncomeRatio				double	销售毛利率（Gross income ratio），计算方法：销售毛利率=(营业收入（TTM）-营业成本（TTM）)/营业收入（TTM）。属于盈利能力和收益质量类因子。
	HBETA							double	历史贝塔（Historical daily beta），过往12个月中，个股日收益关于市场组合日收益的三阶自回归，市场组合日收益的系数。属于超买超卖型因子。
	HSIGMA							double	历史波动（Historical daily sigma），过往12个月中，个股日收益关于市场组合日收益的三阶自回归，市场组合日收益的残差标准差。属于超买超卖型因子。
	IntangibleAssetRatio			double	无形资产比率（Intangible assets ratio）。计算方法：无形资产比率=(无形资产+研发支出+商誉)/总资产。属于偿债能力和资本结构类因子。
	InventoryTDays					double	存货周转天数（Inventory turnover days）。计算方法：存货周转天数=360/存货周转率。属于营运能力类因子。
	InventoryTRate					double	存货周转率（Inventory turnover rate）。计算方法：存货周转率=营业成本（TTM）/存货。属于营运能力类因子。
	InvestCashGrowRate				double	投资活动产生的现金流量净额增长率（Growth rate of cash flows from investments）。计算方法：投资活动产生的现金流量净额增长率=(今年投资活动产生的现金流量净额（TTM）/去年投资活动产生的现金流量净额（TTM）)-1。属于现金流指标因子。
	LCAP							double	对数市值（Natural logarithm of total market values）。计算方法：对数市值=市值的对数。属于估值与市值类因子。
	LFLO							double	对数流通市值（Natural logarithm of float market values）。计算方法：对数流通市值=流通市值的对数。属于估值与市值类因子。
	LongDebtToAsset					double	长期借款与资产总计之比（Long term loan to total assets）。计算方法：长期借款与资产总计之比=长期借款/总资产。属于偿债能力和资本结构类因子。
	LongDebtToWorkingCapital		double	长期负债与营运资金比率（Long term debt to working capital）。计算方法：长期负债与营运资金比率=非流动负债合计/(流动资产合计-流动负债合计)。属于偿债能力和资本结构类因子。
	LongTermDebtToAsset				double	长期负债与资产总计之比（Long term debt to total assets）。计算方法：长期负债与资产总计之比=非流动负债合计/总资产。属于偿债能力和资本结构类因子。
	MA10							double	10日移动均线（Moving average）。取最近N天的前复权价格的均值。属于均线型因子。
	MA120							double	120日移动均线（Moving average）。取最近N天的前复权价格的均值。 属于均线型因子。
	MA20							double	20日移动均线（Moving average）。取最近N天的前复权价格的均值。属于均线型因子。
	MA5								double	5日移动均线（Moving average）。取最近N天的前复权价格的均值。属于均线型因子。
	MA60							double	60日移动均线（Moving average）。取最近N天的前复权价格的均值。属于均线型因子。
	MAWVAD							double	因子WVAD的6日均值。属于超买超卖型因子。
	MFI								double	资金流量指标（Money Flow Index），该指标是通过反映股价变动的四个元素：上涨的天数、下跌的天数、成交量增加幅度、成交量减少幅度来研判量能的趋势，预测市场供求关系和买卖力道。属于超买超卖型因子。
	MLEV							double	市场杠杆（Market leverage）。计算方法：市场杠杆=非流动负债合计/(非流动负债合计+总市值)。属于偿债能力和资本结构类因子。
	NetAssetGrowRate				double	净资产增长率（Net assets growth rate）。计算方法：净资产增长率=(今年股东权益/去年股东权益)-1。属于成长能力类因子。
	NetProfitGrowRate				double	净利润增长率（Net profit growth rate）。计算方法：净利润增长率=(今年净利润（TTM）/去年净利润（TTM）)-1。属于成长能力类因子。
	NetProfitRatio					double	销售净利率（Net profit ratio），计算方法：销售净利率=净利润（TTM）/营业收入（TTM）。属于盈利能力和收益质量类因子。
	NOCFToOperatingNI				double	经营活动产生的现金流量净额与经营活动净收益之比。计算方法：经营活动产生的现金流量净额与经营活动净收益之比=经营活动产生的现金流量净额（TTM）/(营业总收入（TTM）-营业总成本（TTM）)。属于现金流指标因子。
	NonCurrentAssetsRatio			double	非流动资产比率（Non-current assets ratio）。计算方法：非流动资产比率=非流动资产合计/总资产。属于偿债能力和资本结构类因子。
	NPParentCompanyGrowRate			double	归属母公司股东的净利润增长率。计算方法：归属母公司股东的净利润增长率=(今年归属于母公司所有者的净利润（TTM）/去年归属于母公司所有者的净利润（TTM）)-1。属于成长能力类因子。
	NPToTOR							double	净利润与营业总收入之比（Net profit to total operating revenues），计算方法：净利润与营业总收入之比=净利润（TTM）/营业总收入（TTM）。属于盈利能力和收益质量类因子。
	OperatingExpenseRate			double	营业费用与营业总收入之比（Operating expense rate）。计算方法：营业费用与营业总收入之比=销售费用（TTM）/营业总收入（TTM）。属于盈利能力和收益质量类因子。
	OperatingProfitGrowRate			double	营业利润增长率（Operating profit growth rate）。计算方法：营业利润增长率=(今年营业利润（TTM）/去年营业利润（TTM）)-1。属于成长能力类因子。
	OperatingProfitRatio			double	营业利润率（Operating profit ratio），计算方法：营业利润率=营业利润（TTM）/营业收入（TTM）。属于盈利能力和收益质量类因子。
	OperatingProfitToTOR			double	营业利润与营业总收入之比（Operating profit to total operating revenues），计算方法：营业利润与营业总收入之比=营业利润（TTM）/营业总收入（TTM）。属于盈利能力和收益质量类因子。
	OperatingRevenueGrowRate		double	营业收入增长率（Operating revenue growth rate）。计算方法：营业收入增长率=（今年营业收入（TTM）/去年营业收入（TTM））-1。属于成长能力类因子。
	OperCashGrowRate				double	经营活动产生的现金流量净额增长率。计算方法：经营活动产生的现金流量净额增长率=(今年经营活动产生的现金流量净额（TTM）/去年经营活动产生的现金流量净额（TTM）)-1。属于现金流指标因子。
	OperCashInToCurrentLiability	double	现金流动负债比（Cash provided by operations to current liability）。计算方法：现金流动负债比=经营活动产生的现金流量净额（TTM）/流动负债合计。属于现金流指标因子。
	PB								double	市净率（Price-to-book ratio）。计算方法：市净率=总市值/归属于母公司所有者权益合计。属于估值与市值类因子。
	PCF								double	市现率（Price-to-cash-flow ratio）。计算方法：总市值/经营活动产生的现金流量净额（TTM）。属于估值与市值类因子。
	PE								double	市盈率（Price-earnings ratio）。使用TTM算法。市盈率=总市值/归属于母公司所有者的净利润（TTM）。属于估值与市值类因子。
	PS								double	市销率（Price-to-sales ratio）。市销率=总市值/营业总收入（TTM）。属于估值与市值类因子。
	PSY								double	心理线指标（Psychological line index），是一定时期内投资者趋向买方或卖方的心理事实转的数值度量，用于判断股价的未来趋势。属于能量型因子。
	QuickRatio						double	速动比率（Quick ratio）。计算方法：速动比率=(流动资产合计-存货)/ 流动负债合计。属于偿债能力和资本结构类因子。
	REVS10							double	股票的10日收益。属于超买超卖型因子。
	REVS20							double	股票的20日收益。属于超买超卖型因子。
	REVS5							double	股票的5日收益。属于超买超卖型因子。
	ROA								double	资产回报率（Return on assets）。计算方法：资产回报率=净利润（TTM）/总资产。属于盈利能力和收益质量类因子。
	ROA5							double	5年资产回报率（Five-year average return on assets）。计算方法：5年资产回报率=净利润（TTM）/总资产。属于盈利能力和收益质量类因子。
	ROE								double	权益回报率（Return on equity）。计算方法：权益回报率=净利润（TTM）/股东权益。属于盈利能力和收益质量类因子。
	ROE5							double	因子描述：5 年权益回报率（Five-year average return on equity） 计算方式：5 年权益回报率=净利润/股东权益
	RSI								double	相对强弱指标（Relative Strength Index），通过比较一段时期内的平均收盘涨数和平均收盘跌数来分析市场买沽盘的意向和实力，据此预测趋势的持续或者转向。属于超买超卖型因子。
	RSTR12							double	12月相对强势（Relative strength for the last 12 months）。属于能量型因子。
	RSTR24							double	12月相对强势（Relative strength for the last 24 months）。属于能量型因子。
	SalesCostRatio					double	销售成本率（Sales cost ratio），计算方法：销售成本率=营业成本（TTM）/营业收入（TTM）。属于盈利能力和收益质量类因子。
	SaleServiceCashToOR				double	销售商品提供劳务收到的现金与营业收入之比（Sale service cash to operating revenues）。计算方法：销售商品提供劳务收到的现金与营业收入之比=销售商品和提供劳务收到的现金（TTM）/营业收入（TTM）。属于现金流指标因子。
	SUE								double	未预期盈余（Standardized unexpected earnings）。计算方法：未预期盈余=(最近一年净利润-除去最近一年的过往净利润均值)/ 除去最近一年的过往净利润标准差。属于盈利能力和收益质量类因子。
	TaxRatio						double	销售税金率（Tax ratio），计算方法：销售税金率=营业税金及附加（TTM）/营业收入（TTM）。属于盈利能力和收益质量类因子。
	TOBT							double	超额流动（Liquidity-turnover beta）。属于能量型因子。
	TotalAssetGrowRate				double	总资产增长率（Total assets growth rate）。计算方法：总资产增长率=(今年总资产/去年总资产)-1。属于成长能力类因子。
	TotalAssetsTRate				double	因子描述：总资产周转率（Total assets turnover rate） 计算方式：总资产周转率=营业收入/总资产
	TotalProfitCostRatio			double	成本费用利润率（Total profit cost ratio）。计算方法：成本费用利润率=利润总额/(营业成本+财务费用+销售费用+管理费用)，以上科目使用的都是TTM的数值。属于盈利能力和收益质量类因子。
	TotalProfitGrowRate				double	利润总额增长率（Total profit growth rate）。计算方法：利润总额增长率=(今年利润总额（TTM）/去年利润总额（TTM）)-1。属于成长能力类因子。
	VOL10							double	10日平均换手率（Turnover Rate）。属于成交量型因子
	VOL120							double	120日平均换手率（Turnover Rate）。属于成交量型因子
	VOL20							double	20日平均换手率（Turnover Rate）。属于成交量型因子
	VOL240							double	240日平均换手率（Turnover Rate）。属于成交量型因子
	VOL5							double	5日平均换手率（Turnover Rate）。属于成交量型因子
	VOL60							double	60日平均换手率（Turnover Rate）。属于成交量型因子
	WVAD							double	威廉变异离散量（William's variable accumulation distribution），是一种将成交量加权的量价指标，用于测量从开盘价至收盘价期间，买卖双方各自爆发力的程度。属于超买超卖型因子。
	REC								double	分析师推荐评级（Recommended rating score by analyst）。属于分析师预期类因子。
	DAREC							double	分析师推荐评级变化（Changes of recommended rating score by analyst），相比于60 个交易日前。属于分析师预期类因子。
	GREC							double	分析师推荐评级变化趋势（Change tendency of recommended rating score by analyst），过去60 个交易日内的DAREC 符号加和。属于分析师预期类因子。
	FY12P							double	分析师盈利预测（Forecast earnings by analyst to market values）。属于分析师预期类因子。
	DAREV							double	分析师盈利预测变化（Changes of forecast earnings by analyst），相比于60个交易日前。属于分析师预期类因子。
	GREV							double	分析师盈利预测变化趋势（Change tendency of forecast earnings by analyst），过去60个交易日内的DAREV符号加和。属于分析师预期类因子。
	SFY12P							double	分析师营收预测（Forecast sales by analyst to market values）。属于分析师预期类因子。
	DASREV							double	分析师盈收预测变化（Changes of forecast sales by analyst），相比于60 个交易日前。属于分析师预期类因子。
	GSREV							double	分析师盈收预测变化趋势（Change tendency of forecast sales by analyst），过去60 个交易日内的DASREV 符号加和。属于分析师预期类因子。
	FEARNG							double	未来预期盈利增长（Growth of forecast earnings）。属于分析师预期类因子。
	FSALESG							double	未来预期盈收增长（Growth of forecast sales）。属于分析师预期类因子。
	TA2EV							double	资产总计与企业价值之比（Assets to enterprise value）。属于估值与市值类因子。
	CFO2EV							double	经营活动产生的现金流量净额与企业价值之比（Cash provided by operations to enterprise value）。属于现金流指标因子。
	ACCA							double	现金流资产比和资产回报率之差（Cash flow assets ratio minus return on assets）。计算方法：现金流资产比和资产回报率之差=（经营活动产生的金流量净额（TTM） - 净利润（TTM））/ 总资产。属于现金流指标因子。
	DEGM							double	毛利率增长（Growth rate of gross income ratio），去年同期相比。计算方法：毛利率增长=(今年毛利率（TTM）/去年毛利率（TTM）)-1。属于成长能力类因子。
	SUOI							double	未预期毛利（Standardized unexpected gross income）。属于盈利能力和收益质量类因子。
	EARNMOM							double	八季度净利润变化趋势（Change tendency of net profit in the past eight quarters），前8个季度的净利润，如果同比（去年同期）增长记为+1，同比下滑记为-1，再将8 个值相加。属于成长能力类因子。
	FiftyTwoWeekHigh				double	当前价格处于过去1 年股价的位置（Price level during the pasted 52 weeks）。属于超买超卖型因子。
	Volatility						double	换手率相对波动率（Volatility of daily turnover during the last N days）。属于超买超卖型因子。
	Skewness						double	股价偏度（Skewness of price during the last N days），过去20个交易日股价的偏度。属于超买超卖型因子。
	ILLIQUIDITY						double	收益相对金额比（Daily return to turnover value during the last N days），过去20个交易日收益相对金额的比例。属于超买超卖型因子。
	BackwardADJ						double	股价向后复权因子，复权是对股价和成交量进行权息修复。属于超买超卖型因子。
	MACD							double	平滑异同移动平均线（Moving Average Convergence Divergence）,又称移动平均聚散指标。属于趋势型因子
	*/
};
//////////////////////////////////////////////////////////////////////////
//请求
struct GD_RealTime_Req					//实盘数据请求
{
	bool	isAllMarket;				//是否订阅全市场
	int		nBeginTime;					//开始请求的时间  0 为从当前时刻， -1 为从开盘开始，hhMMsszzz(903001000) 为从指定时间开始
	int		nSubDataType;				//订阅代码类型
	int		nCodeNum;					//代码条数
	GD_CodeType szCodes[1];				//订阅代码首地址
};

struct GD_RealTimeGDKline_Req
{
	int		nCycType;					//周期类型
	bool	isAllMarket;				//是否订阅全市场
	int		nBeginTime;					//开始请求的时间  0 为从当前时刻， -1 为从开盘开始，hhMMsszzz(903001000) 为从指定时间开始
	int		nCodeNum;					//代码条数
	GD_CodeType szCodes[1];				//订阅代码首地址
};

struct GD_UpdateSubCodes_Req
{
	GD_UpdateSubCodeType nType;			//请求类型
	bool	isAllMarket;				//是否订阅全市场
	int		nCodeNum;					//代码条数
	GD_CodeType szCodes[1];				//订阅代码首地址
};

struct GD_SimulationTimeline_Req
{
	GD_ISODateTimeType szBeginDatetime;	//请求开始的时间
	GD_PlaybackSpeedType nType;			//回放速度
};

typedef GD_RealTime_Req GD_SimulationTick_Req;
typedef GD_RealTimeGDKline_Req GD_SimulationGDKline_Req;
typedef GD_UpdateSubCodes_Req GD_SimulationUpdateSubCodes_Req;

struct GD_HistoryData_Req				//模拟数据请求
{
	GD_ISODateTimeType szBeginDatetime;	//请求开始的时间
	GD_ISODateTimeType szEndDatetime;	//请求结束的时间
	GD_PlaybackSpeedType nModelType;		//回测模式
	bool	isAllMarket;				//是否订阅全市场
	int		nCodeNum;					//代码条数
	GD_CodeType szCodes[1];				//订阅代码首地址
};

struct GD_HistoryKline_Req						//模拟数据请求
{
	GD_CycType nType;					//周期类型
	GD_ISODateTimeType szBeginDatetime;	//请求开始的时间
	GD_ISODateTimeType szEndDatetime;	//请求结束的时间
	bool	isAllMarket;				//是否订阅全市场
	int		nCodeNum;					//代码条数
	GD_CodeType szCodes[1];				//订阅代码首地址
};

struct GD_TradingDay_Req				//查询一段时间内的所有交易日
{
	GD_ISODateTimeType szBeginDay;		//开始时间
	GD_ISODateTimeType szEndDay;		//结束的时间
};

//////////////////////////////////////////////////////////////////////////
//回调

typedef GD_ISODateTimeType GD_TradingDateBegin_Rsp;		//交易日开始
typedef GD_ISODateTimeType GD_TradingDateEnd_Rsp;		//交易日结束
typedef GD_SimulationTimeline_Req GD_SimulationTimelineConfirmed_Rsp;	//模拟时间线确认，开始回放数据

//服务器连接类型代码
typedef char PT_ServerTypeCD;
const PT_ServerTypeCD		Realtime_PT_ServerTypeCD = 10;		//实时行情服务器
const PT_ServerTypeCD		History_PT_ServerTypeCD = 12;		//历史行情服务器

struct GD_Kline_Data						//模拟数据请求
{
	GD_CycType nType;					//周期类型
	char	szCode[32];					//是否订阅全市场
	GD_ISODateTimeType szDatetime;		//时间
	unsigned int nDate;					//日期 yyyyMMdd
	unsigned int nTime;					//时间 hhmmsszzz
	double	nOpen;
	double	nHigh;
	double	nLow;
	double	nClose;
	double	nPreClose;					//昨日收盘价
	double	nHighLimit;
	double	nLowLimit;
	unsigned long long iVolume;
	double	nTurover;
};

struct GD_Stock_Timeliness_Notification
{
	bool isTick;						//True 为tick, false 为K线数据
	GD_TimelinessType nType;			//数据时效性属性
	GD_CodeType szCode;					//代码名称
};

struct GD_TradingDay_Rsp
{
	unsigned nNum;
	GD_ISODateTimeType mDayList[1];		//交易日列表首地址
};

#pragma pack(pop)
#endif // GETDATASTRUCT_H
