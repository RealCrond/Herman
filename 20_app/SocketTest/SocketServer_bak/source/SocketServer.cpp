/********************************************************************************//*
*@file          SocketServer.cpp
*@brief         简易版TCP通信服务器
*
*@author        Herman
*@version       1.5
*@date          20200604
*@copyright     (c)1995-2020 Suzhou Keda Technology Co.,Ltd. All rights reserved
***********************************************************************************/

#include "CEasyTcpServer.h"

int main()
{
	CEasyTcpServer cEasyTcpServer;
	cEasyTcpServer.Init();
	if (SOCKET_ERROR == cEasyTcpServer.Bind(NULL, MYPROT))
		printf("Fail to bind!");
	
	cEasyTcpServer.Listen(5);
	printf("Listening....\n");

	while ( INVALID_SOCKET != cEasyTcpServer.GetServerSocket() )
	{
		if (-1 == cEasyTcpServer.RecvData())
		{
			continue;
		}	
	}

	getchar();
	return 0;
}
