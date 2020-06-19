
/********************************************************************************//*
*@file          CEasyTcpServer.h
*@brief         简易版TCP通信服务器
*
*@author        Herman
*@version       1.5
*@date          20200604
*@copyright     (c)1995-2020 Suzhou Keda Technology Co.,Ltd. All rights reserved
***********************************************************************************/
#pragma once

#ifdef _WIN32
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <WinSock2.h>
	#include <Windows.h>
	#pragma comment(lib,"ws2_32.lib")
#else
	#include <unistd.h>
	#include <arpa/inet.h>
	#define SOCKET int
	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)
#endif

#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include "easytcptype.h"
#include <chrono>

class CEasyTcpServer
{
public:
	CEasyTcpServer();
	virtual ~CEasyTcpServer();

	int Init();
	int Bind(const char* addr_ip, unsigned short addr_port);
	int Listen(int backLog);
	SOCKET GetServerSocket() const;
	int Accpet();
	int RecvData();
	int SendData(SOCKET sc, const char* data, int len, int flags);
	int OnNetMsg(SOCKET sc, char* recvBuff);
	int Close();


private:
	SOCKET m_scServer;
	std::vector<SOCKET> m_vcScClient;

	char recvBuff[1024];

	long long _nCount;
	std::chrono::high_resolution_clock::time_point _begin;

	
};