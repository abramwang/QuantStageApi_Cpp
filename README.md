# PT_QuantBaseApi_Cpp

[项目主页](http://www.praestans.tech/"项目主页") 

PT_QuantBaseApi_Cpp 是 PT_QuantBaseApi 接口的 C++ 实现





## 安装方法

### 



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





