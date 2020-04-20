#pragma once

class CRightMenuContact : public WindowImplBase
{
public:
	CRightMenuContact();
	~CRightMenuContact();

protected:
	virtual CDuiString GetSkinFolder()
	{
		return _T("");
	};
	virtual CDuiString GetSkinFile() 
	{
		return _T("RMenu_Wnd.xml");
	};;
	virtual LPCTSTR GetWindowClassName(void) const
	{
		return _T("RightMenuContact");
	};;
};