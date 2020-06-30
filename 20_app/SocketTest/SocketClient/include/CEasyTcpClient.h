/********************************************************************************//*
*@file          CEasyTcpClient.h
*@brief         简易版TCP通信客户端
*
*@author        Herman
*@version       1.5
*@date          20200604
*@copyright     (c)1995-2020 Suzhou Keda Technology Co.,Ltd. All rights reserved
***********************************************************************************/

#pragma once

#ifdef WIN32
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
	#include <WinSock2.h>
	#include <Windows.h>
	#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#else
	#include <unistd.h>
	#include <arpa/inet.h>
	#define SOCKET int
	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)
#endif // WIN32

#include <stdio.h>
#include "easytcptype.h"

class CEasyTcpClient
{
public:
	CEasyTcpClient();
	virtual ~CEasyTcpClient();

	int Init();
	int Connect(const char* addr_ip, unsigned short addr_port);
	int RecvData();
	int SendData(SOCKET sc, const char* data, int len, int flags);
	int OnNetMsg(SOCKET sc,char* recvBuff);
	SOCKET GetClientSocket() const;

private:
	SOCKET m_scClient;
};