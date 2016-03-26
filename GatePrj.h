
// GatePrj.h : main header file for the GatePrj application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGatePrjApp:
// See GatePrj.cpp for the implementation of this class
//

class CGatePrjApp : public CWinApp
{
public:
	CGatePrjApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGatePrjApp theApp;
