// SocketClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#if WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#endif // WIN32


#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

using namespace std;

#define MYSERVERIP	"127.0.0.1"
#define MYPROT	16000

int main()
{
	std::cout << "Hello World!\n";

	SOCKET nLocalSocket;
	char message[100];

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		std::cout << "Socket版本加载失败" << std::endl;


	nLocalSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ( nLocalSocket != INVALID_SOCKET )
	{
		cout << "客户端socket创建成功!" << endl;
	}
	else
	{
		cout << "客户端sockset创建失败!" << endl;
		return 0;
	}

	sockaddr_in nServeraddr;
	memset(&nServeraddr, 0, sizeof(nServeraddr));
	nServeraddr.sin_family = AF_INET;
	inet_pton(AF_INET, MYSERVERIP, (void *)&nServeraddr.sin_addr);
	//nServeraddr.sin_addr.s_addr = inet_addr(MYSERVERIP);
	nServeraddr.sin_port = htons(MYPROT);
	int nRet = connect(nLocalSocket, (sockaddr*)&nServeraddr, sizeof(nServeraddr));//成功返回0。否则返回SOCKET_ERROR

	if (nRet == SOCKET_ERROR)
	{
		cout << "服务器连接失败！" << endl;
		return false;
	}

	int resultRecv = -1;
	while (true)
	{
		resultRecv = recv(nLocalSocket, message, sizeof(message), 0);
		if (resultRecv > 0)
		{
			//输出消息
			cout << message << endl;
			memset(message, '\0', sizeof(message));
			
			char buffer5[100] = "client:客户端连接测试成功！";
			send(nLocalSocket, buffer5, sizeof(buffer5), 0);
		}
		else
		{
			//这几种错误码，认为连接是正常的，继续接收
			if ((resultRecv < 0) && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
			{
				continue;//继续接收数据
			}
			cout << "与服务器连接中断！" << endl;
			break;//跳出接收循环
		}
	}

	char ch = getchar();
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
