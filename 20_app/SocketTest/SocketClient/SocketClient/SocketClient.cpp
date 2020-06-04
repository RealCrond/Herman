// SocketClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#ifdef WIN32
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <WinSock2.h>
	//#include <WS2tcpip.h>
	#include <Windows.h>
	#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#else
	#include <unistd.h>
	#include <apra/inet.h>
	#define SOCKET int
	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)
#endif // WIN32

#include <iostream>
#include <thread>

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


int HandleSocket(SOCKET sClient)
{
	THeader tHeader;
	TLogin tLoginInfo;
	TLoginResult tLoginRes;
	TLogout tLogout;
	TLogoutRes tLogoutRes;
	char recvBuff[1024] = { 0 };
	if (sClient != INVALID_SOCKET)
	{
		// 从客户端接收数据
		int resultRecv = recv(sClient, (char*)&tHeader, sizeof(THeader), 0);//从客户端接受消息
		if (resultRecv > 0)
		{
			switch (tHeader.emEvent)
			{
			case emLoginRsp:
				recv(sClient, (char*)&tLoginRes + sizeof(THeader), sizeof(TLoginResult) - sizeof(THeader), 0);
				printf("收到登录回应: %d\n", tLoginRes.result);
				break;
			case emQuitInd:
				recv(sClient, (char*)&tLogoutRes + sizeof(THeader), sizeof(TLogoutRes) - sizeof(THeader), 0);
				printf("收到登出回应: %d\n", tLogoutRes.res);
				//closesocket(sClient);
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
			}
			std::cout << "客户端退出！" << std::endl;
			return -1;
		}
	}
	return 0;
};

void HandleInput(SOCKET nLocalSocket)
{
	char input[128] = {};
	while (true)
	{
		scanf_s("%s", input, 128);

		//if (0 == strcmp("connect", input))
		//{
		//	nLocalSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//	if (nLocalSocket != INVALID_SOCKET)
		//	{
		//		std::cout << "|***********启动客户端***********|\n" << std::endl;
		//	}
		//	else
		//	{
		//		std::cout << "客户端sockset创建失败!" << std::endl;
		//		continue;
		//	}
		//	sockaddr_in nServeraddr;
		//	memset(&nServeraddr, 0, sizeof(nServeraddr));
		//	nServeraddr.sin_family = AF_INET;
		//	inet_pton(AF_INET, MYSERVERIP, (void *)&nServeraddr.sin_addr);
		//	//nServeraddr.sin_addr.s_addr = inet_addr(MYSERVERIP);
		//	nServeraddr.sin_port = htons(MYPROT);
		//	int nRet = connect(nLocalSocket, (sockaddr*)&nServeraddr, sizeof(nServeraddr));//成功返回0。否则返回SOCKET_ERROR
		//	if (nRet == SOCKET_ERROR)
		//	{
		//		std::cout << "服务器连接失败！" << std::endl;
		//	}
		//	else
		//	{
		//		printf("连接成功!\n");
		//	}
		//	continue;
		//}
		//else 
		if (0 == strcmp("login", input))
		{
			char achUserName[64] = {};
			char achPassWord[64] = {};
			printf("请输入用户名:\n");
			scanf_s("%s", achUserName, 64);
			printf("请输入密码:\n");
			scanf_s("%s", achPassWord, 64);
			TLogin* ptLogin = new TLogin();
			strcpy_s(ptLogin->achUserName, achUserName);
			strcpy_s(ptLogin->achPassWord, achPassWord);
			send(nLocalSocket, (const char*)ptLogin, sizeof(TLogin), 0);
		}
		else if (0 == strcmp("logout", input))
		{
			TLogout* ptLogout = new TLogout();
			send(nLocalSocket, (const char*)ptLogout, sizeof(TLogout), 0);
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
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Socket版本加载失败\n" << std::endl;
	}

	SOCKET nLocalSocket;
	nLocalSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (nLocalSocket != INVALID_SOCKET)
	{
		std::cout << "|***********启动客户端***********|\n" << std::endl;
	}
	else
	{
		std::cout << "客户端sockset创建失败!\n" << std::endl;
		return -1;
	}

	sockaddr_in nServeraddr;
	memset(&nServeraddr, 0, sizeof(nServeraddr));
	nServeraddr.sin_family = AF_INET;
	//inet_pton(AF_INET, MYSERVERIP, (void *)&nServeraddr.sin_addr);
	nServeraddr.sin_addr.s_addr = inet_addr(MYSERVERIP);
	nServeraddr.sin_port = htons(MYPROT);
	int nRet = connect(nLocalSocket, (sockaddr*)&nServeraddr, sizeof(nServeraddr));//成功返回0。否则返回SOCKET_ERROR
	if (nRet == SOCKET_ERROR)
	{
		std::cout << "连接服务器失败!\n" << std::endl;
	}
	else
	{
		printf("连接服务器成功!\n");
	}

	std::thread t(HandleInput, nLocalSocket);

	int ndfs = nLocalSocket + 1;
	fd_set fdRead;
	fd_set fdWrite;
	fd_set fdExp;
	timeval timeout = { 2,0 };
	while (true)
	{
		FD_ZERO(&fdRead);
		FD_ZERO(&fdWrite);
		FD_ZERO(&fdExp);

		FD_SET(nLocalSocket, &fdRead);

		int ret = select(ndfs, &fdRead, &fdWrite, &fdExp, &timeout);
		if ( ret < 0 )
		{
			break;
		}

		if ( FD_ISSET(nLocalSocket,&fdRead) )
		{
			HandleSocket(nLocalSocket);
		}		
	}

	closesocket(nLocalSocket);
	t.join();

	WSACleanup(); 
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
