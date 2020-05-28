// SocketServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#endif // WIN32

//using namespace std; 不能使用，否则会出错

#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

//using namespace std;

#define MYSERVERIP	"127.0.0.1"
#define MYPROT	2500


void HandleClient(SOCKET sClient)
{
	std::cout << "有客户端连接: " << std::endl;
	char mess[] = "/*********** Welcome ************\r\n";
	char buff[256] = { 0 };
	char achTitle[] = "Titile->";

	send(sClient, mess, sizeof(mess), 0);//发送消息给客户端
	send(sClient, achTitle, sizeof(achTitle), 0);//发送消息给客户端
	while (sClient != 0)
	{
		// 从客户端接收数据
		memset(buff, 0, 256);
		int nRecv = recv(sClient, buff, 256, 0);//从客户端接受消息
		if (!strcmp(buff, "\r\n"))
		{
			std::cout << "回车。。。" << std::endl;
			send(sClient, achTitle, sizeof(achTitle), 0);
			continue;
		}
		if (!strcmp(buff, "bye"))
		{
			closesocket(sClient);
			return;
		}
		if (nRecv > 0)
		{
			std::cout << buff << std::endl;
			char mess[] = "server:收到了你的消息，欢迎使用!\r\n";
			send(sClient, mess, sizeof(mess), 0);
			//closesocket(sClient);
			//sClient = 0;
		}
		else
		{
			std::cout << "客户端退出" << std::endl;
			return;
		}
	}
};

int main()
{
    std::cout << "Hello World!\n";
	SOCKET nServerSocket; //绑定本地地址和端口号的套接口

	WSADATA wsaData;
	if ( WSAStartup(MAKEWORD(2,2), &wsaData) != 0  )
	{
		std::cout << "Socket版本错误!" << std::endl;
	}


	nServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	sockaddr_in Serveraddr;
	memset(&Serveraddr, 0, sizeof(sockaddr_in*));
	Serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, MYSERVERIP, (void *)&Serveraddr.sin_addr);
	//Serveraddr.sin_addr.s_addr = inet_addr(MYSERVERIP);
	Serveraddr.sin_port = htons(MYPROT);
	int nRet = bind(nServerSocket, (sockaddr *)&Serveraddr, sizeof(Serveraddr));


	nRet = listen(nServerSocket, 5);


	SOCKET sClient = 0;
	sockaddr_in nClientSocket;
	int nSizeClient = sizeof(nClientSocket);
	char buff[256] = { 0 };
	char achTitle[] = "Titile->";
	while (nServerSocket != -1)
	{
		sClient = accept(nServerSocket, (sockaddr*)&nClientSocket, &nSizeClient);//接受客户端连接，阻塞状态;失败返回-1
		if (sClient == SOCKET_ERROR)
		{
			std::cout << "accept连接失败" << std::endl;
			return 0;
		}

		std::thread* pth = new std::thread(HandleClient, sClient);
		pth->detach();
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
