
#include "stdafx.h"
#include "CVirtualWnd.h"

//虚拟窗口为page1的List控件及其子控件，他们的消息处理都在这里
DUI_BEGIN_MESSAGE_MAP(CVirtualWndPage1, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)			//page1里的click消息会被拦截，mainwnd就收不到了
	DUI_ON_MSGTYPE_CTRNAME(DUI_MSGTYPE_CLICK,_T("open"), OnClick)
	//DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED, OnSelectChanged)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMCLICK, OnItemClick)   //这个会拦截mainwnd的itemclick消息
DUI_END_MESSAGE_MAP()

CVirtualWndPage1::CVirtualWndPage1()
{
	m_pPaintManager = NULL;
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