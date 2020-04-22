
#pragma once

class CVirtualWndPage1 : public CNotifyPump
{
public:
	CVirtualWndPage1();
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);

	DUI_DECLARE_MESSAGE_MAP()
	
	void OnClick(TNotifyUI& msg);
	void OnSelectChanged(TNotifyUI &msg);
	void OnItemClick(TNotifyUI &msg);
	void OnItemDbClick(TNotifyUI &msg);
	void OnSendMessage(TNotifyUI &msg);
	void OnMenu(TNotifyUI& msg);

private:
	CPaintManagerUI* m_pPaintManager;
	int index;
};