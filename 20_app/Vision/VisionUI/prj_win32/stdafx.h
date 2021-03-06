// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料

// TODO: 在此处引用程序需要的其他头文件
#include <windows.h>
#include <tchar.h>

#include "../../DuiLib/UIlib.h"
using namespace DuiLib;

#include "visionresourcedll.h"	
#include "ControlEx.h"

#pragma comment(lib,"DuiLib_u.lib")
#pragma comment(lib,"VisionSourceDll.lib")


#define DUI_DECLARE_CUSTOM_MESSAGE_MAP()	\
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

#define DUI_BEGIN_CUSTOM_MESSAGE_MAP(theClass)															\
	LRESULT theClass::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled){		\
		switch(uMsg){																						

#define PMSG_FUN(uMsg,fun)						\
		case uMsg:								\
			fun(uMsg, wParam, lParam, bHandled);		\
			break;

#define DUI_END_CUSTOM_MESSAGE_MAP()			\
			default:							\
				break;							\
		}										\
		return 0;								\
	}		