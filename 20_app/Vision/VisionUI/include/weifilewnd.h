#pragma once


class CWeifileWnd : public WindowImplBase
{
public:
	CWeifileWnd();
	~CWeifileWnd();

	/**ʹ��zip��Դ���Ķ�̬��**/
	//virtual UILIB_RESOURCETYPE GetResourceType() const {
	//	return UILIB_ZIPRESOURCE;
	//};

	//virtual LPCTSTR GetResourceID() const {
	//	return MAKEINTRESOURCE(IDR_ZIPRES);
	//};

protected:
	virtual CDuiString GetSkinFolder()
	{
		return _T("");
	};

	virtual CDuiString GetSkinFile()
	{
		return _T("WeiFile_Wnd.xml");
	};

	virtual LPCTSTR GetWindowClassName(void) const
	{
		return _T("WeifileWnd");
	};

};