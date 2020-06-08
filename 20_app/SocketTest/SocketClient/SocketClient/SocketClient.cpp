﻿/********************************************************************************//*
*@file          SocketClient.cpp
*@brief         简易版TCP通信客户端
*
*@author        Herman
*@version       1.5
*@date          20200604
*@copyright     (c)1995-2020 Suzhou Keda Technology Co.,Ltd. All rights reserved
***********************************************************************************/

#include "CEasyTcpClient.h"
#include <thread>

void HandleInput(CEasyTcpClient* peasyTcpClient)
{
	char input[128] = {};
	while (true)
	{
		scanf("%s", input);
		if (0 == strcmp("login", input))
		{
			char achUserName[64] = {};
			char achPassWord[64] = {};
			printf("请输入用户名:\n");
			scanf("%s", achUserName);
			printf("请输入密码:\n");
			scanf("%s", achPassWord);
			TLogin* ptLogin = new TLogin();
			strcpy(ptLogin->achUserName, achUserName);
			strcpy(ptLogin->achPassWord, achPassWord);
			peasyTcpClient->SendData(peasyTcpClient->GetClientSocket(), (const char*)ptLogin, sizeof(TLogin), 0);
		}
		else if (0 == strcmp("logout", input))
		{
			TLogout tLogout;
			peasyTcpClient->SendData(peasyTcpClient->GetClientSocket(), (const char*)&tLogout, sizeof(TLogout), 0);
		}
		else
		{
			printf("Invalid operation!\n");
			continue;
		}
	}

}


int main()
{
	CEasyTcpClient cEasyTcpClient;
	cEasyTcpClient.Init();
	cEasyTcpClient.Connect(MYSERVERIP, MYPROT);
	std::thread t(HandleInput, &cEasyTcpClient);
	while ( INVALID_SOCKET != cEasyTcpClient.GetClientSocket() )
	{
		if (-1 == cEasyTcpClient.RecvData())
			break;
	}
	t.join();
	
	getchar();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
