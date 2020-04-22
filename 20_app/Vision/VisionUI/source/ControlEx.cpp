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

void CListContainerElementEx::DoEvent(TEventUI& event)
{
	if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND) {
		if (m_pOwner != NULL) m_pOwner->DoEvent(event);
		else CContainerUI::DoEvent(event);
		return;
	}

	if (event.Type == UIEVENT_DBLCLICK)
	{
		if (IsEnabled()) {
			//Activate();
			Invalidate();
			m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMDBCLICK);
		}
		return;
	}
	if (event.Type == UIEVENT_KEYDOWN)
	{
		if (IsKeyboardEnabled() && IsEnabled()) {
			if (event.chKey == VK_RETURN) {
				Activate();
				Invalidate();
				return;
			}
		}
	}
	if (/*event.Type == UIEVENT_BUTTONDOWN ||*/ event.Type == UIEVENT_RBUTTONDOWN)
	{
		if (IsEnabled()) {
			//Select();
			Invalidate();
			m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);
		}
		return;
	}
	if (event.Type == UIEVENT_BUTTONUP )
	{
		if (IsEnabled()) {
			//m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);
			//Select();
			Invalidate();
		}
		return;
	}
	if (event.Type == UIEVENT_MOUSEMOVE)
	{
		return;
	}
	if (event.Type == UIEVENT_MOUSEENTER)
	{
		if (::PtInRect(&m_rcItem, event.ptMouse)) {
			if (IsEnabled()) {
				if ((m_uButtonState & UISTATE_HOT) == 0) {
					m_uButtonState |= UISTATE_HOT;
					Invalidate();
				}
			}
		}
	}
	if (event.Type == UIEVENT_MOUSELEAVE)
	{
		if (!::PtInRect(&m_rcItem, event.ptMouse)) {
			if (IsEnabled()) {
				if ((m_uButtonState & UISTATE_HOT) != 0) {
					m_uButtonState &= ~UISTATE_HOT;
					Invalidate();
				}
			}
			if (m_pManager) m_pManager->RemoveMouseLeaveNeeded(this);
		}
		else {
			if (m_pManager) m_pManager->AddMouseLeaveNeeded(this);
			return;
		}
	}

	// An important twist: The list-item will send the event not to its immediate
	// parent but to the "attached" list. A list may actually embed several components
	// in its path to the item, but key-presses etc. needs to go to the actual list.
	if (m_pOwner != NULL) m_pOwner->DoEvent(event); else CControlUI::DoEvent(event);
}

CListContainerElementContact::CListContainerElementContact()
{
	CDialogBuilder builder;
	m_pListContainerElementContct = static_cast<CContainerUI*>(builder.Create(_T("ListContainerElementContact.xml"), (UINT)0));
	if (m_pListContainerElementContct) {
		this->Add(m_pListContainerElementContct);
	}
	else {
		this->RemoveAll();
		return;
	}

	//m_pListContainerElementContct
}

CListContainerElementContact::~CListContainerElementContact()
{

}

void CListContainerElementContact::DoEvent(TEventUI& event)
{
	if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND) {
		if (m_pOwner != NULL) m_pOwner->DoEvent(event);
		else CContainerUI::DoEvent(event);
		return;
	}

	if (event.Type == UIEVENT_DBLCLICK)
	{
		if (IsEnabled()) {
			//Activate();
			Invalidate();
			m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMDBCLICK);
		}
		return;
	}
	if (event.Type == UIEVENT_KEYDOWN)
	{
		if (IsKeyboardEnabled() && IsEnabled()) {
			if (event.chKey == VK_RETURN) {
				Activate();
				Invalidate();
				return;
			}
		}
	}
	if (event.Type == UIEVENT_BUTTONDOWN /*|| event.Type == UIEVENT_RBUTTONDOWN*/)
	{
		if (IsEnabled()) {
			Select();
			Invalidate();
			m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);
		}
		return;
	}
	if ( event.Type == UIEVENT_RBUTTONDOWN )
	{
		if (IsEnabled()) {
			Select();
			Invalidate();
			//m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);
		}
		return;
	}

	if (event.Type == UIEVENT_BUTTONUP)
	{
		if (IsEnabled()) {
			//m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);
			//Select();
			Invalidate();
		}
		return;
	}
	if (event.Type == UIEVENT_MOUSEMOVE)
	{
		return;
	}
	if (event.Type == UIEVENT_MOUSEENTER)
	{
		if (::PtInRect(&m_rcItem, event.ptMouse)) {
			if (IsEnabled()) {
				if ((m_uButtonState & UISTATE_HOT) == 0) {
					m_uButtonState |= UISTATE_HOT;
					Invalidate();
				}
			}
		}
	}
	if (event.Type == UIEVENT_MOUSELEAVE)
	{
		if (!::PtInRect(&m_rcItem, event.ptMouse)) {
			if (IsEnabled()) {
				if ((m_uButtonState & UISTATE_HOT) != 0) {
					m_uButtonState &= ~UISTATE_HOT;
					Invalidate();
				}
			}
			if (m_pManager) m_pManager->RemoveMouseLeaveNeeded(this);
		}
		else {
			if (m_pManager) m_pManager->AddMouseLeaveNeeded(this);
			return;
		}
	}

	// An important twist: The list-item will send the event not to its immediate
	// parent but to the "attached" list. A list may actually embed several components
	// in its path to the item, but key-presses etc. needs to go to the actual list.
	if (m_pOwner != NULL) m_pOwner->DoEvent(event); else CControlUI::DoEvent(event);
}

void CListContainerElementContact::InitContainer(CDuiString name = _T("Herman"), CDuiString mesg =_T("message"), CDuiString time =_T("time"))
{
	static_cast<CLabelUI*>(m_pListContainerElementContct->FindSubControl(_T("alias")))->SetText(name);
	static_cast<CLabelUI*>(m_pListContainerElementContct->FindSubControl(_T("message")))->SetText(mesg);
	static_cast<CLabelUI*>(m_pListContainerElementContct->FindSubControl(_T("time")))->SetText(time);
}

