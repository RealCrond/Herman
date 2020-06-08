
/********************************************************************************//*
*@file          CEasyTcpServer.h
*@brief         ���װ�TCPͨ�ŷ�����
*
*@author        Herman
*@version       1.5
*@date          20200604
*@copyright     (c)1995-2020 Suzhou Keda Technology Co.,Ltd. All rights reserved
***********************************************************************************/
#include "CEasyTcpServer.h"

CEasyTcpServer::CEasyTcpServer() 
{
	m_scServer = INVALID_SOCKET;
	m_vcScClient.clear();
}

CEasyTcpServer::~CEasyTcpServer()
{

}

int CEasyTcpServer::Init()
{
#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Socket�汾����ʧ��\n");
	}
#endif // _WIN32

	m_scServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_scServer)
	{
		printf("��ʼ��ʧ��!\n");
	}
	else
	{
		printf("��ʼ���ɹ�!\n");
	}

	return 0;
}

int CEasyTcpServer::Bind(const char* addr_ip, unsigned short addr_port)
{
	sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	if (addr_ip)
	{
		addr_in.sin_addr.s_addr = inet_addr(addr_ip);
	}
	else
	{
		addr_in.sin_addr.s_addr = ADDR_ANY;
	}
	addr_in.sin_port = htons(addr_port);

	return bind(m_scServer, (const sockaddr*)&addr_in, sizeof(sockaddr));
}

int CEasyTcpServer::Listen(int backLog)
{
	int ret = listen(m_scServer, backLog);
	if (ret == SOCKET_ERROR )
	{
		printf("�����˿ڰ�ʧ��!");
	}
	return ret;
}

SOCKET CEasyTcpServer::GetServerSocket() const
{
	return m_scServer;
}

int CEasyTcpServer::Accpet()
{
	sockaddr_in addr;
	int len = sizeof(sockaddr);
	SOCKET scClient = accept(m_scServer, (sockaddr*)&addr, &len);
	//printf("�пͻ���<%d>����!\n", scClient);
	if ( scClient != INVALID_SOCKET )
	{
		printf("�пͻ���<%d>����!\n", scClient);
		m_vcScClient.push_back(scClient);
	}
	for (size_t i = 0; i < m_vcScClient.size(); i++)
	{
		TLoginResult* ptLoginResult = new TLoginResult();
		send(m_vcScClient[i], (const char*)ptLoginResult, sizeof(TLoginResult), 0);
	}
	return 0;
}

int CEasyTcpServer::RecvData()
{
	fd_set fdRead;
	fd_set fdWrite;
	fd_set fdExp;
	FD_ZERO(&fdRead);
	FD_ZERO(&fdWrite);
	FD_ZERO(&fdExp);

	FD_SET(m_scServer, &fdRead);
	for ( auto iter = m_vcScClient.begin(); iter != m_vcScClient.end(); iter++ )
	{
		FD_SET(*iter, &fdRead);
	}

	int maxSc = m_scServer;
	timeval timeout = { 1,0 };
	int recv = select(maxSc + 1, &fdRead, &fdWrite, &fdExp, NULL);
	if (recv<0)
	{
		return -1;
	}
	if ( FD_ISSET(m_scServer,&fdRead) )
	{
		FD_CLR(m_scServer, &fdRead);
		Accpet();
	}
	for (unsigned int index = 0; index < m_vcScClient.size(); index++)
	{
		if ( FD_ISSET(m_vcScClient[index],&fdRead) )
		{
			if ( -1 == OnNetMsg(m_vcScClient[index]) )
			{
				auto itr = std::find(m_vcScClient.begin(), m_vcScClient.end(), m_vcScClient[index]);
				m_vcScClient.erase(itr);
			}
		}
	}

	return 0;
}

int CEasyTcpServer::SendData(SOCKET sc, const char* data, int len, int flags)
{
	return send(sc, data, len, flags);
}

int CEasyTcpServer::OnNetMsg(SOCKET sc)
{
	char recvBuff[1024];
	int ret = recv(sc, recvBuff, sizeof(recvBuff), 0);
	if (ret > 0)
	{
		THeader* header = (THeader*)recvBuff;
		switch (header->emEvent)
		{
			case emLoginReq:
			{
				printf("�յ���¼����!\n");
				TLoginResult* ptLoginRes = new TLoginResult();
				send(sc, (const char*)ptLoginRes, sizeof(TLoginResult), 0);
			}
			break;
			case emQuitCmd:
			{
				printf("�յ��˳�����!\n");
				TLogoutRes* ptLogoutRes = new TLogoutRes();
				send(sc, (const char*)ptLogoutRes, sizeof(TLogoutRes), 0);
			}
			break;
			default:
				break;
		}
	}
	else
	{
		//�⼸�ִ����룬��Ϊ�����������ģ���������
		if ((ret < 0) && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
		{
			return 0;
		}
		printf("�ͻ���<%d>�˳���\n", sc);
		return -1;
	}


	return 0;
}

int CEasyTcpServer::Close()
{
#ifdef _WIN32
	closesocket(m_scServer);
	for (auto iter = m_vcScClient.begin(); iter != m_vcScClient.end(); iter++)
	{
		closesocket(*iter);
	}
	WSACleanup();
#else
	close(m_scServer);
	for (auto iter = m_vcScClient.begin(); iter != m_vcScClient.end(); iter++)
	{
		close(*iter);
	}
#endif // _WIN32

	return 0;
}