// TabTwo.cpp: 구현 파일
//

#include "stdafx.h"
#include "0620_MFC.h"
#include "TabTwo.h"
#include "afxdialogex.h"


// TabTwo 대화 상자

IMPLEMENT_DYNAMIC(TabTwo, CDialogEx)

TabTwo::TabTwo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

TabTwo::~TabTwo()
{
}

void TabTwo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_H);
	DDX_Control(pDX, IDC_EDIT2, edit_M);
	DDX_Control(pDX, IDC_EDIT3, edit_S);
	DDX_Control(pDX, IDC_EDIT4, edit_T);
}


BEGIN_MESSAGE_MAP(TabTwo, CDialogEx)
END_MESSAGE_MAP()


// TabTwo 메시지 처리기
