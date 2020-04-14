#pragma once
#include "visionresourcedll.h"	

class CMainwnd : public WindowImplBase
{
public:
	CMainwnd();
	virtual ~CMainwnd();

	virtual UILIB_RESOURCETYPE GetResourceType() const{
		return UILIB_ZIPRESOURCE;
	};

	virtual LPCTSTR GetResourceID() const{
		return MAKEINTRESOURCE(IDR_ZIPRES);
	};


	//自定义控件
	CControlUI* CreateControl(LPCTSTR pstrClass){
		if (_tcscmp(pstrClass, _T("ComputerExamine")) == 0) 
			return new ComputerExamineUI();
		return NULL;
	};

	//控件消息及其响应函数
	DUI_DECLARE_MESSAGE_MAP()
	void OnClose(TNotifyUI& msg);

	//自定义消息及其响应函数
	DUI_DECLARE_CUSTOM_MESSAGE_MAP()
	LRESULT	OnTestInd(WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	virtual CDuiString GetSkinFolder() {
		return _T("");
	};

	virtual CDuiString GetSkinFile() {
		return _T("MAIN_WND.xml");
	};

	virtual LPCTSTR GetWindowClassName(void) const {
		return _T("MainWnd");
	};

private:
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pMinBtn;

};
