// PRTracer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CPRTracerApp:
// �� Ŭ������ ������ ���ؼ��� PRTracer.cpp�� �����Ͻʽÿ�.
//

class CPRTracerApp : public CWinApp
{
public:
	CPRTracerApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CPRTracerApp theApp;
