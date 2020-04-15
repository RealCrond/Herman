#include "stdafx.h"
#include "ControlEx.h"

ComputerExamineUI::ComputerExamineUI() {
	CDialogBuilder builder;
	CContainerUI* pComputerExamine = static_cast<CContainerUI*>(builder.Create(_T("ComputerExamine.xml"), (UINT)0));
	if (pComputerExamine) {
		this->Add(pComputerExamine);
	}
	else {
		this->RemoveAll();
		return;
	}
}

ComputerExamineUI::~ComputerExamineUI()
{

}


CListContainerElementEx::CListContainerElementEx() {
	CDialogBuilder builder;
	CContainerUI* pListContainerElementEx = static_cast<CContainerUI*>(builder.Create(_T("ListContainerElementEx.xml"), (UINT)0));
	if (pListContainerElementEx) {
		this->Add(pListContainerElementEx);
	}
	else {
		this->RemoveAll();
		return;
	}
}

CListContainerElementEx::~CListContainerElementEx()
{

}