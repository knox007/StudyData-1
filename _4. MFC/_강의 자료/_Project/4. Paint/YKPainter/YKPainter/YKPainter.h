// YKPainter.h : YKPainter ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CYKPainterApp:
// �� Ŭ������ ������ ���ؼ��� YKPainter.cpp�� �����Ͻʽÿ�.
//

class CYKPainterApp : public CWinApp
{
public:
	CYKPainterApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
protected:

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CYKPainterApp theApp;