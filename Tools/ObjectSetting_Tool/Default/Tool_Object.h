
// Tool_Object.h : Tool_Object ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTool_ObjectApp:
// �� Ŭ������ ������ ���ؼ��� Tool_Object.cpp�� �����Ͻʽÿ�.
//

class CTool_ObjectApp : public CWinApp
{
public:
	CTool_ObjectApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTool_ObjectApp theApp;
