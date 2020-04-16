
#pragma once

class CVirtualWndPage1 : public CNotifyPump
{
public:
	CVirtualWndPage1();
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);

	DUI_DECLARE_MESSAGE_MAP()
	
	virtual void OnClick(TNotifyUI& msg);
	virtual void OnSelectChanged(TNotifyUI &msg);
	virtual void OnItemClick(TNotifyUI &msg);
	virtual void OnItemDbClick(TNotifyUI &msg);

private:
	CPaintManagerUI* m_pPaintManager;
	int index;
};