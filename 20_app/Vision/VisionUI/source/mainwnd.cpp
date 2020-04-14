#include "stdafx.h"
#include "mainwnd.h"


DUI_BEGIN_MESSAGE_MAP(CMainwnd, WindowImplBase)
	DUI_ON_CLICK_CTRNAME(_T("closebtn"), OnClose)
	//DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
	//DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED, OnSelectChanged)
	//DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMCLICK, OnItemClick)
DUI_END_MESSAGE_MAP()

DUI_BEGIN_CUSTOM_MESSAGE_MAP(CMainwnd)
	PMSG_FUN(WM_USER + 100, OnTestInd)
DUI_END_CUSTOM_MESSAGE_MAP()

CMainwnd::CMainwnd()
{

}

CMainwnd::~CMainwnd()
{

}

void CMainwnd::OnClose(TNotifyUI& msg)
{
	PostQuitMessage(0);
}



LRESULT	CMainwnd::OnTestInd(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::MessageBox(NULL, _T("alert!"), _T("Duilib Demo"), MB_OK);
	return 0;
}