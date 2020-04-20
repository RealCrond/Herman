/*************



**************/
#pragma once
#include "CVirtualWnd.h"
#include "weifilewnd.h"
#include "rightmenucontact.h"

class CMainwnd : public WindowImplBase
{
public:
	CMainwnd();
	virtual ~CMainwnd();
	virtual void InitWindow();


	/**ʹ��zip��Դ���Ķ�̬��**/
	virtual UILIB_RESOURCETYPE GetResourceType() const{
		return UILIB_ZIPRESOURCE;
	};

	virtual LPCTSTR GetResourceID() const{
		return MAKEINTRESOURCE(IDR_ZIPRES);
	};

	//�Զ���ؼ�
	CControlUI* CreateControl(LPCTSTR pstrClass);

	//�ؼ���Ϣ������Ӧ����
	DUI_DECLARE_MESSAGE_MAP()
	void OnClose(TNotifyUI& msg);
	void OnWeiFile(TNotifyUI& msg);
	void OnRightMenu(TNotifyUI& msg);
	void OnMenu(TNotifyUI& msg);
	void OnItemClick(TNotifyUI &msg);
	void OnOptionSelectChange(TNotifyUI &msg);
	void OnClick(TNotifyUI &msg);

	//�Զ�����Ϣ������Ӧ����
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
	CButtonUI*		m_pCloseBtn;
	CButtonUI*		m_pMaxBtn;
	CButtonUI*		m_pMinBtn;
	CListUI*        m_pList;
	CTabLayoutUI*	m_pTabLayout;

	CVirtualWndPage1 m_Page1;
	CVirtualWndPage1 m_Page2;
	CRightMenuContact* pMenuWnd;
};
