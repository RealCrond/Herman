#pragma once


//�Զ���ؼ�ComputerExamineUI
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