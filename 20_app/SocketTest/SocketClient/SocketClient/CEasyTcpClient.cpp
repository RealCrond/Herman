/********************************************************************************//*
*@file          CEasyTcpClient.cpp
*@brief         ���װ�TCPͨ�ſͻ���
*
*@author        Herman
*@version       1.5
*@date          20200604
*@copyright     (c)1995-2020 Suzhou Keda Technology Co.,Ltd. All rights reserved
***********************************************************************************/

#include "CEasyTcpClient.h"

CEasyTcpClient::CEasyTcpClient()
{
#ifdef  _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Socket�汾����ʧ��\n");
	}
#endif //  _WIN32

	m_scClient = INVALID_SOCKET;
}

CEasyTcpClient::~CEasyTcpClient()
{

}

int CEasyTcpClient::Init()
{
	m_scClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_scClient)
	{
		printf("��ʼ��ʧ��!\n");
	}
	else
	{
		printf("��ʼ��socket<%d>�ɹ�!\n", m_scClient);
	}
	return m_scClient;
}

int CEasyTcpClient::Connect(const char* addr_ip,unsigned short addr_port)
{
	sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.s_addr = inet_addr(addr_ip);
	addr_in.sin_port = htons(addr_port);
	int length = sizeof(sockaddr_in);
	return connect(m_scClient, (const sockaddr*)&addr_in, length);
}

int CEasyTcpClient::RecvData()
{
	fd_set fdRead;
	fd_set fdWrite;
	fd_set fdExp;

	FD_ZERO(&fdRead);
	FD_ZERO(&fdWrite);
	FD_ZERO(&fdExp);

	FD_SET(m_scClient, &fdRead);

	int maxSc = m_scClient;
	timeval timeout = {1,0};
	int ret = select(maxSc + 1, &fdRead, &fdWrite, &fdExp, &timeout);
	if ( ret < 0)
	{
		printf("��������Ͽ���!\n");
		return -1;
	}

	if ( FD_ISSET(m_scClient,&fdRead) )
	{
		char recvBuff[1024];
		int ret = recv(m_scClient, recvBuff, sizeof(recvBuff), 0);
		if (ret > 0)
		{
			if (-1 == OnNetMsg(m_scClient, recvBuff))
			{
				printf("�Ͽ�!\n");
				return -1;
			}
		}
		else
		{
			//�⼸�ִ����룬��Ϊ�����������ģ���������
			if ((ret < 0) && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
			{
				return 0;
			}
			printf("<%d>�Ͽ���\n", m_scClient);
			return -1;
		}
	}

	return 0;
}

int CEasyTcpClient::SendData(SOCKET sc, const char* data, int len, int flags)
{
	return send(sc, data, len, flags);
}

int CEasyTcpClient::OnNetMsg(SOCKET sc,char* recvBuff)
{

	THeader* header = (THeader*)recvBuff;
	switch (header->emEvent)
	{
	case emLoginRsp:
	{
		TLoginResult tLoginRes;
		//recv(sc, (char*)&tLoginRes + sizeof(THeader), sizeof(TLoginResult) - sizeof(THeader), 0);
		printf("�յ���¼��Ӧ (emLoginRsp) : %d\n", tLoginRes.result);
	}
	break;
	case emQuitInd:
	{
		TLogoutRes* ptLogoutRes = (TLogoutRes*)recvBuff;
		printf("[emQuitInd][%d][%s]\n", ptLogoutRes->res, ptLogoutRes->data);
		//recv(sc, (char*)&tLogoutRes + sizeof(THeader), sizeof(TLogoutRes) - sizeof(THeader), 0);
		//printf("�յ��ǳ���Ӧ (emQuitInd) : %d\n", tLogoutRes.res);
	}
	break;
	default:
		printf("�յ�δ֪��Ϣ!\n");
		break;
	}

	return 0;
}

SOCKET CEasyTcpClient::GetClientSocket() const
{
	return m_scClient;
}