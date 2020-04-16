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