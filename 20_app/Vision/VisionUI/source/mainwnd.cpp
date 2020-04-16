/*************



**************/
#include "stdafx.h"
#include "mainwnd.h"


DUI_BEGIN_MESSAGE_MAP(CMainwnd, WindowImplBase)
	DUI_ON_MSGTYPE_CTRNAME(DUI_MSGTYPE_CLICK, _T("closebtn"), OnClose)
	DUI_ON_MSGTYPE_CTRNAME(DUI_MSGTYPE_SELECTCHANGED, _T(""), OnOptionSelectChange)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMCLICK, OnItemClick)
DUI_END_MESSAGE_MAP()


DUI_BEGIN_CUSTOM_MESSAGE_MAP(CMainwnd)
	PMSG_FUN(WM_USER + 100, OnTestInd)
DUI_END_CUSTOM_MESSAGE_MAP()


CMainwnd::CMainwnd()
{
	m_Page1.SetPaintMagager(&m_PaintManager);
	m_Page2.SetPaintMagager(&m_PaintManager);

	AddVirtualWnd(_T("page1"), &m_Page1);
	AddVirtualWnd(_T("page2"), &m_Page2);
}

CMainwnd::~CMainwnd()
{
	RemoveVirtualWnd(_T("page1"));
	RemoveVirtualWnd(_T("page2"));
}

CControlUI* CMainwnd::CreateControl(LPCTSTR pstrClass) {
	if (_tcscmp(pstrClass, _T("ComputerExamine")) == 0)
	{
		return new ComputerExamineUI();
	}	
	else if (_tcscmp(pstrClass, _T("ListContainerElementEx")) == 0)
	{
		return new CListContainerElementEx();
	}
	return NULL;
};

void CMainwnd::InitWindow()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("closebtn")));
	m_pMaxBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("maxbtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("minbtn")));
	m_pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("down_list_tab")));
	//ComputerExamineUI x;
	//CListContainerElementEx ListElem;
	int nWidth = 150;
	int nHeight = 50;
	CListContainerElementEx* pListElem = new CListContainerElementEx();
	pListElem->SetBorderSize(2);
	pListElem->SetBorderColor(0xFF00ff00);
	pListElem->SetText(_T("1111"));
	pListElem->SetToolTip(_T("22222"));
	pListElem->SetMinWidth(nWidth);
	pListElem->SetMinHeight(nHeight);
	//pListElem->SetFixedWidth(nWidth);
	//pListElem->SetFixedHeight(nHeight);
	pListElem->SetName(_T("item1"));
	pListElem->GetIndex();
	pListElem->SetToolTip(_T("这是一条提示"));
	m_pList->Add(pListElem);

	CListContainerElementEx* pListElem2 = new CListContainerElementEx();
	pListElem2->SetMinWidth(nWidth);
	pListElem2->SetMinHeight(nHeight);
	pListElem2->SetName(_T("item2"));
	m_pList->Add(pListElem2);

	CListContainerElementEx* pListElem3 = new CListContainerElementEx();
	pListElem3->SetMinWidth(nWidth);
	pListElem3->SetMinHeight(nHeight);
	pListElem3->SetName(_T("item3"));
	m_pList->Add(pListElem3);

	CListContainerElementEx* pListElem4 = new CListContainerElementEx();
	pListElem4->SetMinWidth(nWidth);
	pListElem4->SetMinHeight(nHeight);
	pListElem4->SetName(_T("item4"));
	m_pList->Add(pListElem4);


	CListContainerElementEx* pListElem5 = new CListContainerElementEx();
	pListElem5->SetMinWidth(nWidth);
	pListElem5->SetMinHeight(nHeight);
	pListElem5->SetName(_T("item5"));
	m_pList->Add(pListElem5);

	
	m_pTabLayout = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_main")));	
}

/********  控件消息响应函数  *******/
void CMainwnd::OnClose(TNotifyUI& msg)
{
	PostQuitMessage(0);
}

void CMainwnd::OnOptionSelectChange(TNotifyUI &msg)
{
	//::MessageBox(NULL, _T("OnOptionSelectChange!"), _T("Duilib Demo"), MB_OK);	
	m_pTabLayout->SelectItem(rand() % 3);
}

void CMainwnd::OnItemClick(TNotifyUI &msg)
{
	::MessageBox(NULL, _T("CMainwnd::OnItemClick!"), _T("Duilib Demo"), MB_OK);
}

/*******  自定义消息响应函数  ********/
LRESULT	CMainwnd::OnTestInd(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::MessageBox(NULL, _T("alert! 测试收到一条用户自定义消息!"), _T("Duilib Demo"), MB_OK);
	//m_pTabLayout->SelectItem(2);
	return 0;
}