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