// testTraderApi.cpp : 定义控制台应用程序的入口点。
//
#include "ThostFtdcTraderApi.h"
#include "TraderSpi.h"
#include "PgsqlConfig.h"

// UserApi对象
CThostFtdcTraderApi* pUserApi;

// 配置参数

CPgsqlConfig g_PgsqlConfig;

TThostFtdcInstrumentIDType INSTRUMENT_ID = "cu0909";		// 合约代码
TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;		// 买卖方向
TThostFtdcPriceType	LIMIT_PRICE = 38850;			// 价格

// 请求编号
int iRequestID = 0;

int main(void)
{
	g_PgsqlConfig.InitializeConfig();
	// 初始化UserApi
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();				// 创建UserApi
	CTraderSpi* pUserSpi = new CTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);				// 注册事件类
	pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);				// 注册公有流
	pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);				// 注册私有流
	pUserApi->RegisterFront(const_cast<char*>(g_PgsqlConfig.GetFrontAddress().c_str()));	// connect
	pUserApi->Init();

	pUserApi->Join();
	pUserApi->Release();
	return 0;
}
