/*************



**************/
#include "stdafx.h"
#include "mainwnd.h"


DUI_BEGIN_MESSAGE_MAP(CMainwnd, WindowImplBase)
	DUI_ON_MSGTYPE_CTRNAME(DUI_MSGTYPE_CLICK, _T("closebtn"), OnClose)
	DUI_ON_MSGTYPE_CTRNAME(DUI_MSGTYPE_SELECTCHANGED, _T(""), OnOptionSelectChange)
	//DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMCLICK, OnItemClick)
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
	m_pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("message_list")));
	//m_pList->SetItemHLineSize(1);
	//m_pList->SetItemHLineColor(0xFFFFFFFF);

	CEditUI* pEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("search")));
	pEdit->SetToolTip(_T("��������Ҫ����������!"));

	int nWidth = 150;
	int nHeight = 50;
	SIZE borderround;
	borderround.cx = 5;
	borderround.cy = 5;
	CListContainerElementUI* pListChatElemTime = new CListContainerElementUI();
	pListChatElemTime->SetMinWidth(nWidth);
	pListChatElemTime->SetMinHeight(nHeight - 14);
	CLabelUI* pLabelTime = new CLabelUI();
	pLabelTime->SetAttribute(_T("align"), _T("center"));
	pLabelTime->SetText(_T("2020-04-18 15:41"));
	pLabelTime->SetFixedHeight(nHeight);
	pListChatElemTime->Add(pLabelTime);
	pListChatElemTime->SetEnabled(FALSE);
	pListChatElemTime->SetBkColor(0xFFF2F3F5);
	m_pList->Add(pListChatElemTime);
	for (size_t i = 0; i < 5; i++)
	{
		CLabelUI* pFriendProfile = new CLabelUI();
		pFriendProfile->SetFixedWidth(50);
		pFriendProfile->SetFixedHeight(50);
		pFriendProfile->SetBorderRound(borderround);
		pFriendProfile->SetAttribute(_T("align"), _T("center"));
		//pFriendProfile->SetBkColor(0xFF00FF00);
		CVerticalLayoutUI* pMessageLayout = new CVerticalLayoutUI();
		CLabelUI* pMessage = new CLabelUI();
		pMessage->SetText(_T("�յ�һ����Ϣ��"));
		pMessage->SetFixedWidth(pMessage->GetText().GetLength() * 18);
		pMessage->SetFixedHeight(30);
		pMessage->SetAttribute(_T("bordersize"), _T("1"));
		pMessage->SetBkColor(0xFFCCE4FC);
		pMessage->SetBorderRound(borderround);
		CControlUI* pCtrlUITop = new CControlUI();
		pMessageLayout->Add(pCtrlUITop);
		pMessageLayout->Add(pMessage);
		CControlUI* pCtrlUIBot = new CControlUI();
		pMessageLayout->Add(pCtrlUIBot);
		//pMessageLayout->SetBkColor(0xFFFF0000);
		pMessageLayout->SetFixedWidth(pMessage->GetFixedWidth());
		CHorizontalLayoutUI* pHLayout = new CHorizontalLayoutUI();
		pHLayout->SetMinWidth(nWidth);
		pHLayout->SetMinHeight(nHeight);
		if (rand() % 2)
		{
			//pFriendProfile->SetText(_T("Me"));
			pFriendProfile->SetAttribute(_T(""), _T(""));    //ɸѡ-hover.png 54*54 normalimage="file='image\number\�½���ϵ��.png' source='0,0,54,54' dest='0,0,50,50' "
			//pFriendProfile->SetBkImage(_T("file=\'image\number\ɸѡ-hover.png\' source=\'0,0,54,54\' dest=\'0,0,50,50\'"));
			pFriendProfile->SetAttribute(_T("bkimage"), _T("file='image\\number\\ɸѡ-hover.png' source='0,0,54,54' dest='5,5,45,45' "));
			pMessage->SetAttribute(_T("align"), _T("right"));
			pMessage->SetText(_T("�ҷ�����һ����Ϣ��"));
			CControlUI* pCtrlUI = new CControlUI();
			pHLayout->Add(pCtrlUI);
			pHLayout->Add(pMessageLayout);
			pHLayout->Add(pFriendProfile);
		}
		else
		{
			//pFriendProfile->SetText(_T("Friend"));
			pFriendProfile->SetAttribute(_T("bkimage"), _T("file='image\\number\\ɸѡ-down.png' source='0,0,54,54' dest='5,5,45,45' "));
			pMessage->SetAttribute(_T("align"), _T("left"));
			pHLayout->Add(pFriendProfile);
			pHLayout->Add(pMessageLayout);
		}

		CListContainerElementUI* pListItem = new CListContainerElementUI();
		pListItem->SetMinWidth(nWidth);
		pListItem->SetMinHeight(nHeight);
		pListItem->Add(pHLayout);
		pListItem->SetEnabled(FALSE);
		pListItem->SetBkColor(0xFFF2F3F5);
		m_pList->Add(pListItem);
	}

	m_pTabLayout = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_main")));	

	CEditUI* pEditAlias = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("alias")));
	pEditAlias->SetText(_T("Ⱥ�������-��Ѷ��Ʒ��"));
	pEditAlias->SetAutoSelAll(true);
	pEditAlias->SetAttribute(_T("font"), _T("3"));
	pEditAlias->SetAttribute(_T("enabled"), _T("false"));
	pEditAlias->SetAttribute(_T("align"), _T("center"));
	//pEditAlias->SetAttribute(_T("textpadding"), _T("15,0,15,0"));
	pEditAlias->SetFixedWidth(pEditAlias->GetText().GetLength() * 18);

	CListUI* pListChat = static_cast<CListUI*>(m_PaintManager.FindControl(_T("chatlist")));
	for (size_t i = 0; i < 20; i++)
	{
		CListContainerElementContact* pListChatElem1 = new CListContainerElementContact();
		pListChatElem1->SetMinWidth(nWidth);
		pListChatElem1->SetMinHeight(nHeight + 14);
		//pListElem->SetFixedWidth(nWidth);
		//pListElem->SetFixedHeight(nHeight);
		CDuiString name;
		name.Format(_T("chatlistitem%d"), i + 1);
		CDuiString message;
		message.Format(_T("%d����һ��������ʷ��Ϣ��¼!"), i + 1);
		CDuiString time;
		time.Format(_T("time%d"), i + 1);

		pListChatElem1->Select( i%2 );
		pListChatElem1->SetName( name );
		pListChatElem1->InitContainer(name, message, time);
		pListChatElem1->SetToolTip(_T("����һ����ʾ"));
		pListChat->Add(pListChatElem1);
	}

	CLabelUI* plabelEmail = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("email")));
	plabelEmail->SetText(_T("liuhuan@kedacom.com"));
	plabelEmail->SetFixedWidth(plabelEmail->GetText().GetLength() * 7);

	CLabelUI* plabelDep = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("department")));
	plabelDep->SetFixedWidth(plabelDep->GetText().GetLength() * 18);
}

/********  �ؼ���Ϣ��Ӧ����  *******/
void CMainwnd::OnClose(TNotifyUI& msg)
{
	Close();
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

/*******  �Զ�����Ϣ��Ӧ����  ********/
LRESULT	CMainwnd::OnTestInd(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::MessageBox(NULL, _T("alert! �����յ�һ���û��Զ�����Ϣ!"), _T("Duilib Demo"), MB_OK);
	//m_pTabLayout->SelectItem(2);
	return 0;
}