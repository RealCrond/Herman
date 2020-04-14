#pragma once

#include <Windows.h>
#include <tchar.h>
//IDR_ZIPRES
#include "resource.h"

#ifdef VISIONSOURCEDLL_EXPORTS
	#define VISIONRES_API __declspec(dllexport)
#else
	#define VISIONRES_API __declspec(dllimport)
#endif // VISIONSOURCEDLL_EXPORTS


class VISIONRES_API CVisionResHandle
{
public:
	CVisionResHandle()
	{
		m_hInstance = ::LoadLibraryEx(_T("VisionSourceDll.dll"), NULL, DONT_RESOLVE_DLL_REFERENCES);
	};

	virtual ~CVisionResHandle()
	{
		::FreeLibrary(m_hInstance);
		m_hInstance = NULL;
	};

	HINSTANCE GetHandle() { return m_hInstance; };

private:
	HINSTANCE m_hInstance;
};

