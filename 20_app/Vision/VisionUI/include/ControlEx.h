#pragma once


//自定义控件ComputerExamineUI
class ComputerExamineUI : public CContainerUI
{
public:
	ComputerExamineUI();
	virtual ~ComputerExamineUI();
};


class CListContainerElementEx : public CListContainerElementUI
{
public:
	CListContainerElementEx();
	virtual ~CListContainerElementEx();

	void DoEvent(TEventUI& event);
};

class CListContainerElementContact : public CListContainerElementUI
{
public:
	CListContainerElementContact();
	virtual ~CListContainerElementContact();
	void DoEvent(TEventUI& event);

	void InitContainer(CDuiString name/* = _T("Herman")*/, CDuiString mesg /*=_T("message")*/, CDuiString time /*=_T("time")*/);

private:
	CContainerUI* m_pListContainerElementContct;
};