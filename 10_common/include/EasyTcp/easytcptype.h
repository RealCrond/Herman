/********************************************************************************//*
*@file          easytcptype.h
*@brief         简易版TCP通信客户端
*
*@author        Herman
*@version       1.5
*@date          20200604
*@copyright     (c)1995-2020 Suzhou Keda Technology Co.,Ltd. All rights reserved
***********************************************************************************/
#pragma once

#define MYSERVERIP	"127.0.0.1"
#define MYPROT	4567

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
