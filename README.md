![项目主页](http://www.praestans.tech/static/img/logo.jpg)
# PT_QuantBaseApi_Cpp

[项目主页](http://www.praestans.tech/"项目主页") 

PT_QuantBaseApi  是 Praestans Quant 团队根据多年国内二级市场上的量化交易经验，将底层量化接口开放出来的一个产品。旨在为国内二级市场的**量化开发者**在数据、算法、交易等方面提供全面支持。目前已开放上证、深圳、中金所三个市场的level2深度行情数据、常用技术分析指标库、普通股票交易、融资融券交易的接口，不久后将开放个股期权交易接口的使用。

PT_QuantBaseApi 不仅仅是一个高速行情和整合了多加券商柜台的交易接口，还是 [Praestans.tech](http://www.praestans.tech/"Praestan.tech") 这个量化平台的入口。通过它量化开发者可以方便的构建自己的自动交易策略、信号提醒工具、甚至自己构建一个类似同花顺、大智慧的行情交易软件。

PT_QuantBaseApi_Cpp 是 PT_QuantBaseApi 接口的 C++ 实现

## 安装方法

你可以通过 [GitHub Releases](https://github.com/abramwang/PT_QuantBaseApi_Cpp/releases"GitHub Releases") 下载最新的版本并解压至任意目录下

`include` 为开发用头文件

`lib_gcc` 为linux下lib，编译版本为 gcc 4.8.5

`lib_msvc` 为windows 下用dll，编译版本为 Visual Studio 2013

其中依赖 boost 1.57 版本，如果开发项目中有用到



## 快速开始

我们创建一个简单的订阅平安银行的实时level2行情数据的demo

#### demo.cpp

```c++
#ifndef WIN32
typedef long long __int64;
#endif
#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include <GetDataStruct.h>
#include <GetDataApi.h>

using namespace PT_QuantPlatform;

//创建一个自己的回调数据处理类
class MySpi : public GetDataSpi{
private:
public:
	MySpi(){};
	~MySpi(){};
public:
	void OnRecvMarket(TDF_MARKET_DATA* pMarket){
		cout << "OnRecvMarket: " << pMarket->szWindCode << " " << pMarket->nTime << endl;
	};
};

int main(int argc, char const *argv[])
{
	MySpi* spi = new MySpi();
	GetDataApi* api = CreateGetDataApi(spi, true, 1000, true);
  
	int err = 0;
  	if(api->Login("Test", "Test", err)){	
    	std::vector<char*> subCodes;
        subCodes.push_back("000001");

        api->ReqRealtimeData(subCodes, false, 0, 0, err);

        while(1){
			int y = 0;
        }
  	}	
	return 0;
}
```



### 编译

####示例makefile

```cmake
INC_PATH := -I../include/
LIB_PATH := -L../lib_gcc/
LIBS     := $(LIB_PATH) -lPTQuantBaseApi -lsnappy -lboost_thread -lboost_system -ljson_linux-gcc-4.8.5_libmt -lboost_locale
CC       := gcc
LD       := g++
CFLAGS   := -O2 -Wall $(INC_PATH)
SRC_PATH := ./
SOURCE   := $(SRC_PATH)/demo.cpp
			
TARGET   := demo
OBJS     := demo.o
$(TARGET): $(OBJS)
	$(LD) -O2 -o $(TARGET) $(OBJS) $(LIBS)
demo.o : $(SRC_PATH)/demo.cpp
	$(CC) $(CFLAGS) -c $(SRC_PATH)/demo.cpp -o $@
.PHONY: clean
clean:
	-rm -rf $(OBJS)
cleanT:
	-rm -rf $(TARGET)
```





