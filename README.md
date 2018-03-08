![img](http://www.quantplus.com.cn/static/img/logo_2.png)
# QuantPlus_Api_Cpp

[项目主页](http://www.quantplus.com.cn/"项目主页") 

QuantPlus_Api_Cpp是QuantPlus团队根据多年国内二级市场上的量化交易经验，将底层量化接口开放出来的一个产品。旨在为国内二级市场的**量化开发者**在数据、算法、交易等方面提供全面支持。目前已开放上证、深圳、中金所三个市场的level2深度行情数据、常用技术分析指标库、普通股票交易、融资融券交易的接口，不久后将开放个股期权交易接口的使用。

QuantPlus_Api 不仅仅是一个高速行情和整合了多家券商柜台的交易接口，还是 [QuantPlus](http://www.quantplus.com.cn/"QuantPlus") 匡益量化平台的入口。通过它量化开发者可以方便的构建自己的自动交易策略、信号提醒工具、甚至自己构建一个类似同花顺、大智慧的行情交易软件。

QuantPlus_Api_Cpp 是 QuantPlus_Api 接口的 c++ 实现

## 安装方法

你可以通过 [GitHub Releases](https://github.com/abramwang/PT_QuantBaseApi_Cpp/releases"GitHub Releases") 下载最新的版本并解压至任意目录下

`include` 为开发用头文件

`bin` 为各个版本库文件

现阶段暂时提供了Windows64位版本，后续会推出linux及其他平台版本



## 快速开始

我们创建一个简单的订阅平安银行的实时level2行情数据的demo

#### demo.cpp

```c++
#include <windows.h>
#include <iostream>
using namespace std;

#include <PT_QuantApi.h>

using namespace PT_QuantPlatform;

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



