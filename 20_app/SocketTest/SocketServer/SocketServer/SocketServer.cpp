// SocketServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#ifdef WIN32
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <WinSock2.h>	
	#include <Windows.h>
	#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#else
	#include <unistd.h>
	#include <apra/inet.h>
	#define SOCKET int
	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)
#endif // WIN32

#include <stdio.h>
#include <iostream>
#include <thread>
#include <vector>

//using namespace std; 不能使用，否则会出错

#define MYSERVERIP	"127.0.0.1"
#define MYPROT	2501

enum EMEvent
{
	emLoginReq,
	emLoginRsp,
	emQuitCmd,
	emQuitInd,
};

struct THeader
{
	EMEvent emEvent;
	int		length;
};

struct TLogin : public THeader
{
	TLogin()
	{
		emEvent = emLoginReq;
		length = sizeof(TLogin);
	}

	char achUserName[64];
	char achPassWord[64];
};

struct TLoginResult : public THeader
{
	TLoginResult()
	{
		emEvent = emLoginRsp;
		length = sizeof(TLoginResult);
		result = 0;
	}
	int result;
};

struct TLogout : public THeader
{
	TLogout()
	{
		emEvent = emQuitCmd;
		length = sizeof(TLogout);
		cmd = 0;
	}
	int cmd;
};

struct TLogoutRes : public THeader
{
	TLogoutRes()
	{
		emEvent = emQuitInd;
		length = sizeof(TLogoutRes);
		res = 0;
	}
	int res;
};


int HandleClient(SOCKET sClient)
{
	THeader tHeader;
	TLogin tLoginInfo;
	TLoginResult tLoginRes;
	TLogout tLogout;
	TLogoutRes tLogoutRes;
	char recvBuff[1024] = { 0 };
	if ( sClient != INVALID_SOCKET )
	{
		// 从客户端接收数据
		int resultRecv = (int)recv(sClient, (char*)&tHeader, sizeof(THeader), 0);//从客户端接受消息
		if (resultRecv > 0)
		{
			switch ( tHeader.emEvent )
			{
			case emLoginReq:
				recv(sClient, (char*)&tLoginInfo + sizeof(THeader), sizeof(TLogin) - sizeof(THeader), 0);
				printf("收到客户端%d的登录emLoginReq请求消息: %s, %s \n", sClient, tLoginInfo.achUserName, tLoginInfo.achPassWord);
				tLoginRes.result = 8;
				send(sClient, (const char*)&tLoginRes, sizeof(TLoginResult), 0);
				break;
			case emQuitCmd:
				recv(sClient, (char*)&tLogout + sizeof(THeader), sizeof(TLogout) - sizeof(THeader), 0);
				printf("收到客户端%d的登出emQuitCmd请求消息: %d \n", sClient, tLogout.cmd);
				tLogoutRes.res = 9;
				send(sClient, (const char*)&tLogoutRes, sizeof(TLogoutRes), 0);
				break;
			default:
				printf("收到未知消息!\n");
				break;
			}
		}
		else
		{
			//这几种错误码，认为连接是正常的，继续接收
			if ((resultRecv < 0) && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
			{
				return 0;
				//continue;
			}
			printf("客户端 %d 退出！\n", sClient);
			//break;
			return -1;
		}
	}
	return 0;
};

int main()
{
#ifdef _WIN32
	WSADATA wsaData;
	if ( WSAStartup(MAKEWORD(2,2), &wsaData) != 0  )
	{
		std::cout << "Socket版本错误!" << std::endl;
	}
#endif

	SOCKET nServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	int _nport = 2500;
	sockaddr_in Serveraddr;
	memset(&Serveraddr, 0, sizeof(sockaddr_in*));
	Serveraddr.sin_family = AF_INET;
	//inet_pton(AF_INET, MYSERVERIP, (void *)&Serveraddr.sin_addr);		//方法一，通过SDL检查
	//Serveraddr.sin_addr.s_addr = inet_addr(MYSERVERIP);				//方法二
	Serveraddr.sin_addr.s_addr = ADDR_ANY;								//方法三
	Serveraddr.sin_port = htons(_nport);
	int nRet = bind(nServerSocket, (sockaddr *)&Serveraddr, sizeof(Serveraddr));
	while ( SOCKET_ERROR == nRet && _nport < 2510 )
	{
		_nport++;
		Serveraddr.sin_port = htons(_nport);
		if ( SOCKET_ERROR != bind(nServerSocket, (sockaddr *)&Serveraddr, sizeof(Serveraddr)) )
		{
			break;
		}
	}
	printf("监听端口开启:%d\n", _nport);

	nRet = listen(nServerSocket, 5);
	if ( SOCKET_ERROR == nRet )
	{
		std::cout << "监听失败!\n" << std::endl;
	}


	std::vector<SOCKET> g_Client;

	int ndfs = nServerSocket + 1;
	fd_set fdRead;
	fd_set fdWrite;
	fd_set fdExp;
	timeval timeout = { 2,0 };

	while (true)
	{
		FD_ZERO(&fdRead);
		FD_ZERO(&fdWrite);
		FD_ZERO(&fdExp);

		FD_SET(nServerSocket, &fdRead);

		if (!g_Client.empty())
		{
			printf("所有客户端: ");
		}
		//for(int n = g_Client.size() - 1; n>=0; n--)
		for (auto iter = g_Client.begin(); iter != g_Client.end(); iter++)
		{
			//FD_SET(g_Client[n], &fdRead);
			//printf("检查 %d  ", g_Client[n]);
			FD_SET(*iter, &fdRead);
			printf(" %d  ", *iter);
		}
		if ( !g_Client.empty() )
		{
			printf("\n");
		}

		int ret = select(ndfs, &fdRead, &fdWrite, &fdExp, &timeout);
		if (ret < 0 )
		{
			break;
		}

		if (FD_ISSET(nServerSocket,&fdRead))
		{
			FD_CLR(nServerSocket,&fdRead);
			sockaddr_in clientaddr;
			int length = sizeof(sockaddr_in);
			SOCKET _sClient = accept(nServerSocket, (sockaddr*)&clientaddr, &length);
			printf("有新客户端加入: %d, IP = %s\n", _sClient, inet_ntoa(clientaddr.sin_addr));
			g_Client.push_back(_sClient);
		}

		for (int n = 0; n < g_Client.size(); n++)
		{
			if (FD_ISSET(g_Client[n],&fdRead))
			{
				if (-1 == HandleClient(g_Client[n]))
				{
					auto iter = std::find(g_Client.begin(), g_Client.end(), g_Client[n]);
					if ( iter != g_Client.end() )
					{
						g_Client.erase(iter);
					}
				}
			}
		}
	}
	for (auto iter = g_Client.begin(); iter != g_Client.end(); iter++)
	{
		closesocket(*iter);
	}


#ifdef _WIN32
	WSACleanup();
#endif // _WIN32

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
