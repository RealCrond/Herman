
#pragma once

class CVirtualWndPage : public CNotifyPump
{
public:
	CVirtualWndPage();
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);

	DUI_DECLARE_MESSAGE_MAP()
	
	virtual void OnClick(TNotifyUI& msg);
	virtual void OnSelectChanged(TNotifyUI &msg);
	virtual void OnItemClick(TNotifyUI &msg);
private:
	CPaintManagerUI* m_pPaintManager;
	int index;
};