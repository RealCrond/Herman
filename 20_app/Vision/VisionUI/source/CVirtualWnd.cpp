
#include "stdafx.h"
#include "CVirtualWnd.h"

//虚拟窗口为page1的List控件及其子控件，他们的消息处理都在这里
DUI_BEGIN_MESSAGE_MAP(CVirtualWndPage1, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)			//page1里的click消息会被拦截，mainwnd就收不到了
	DUI_ON_MSGTYPE_CTRNAME(DUI_MSGTYPE_CLICK,_T("open"), OnClick)
	DUI_ON_MSGTYPE_CTRNAME(DUI_MSGTYPE_CLICK, _T("folder"), OnClick)
	DUI_ON_MSGTYPE_CTRNAME(DUI_MSGTYPE_RETURN, _T("messageinput"), OnSendMessage)
	DUI_ON_MSGTYPE_CTRNAME(DUI_MSGTYPE_CLICK,_T("send"),OnSend)
	//DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED, OnSelectChanged)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_RETURN, OnSendMessage)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMCLICK, OnItemClick)   //这个会拦截mainwnd的itemclick消息
	DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMDBCLICK, OnItemDbClick)   //这个会拦截mainwnd的itemclick消息
	//DUI_ON_MSGTYPE(DUI_MSGTYPE_MENU, OnMenu)
DUI_END_MESSAGE_MAP()

CVirtualWndPage1::CVirtualWndPage1()
{
}

void CVirtualWndPage1::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
	m_pPaintManager = pPaintMgr;
}

void CVirtualWndPage1::OnClick(TNotifyUI& msg)
{
	if (msg.pSender->GetName() == _T("down_ico"))
	{
		CControlUI *find_ctrl = m_pPaintManager->FindSubControlByName(msg.pSender->GetParent()->GetParent(), _T("down_name"));

		if (find_ctrl)
		{
			MessageBox(NULL,
				find_ctrl->GetText() + _T(" 演示未选中行中的按钮触发动作，依该按钮父结点的找到所属行listcontainer.."),
				_T("DUILIB DEMO"), MB_OK);
			((CLabelUI *)find_ctrl)->SetText(_T("由程序动态设置后的名称..."));
		}
	}
	else if (msg.pSender->GetName() == _T("open"))
	{
		CListUI* m_pList = static_cast<CListUI*>(m_pPaintManager->FindControl(_T("down_list_tab")));
		CListContainerElementEx* pItem = (CListContainerElementEx*)(msg.pSender->GetParent()->GetParent()->GetParent()->GetParent());
		index = pItem->GetIndex();
		::MessageBox(NULL, msg.pSender->GetParent()->GetParent()->GetParent()->GetParent()->GetName() + _T("  Open?"), _T("Duilib Demo Open"), MB_OK);
	}
	else if (msg.pSender->GetName() == _T("folder"))
	{
		CListUI* m_pList = static_cast<CListUI*>(m_pPaintManager->FindControl(_T("down_list_tab")));
		CListContainerElementEx* pItem = (CListContainerElementEx*)(msg.pSender->GetParent()->GetParent()->GetParent()->GetParent());
		index = pItem->GetIndex();
		::MessageBox(NULL, msg.pSender->GetParent()->GetParent()->GetParent()->GetParent()->GetName() + _T("  folder?"), _T("Duilib Demo Open"), MB_OK);
	}
	else if (msg.pSender->GetName() == _T("down_del"))
	{
		CListUI *down_list =
			static_cast<CListUI*>(m_pPaintManager->FindControl(_T("down_list_tab")));
		if (!down_list)
			return;

		down_list->RemoveAt(down_list->GetCurSel());
	}
	else if (msg.pSender->GetName() == _T("down_new"))
	{
		CListUI *down_list = static_cast<CListUI*>(m_pPaintManager->FindControl(_T("down_list_tab")));
		if (!down_list)
			return;

		CListContainerElementUI *new_node = new CListContainerElementUI;
		new_node->SetAttributeList(_T("height=\"45\""));

		CHorizontalLayoutUI *new_h_lay = new CHorizontalLayoutUI;
		new_h_lay->SetAttributeList(_T("float=\"false\" ")\
			_T("childpadding=\"10\" inset=\"3,5,3,5\""));

		CButtonUI *new_btn_1 = new CButtonUI;
		new_btn_1->SetAttributeList(
			_T("name=\"down_ico\" float=\"false\" ")\
			_T("bordersize=\"0\" width=\"32\" maxheight=\"26\" ")\
			_T("bkimage=\"downlist_app.png\" ")\
			_T("normalimage=\"file='downlist_run.png' dest='20,14,32,26'\""));

		CVerticalLayoutUI *new_v_lay = new CVerticalLayoutUI;
		new_h_lay->Add(new_btn_1);
		new_h_lay->Add(new_v_lay);

		CLabelUI *new_label = new CLabelUI;
		new_label->SetAttributeList(_T("textcolor=\"#FFAAAAAA\" showhtml=\"true\""));
		new_label->SetText(_T("new added item.exe"));
		new_label->SetName(_T("down_name"));
		CProgressUI *new_progress = new CProgressUI;
		new_progress->SetMinValue(0);
		new_progress->SetMaxValue(100);
		new_progress->SetValue(1);
		new_progress->SetMaxWidth(200);
		new_progress->SetMaxHeight(7);
		new_progress->SetForeImage(_T("progress_fore.png"));
		new_progress->SetName(_T("down_progress"));
		new_v_lay->Add(new_label);
		new_v_lay->Add(new_progress);

		CLabelUI *new_label2 = new CLabelUI;
		CLabelUI *new_label3 = new CLabelUI;
		CVerticalLayoutUI *new_v_lay2 = new CVerticalLayoutUI;
		new_h_lay->Add(new_v_lay2);
		new_v_lay2->Add(new_label2);
		new_v_lay2->Add(new_label3);
		new_label2->SetAttributeList(
			_T("align=\"right\" text=\"\" textcolor=\"#FFAAAAAA\" showhtml=\"true\""));
		new_label3->SetAttributeList(
			_T("align=\"right\" text=\"0.00K/34.33M \" textcolor=\"#FFAAAAAA\" showhtml=\"true\""));

		new_node->Add(new_h_lay);
		down_list->Add(new_node);
	}
}

void CVirtualWndPage1::OnSelectChanged(TNotifyUI &msg)
{

}

void CVirtualWndPage1::OnItemClick(TNotifyUI &msg)
{
	::MessageBox(NULL, _T("OnItemClick!"), _T("Duilib Demo"), MB_OK);
}

void CVirtualWndPage1::OnItemDbClick(TNotifyUI &msg)
{
	::MessageBox(NULL, _T("OnItemDbClick!"), _T("Duilib Demo"), MB_OK);
	return;
}

void CVirtualWndPage1::OnSendMessage(TNotifyUI &msg)
{
	::MessageBox(NULL, _T("Send Message!"), _T("Duilib Demo"), MB_OK);
	return;
}

void CVirtualWndPage1::OnSend(TNotifyUI &msg)
{

	CListUI* pList = static_cast<CListUI*>(m_pPaintManager->FindControl(_T("message_list")));

	int nWidth = 150;
	int nHeight = 50;
	SIZE borderround;
	borderround.cx = 5;
	borderround.cy = 5;
	CLabelUI* pFriendProfile = new CLabelUI();
	pFriendProfile->SetFixedWidth(50);
	pFriendProfile->SetFixedHeight(50);
	pFriendProfile->SetBorderRound(borderround);
	pFriendProfile->SetAttribute(_T("align"), _T("center"));
	pFriendProfile->SetAttribute(_T(""), _T(""));    //筛选-hover.png 54*54 normalimage="file='image\number\新建联系人.png' source='0,0,54,54' dest='0,0,50,50' "
	pFriendProfile->SetAttribute(_T("bkimage"), _T("file='image\\number\\筛选-hover.png' source='0,0,54,54' dest='5,5,45,45' "));
	CVerticalLayoutUI* pMessageLayout = new CVerticalLayoutUI();
	CLabelUI* pMessage = new CLabelUI();
	CRichEditUI* pEdit = static_cast<CRichEditUI*>(m_pPaintManager->FindControl(_T("messageinput")));
	pMessage->SetText(pEdit->GetText());
	pMessage->SetFixedWidth(pMessage->GetText().GetLength() * 18);
	pMessage->SetFixedHeight(30);
	pMessage->SetAttribute(_T("bordersize"), _T("1"));
	pMessage->SetBkColor(0xFFCCE4FC);
	pMessage->SetBorderRound(borderround);
	pMessage->SetAttribute(_T("align"), _T("right"));
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

	CControlUI* pCtrlUI = new CControlUI();
	pHLayout->Add(pCtrlUI);
	pHLayout->Add(pMessageLayout);
	pHLayout->Add(pFriendProfile);

	CListContainerElementUI* pListItem = new CListContainerElementUI();
	pListItem->SetMinWidth(nWidth);
	pListItem->SetMinHeight(nHeight);
	pListItem->Add(pHLayout);
	pListItem->SetEnabled(FALSE);
	pListItem->SetBkColor(0xFFF2F3F5);
	pList->Add(pListItem);
	//::MessageBox(NULL, _T("Send!"), _T("Duilib Demo"), MB_OK);
	pList->EndDown();

	//SIZE szScrollRange = pList->GetScrollRange();
	//SIZE szScrollPos = pList->GetScrollPos();
	//szScrollPos.cy = szScrollRange.cy;
	//pList->SetScrollPos(szScrollPos);
	return;
}

void CVirtualWndPage1::OnMenu(TNotifyUI& msg)
{
	
	::MessageBox(NULL, _T("OnMenu"), _T("Duilib Demo"), MB_OK);
	return;
}