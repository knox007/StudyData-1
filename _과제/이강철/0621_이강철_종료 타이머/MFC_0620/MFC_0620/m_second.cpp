// m_second.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC_0620.h"
#include "m_second.h"
#include "afxdialogex.h"


// m_second 대화 상자

IMPLEMENT_DYNAMIC(m_second, CDialogEx)

m_second::m_second(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

m_second::~m_second()
{
}

void m_second::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_second_hour);
	DDX_Control(pDX, IDC_COMBO2, m_second_min);
	DDX_Control(pDX, IDC_COMBO3, m_second_sec);
	DDX_Control(pDX, IDC_EDIT1, m_second_nowtime);
	DDX_Control(pDX, IDC_EDIT2, m_second_latetime);
	DDX_Control(pDX, IDC_EDIT3, m_second_endtime);
	DDX_Control(pDX, IDC_EDIT4, t_hour);
	DDX_Control(pDX, IDC_EDIT5, t_min);
	DDX_Control(pDX, IDC_EDIT6, t_sec);
}


BEGIN_MESSAGE_MAP(m_second, CDialogEx)
END_MESSAGE_MAP()


// m_second 메시지 처리기
