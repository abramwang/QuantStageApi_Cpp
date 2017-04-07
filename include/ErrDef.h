#ifndef ERRDEF_H
#define ERRDEF_H

namespace PT_QuantPlatform {
	enum PT_ErrorType
	{
		PT_ErrorType_none,						//无

		//登录
		PT_ErrorType_userError = 1,				//用户不存在或用户名密码错误
		PT_ErrorType_overLoginNumError,			//登录数超限
		PT_ErrorType_notloginyet,               //未登录

		//注册
		PT_ErrorType_userNameAlreadyExists = 5, //用户名已存在
		PT_ErrorType_mobileAlreadyExists,		//手机号已存在
		PT_ErrorType_mailAlreadyExists,			//注册邮箱已存在
		PT_ErrorType_passIsTooWeak,				//密码太弱

		//请求错误
		PT_ErrorType_serverConnectedError = 10,	//服务器连接错误
		PT_ErrorType_sendFailed,                //服务器发送指令失败
		PT_ErrorType_dbOperationFailed,         //数据库操作错误
		PT_ErrorType_noServerCanbeused,         //没有可用服务器
		PT_ErrorType_securityCodeMismatch,      //动态口令验证失败
		PT_ErrorType_noPrivilege,               //无此权限
		PT_ErrorType_noTavailableFuction,       //暂不支持此功能
		PT_ErrorType_loadDynLibraryFailed,      //动态库加载失败

		//交易部分
		PT_ErrorType_orderNotFound = 200,          //无此订单
		PT_ErrorType_finishedOrder,                //已完结的订单
		PT_ErrorType_breakRule,                    //非法订单
		PT_ErrorType_notTradingTime,               //非交易时间
		PT_ErrorType_badModifyOrder,               //非法的改单
		PT_ErrorType_notEnoughPosition,            //仓位不足
		PT_ErrorType_notEnoughMoney,               //资金不足
		PT_ErrorType_sucrityAccountNotAvailable,   //该资金通道异常
		PT_ErrorType_cancelFailed_canotCancelYet,  //撤单失败，暂时不能撤单
		PT_ErrorType_cannotselfdeal,               //不能自成交
		PT_ErrorType_TooHighFrequency,             //频率太高


		//行情部分
		

		//系统部分
		PT_ErrorType_invalidAargument = 1000,			//非法的参数
		PT_ErrorType_invalidSimulationObjectInstance	//错误的模拟交易api实例
	};
}
#endif