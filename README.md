# QuantPlus_Api_Cpp

| 项目名称 | Quant量化系统平台      | 研发单位 |  |
| ---- | -------------------- | ---- | ------------ |
| 文档名称 | QuantBaseApi cpp开发手册 | 项目版本 | beta5.2.1   |
| 文档状态 | 编辑中                  | 发布日期 | 2018.12.21 |
| 文档编辑 | 杨军辉、王龙               | 文档版本 | 0.1          |

[项目主页](https://www.quantstage.com/) 

QuantBase_Api_Cpp是QuantBase团队根据多年国内二级市场上的量化交易经验，将底层量化接口开放出来的一个产品。旨在为国内二级市场的**量化开发者**在数据、算法、交易等方面提供全面支持。目前已开放上证、深圳、中金所三个市场的level2深度行情数据、常用技术分析指标库、普通股票交易、融资融券交易的接口，不久后将开放个股期权交易接口的使用。

QuantBase_Api 不仅仅是一个高速行情和整合了多家券商柜台的交易接口。通过它量化开发者可以方便的构建自己的自动交易策略、信号提醒工具、甚至自己构建一个类似同花顺、大智慧的行情交易软件。

QuantBase_Api_Cpp 是 QuantBase_Api 接口的 c++ 实现

## 安装方法


**终端下载**

- [Windows-64位](https://download.quantstage.com/)

  终端基于c++Api进行开发，账户与Api通用，用户可用终端数据作为参考

**Window版本**（建议使用环境：xp以上）

- [x64-msvc-12.0-Debug](https://github.com/abramwang/QuantStageApi_Cpp/raw/master/bin/lib-x64-msvc-12.0-Debug.zip)
- [x64-msvc-12.0-Release](https://github.com/abramwang/QuantStageApi_Cpp/raw/master/bin/lib-x64-msvc-12.0-Release.zip)

**Linux版本**（建议使用环境：ubuntu 16.04）

- [linux-gcc4.8](https://github.com/abramwang/QuantStageApi_Cpp/raw/master/bin/linux-gcc4.8.zip)
- [linux-gcc5.4](https://github.com/abramwang/QuantStageApi_Cpp/raw/master/bin/linux-gcc5.4.zip)


下载完成后解压至任意目录下。其中，windows版本的目录结构如下

```
├─QuantBaseApi
	├─PT_MarketDataApi.dll
	├─PT_QuantApi.dll
	├─PT_TradeDataApi.dll
	└─PT_QuantApi.lib


```

1、动态加载，只需将dll文件拷贝到可执行文件同目录下即可，lib文件无用。

2、静态加载，将dll文件拷贝到可执行文件同目录下，同时将lib文件拷贝到项目工程文件同目录下；请注意宏**WIN32**是否已经预定义，否则请自行定义或者自行指定lib依赖

linux 版本目录结构如下

```
├─QuantBaseApi
	├─libboost_chrono.so.1.64.0
	├─libboost_context.so.1.64.0
	├─libboost_coroutine.so.1.64.0
	├─libboost_date_time.so.1.64.0
	├─libboost_filesystem.so.1.64.0
	├─libboost_program_options.so.1.64.0
	├─libboost_system.so.1.64.0
	├─libboost_thread.so.1.64.0
	├─libprotobuf.so.13
	├─libPT_MarketDataApi.so
	├─libPT_QuantApi.so
	├─libPT_TradeDataApi.so
	├─libPTNetwork.so
	├─libsnappy.so.1
	└─libz.so.1

```

将QuantBaseApi目录下所有so文件拷贝到系统默认路径下，或者自行添加环境变量即可

snappy版本为1.1.3

protobuf版本为3.3.0

boost版本为1.64

[^注](https://github.com/abramwang/QuantPlusApi_Cpp/blob/master/doc/%E4%B8%9A%E5%8A%A1%E6%9C%8D%E5%8A%A1%E5%99%A8%E8%BF%9E%E9%80%9A%E6%97%B6%E4%B8%BB%E5%8A%A8%E9%80%9A%E7%9F%A5): 头文件都在[Include](https://github.com/abramwang/QuantPlusApi_Cpp/tree/master/include)中


## 快速开始

我们创建一个简单的订阅平安银行的实时level2行情数据的demo

#### demo.cpp

```c++
#include <windows.h>
#include <iostream>
using namespace std;

#include <PT_QuantApi.h>

using namespace QuantPlus;

//创建一个自己的回调数据处理类
class MySpi : public PT_QuantSpi{
private:
public:
	MySpi(){};
	~MySpi(){};
public:
	void OnRtnMarket(MD_ReqID nReqID, MD_DATA_MARKET *pMarket){
		cout << "OnRtnMarket: " << pMarket->szWindCode << " " << pMarket->nTime << endl;
	};
  	//为了简单其他其他纯虚函数没有重载，实际业务代码中每一个虚函数都需要重载
};

int main(int argc, char const *argv[])
{
	MySpi* spi = new MySpi();
	int err = 0;

	PT_QuantApi::Init();

	PT_QuantApi* api = PT_QuantApi::createApi(spi, true, PT_QuantTdAppEType_Test, false, PT_QuantMdAppEType_Real, true, false);    //此处只连接了行情业务服务器

	err = api->Login("test", "test");

	int codeNum = 1;
	MD_CodeType *pSubWindCode = new MD_CodeType[codeNum];

	for(int i = 0; i < codeNum; ++i)
	{
		memcpy(pSubWindCode[i], "600000.SH", sizeof(MD_CodeType));
	}

	int reqId = 1;
	Sleep(1000);    //此处做延时是为了等待异步connect连接成功，严格意义上需要等待onconnect函数返回判断对应的业务服务器连接成功之后才能做业务请求
	err = api->ReqSubQuote(reqId, MD_SubType_market, MD_CycType_none, pSubWindCode, codeNum, "2018-02-21 0:0:01", "2018-02-28 23:59:59");

	system("Pause");
	return 0;
}
```

## 文档 [详情](https://github.com/abramwang/QuantPlusApi_Cpp/tree/master/doc)

整个 QuantPlus_BaseApi 按照功能分类提供了3种类型的接口

**系统接口** [详情](https://github.com/abramwang/QuantPlusApi_Cpp/blob/master/doc/%E7%B3%BB%E7%BB%9F%E6%8E%A5%E5%8F%A3.md)

系统接口，API实例初始化、创建、删除、错误码的转换、股票代码表的获取、用户的登陆以及相关回调等功能

系统函数全部为同步函数！

**交易接口** [详情](https://github.com/abramwang/QuantPlusApi_Cpp/blob/master/doc/%E4%BA%A4%E6%98%93%E6%8E%A5%E5%8F%A3.md)

交易业务请求及相关回调、推送接口

**行情接口** [详情](https://github.com/abramwang/QuantPlusApi_Cpp/blob/master/doc/%E8%A1%8C%E6%83%85%E6%8E%A5%E5%8F%A3.md)

行情业务请求及相关回调、推送接口

