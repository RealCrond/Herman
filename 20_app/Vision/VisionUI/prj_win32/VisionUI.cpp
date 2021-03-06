// VisionUI.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "mainwnd.h"
#include "weifilewnd.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CVisionResHandle resHandle;
	CPaintManagerUI::SetResourceDll(resHandle.GetHandle());

	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;

	CMainwnd* pFrame = new CMainwnd();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("DuiLib Demo from mbstudio.cn / meineson"), UI_CLASSSTYLE_DIALOG, 0L, 0, 0, 1024, 650);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);


	::SendMessage(pFrame->GetHWND(), 1124, 0, 0);

	//::MessageBox(NULL, _T("alert!"), _T("Duilib Demo"), MB_OK);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return 0;
}

