// TabOne.cpp: 구현 파일
//

#include "stdafx.h"
#include "0620_MFC.h"
#include "TabOne.h"
#include "afxdialogex.h"


// TabOne 대화 상자

IMPLEMENT_DYNAMIC(TabOne, CDialogEx)

TabOne::TabOne(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

TabOne::~TabOne()
{
}

void TabOne::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combo_H);
	DDX_Control(pDX, IDC_COMBO2, combo_M);
	DDX_Control(pDX, IDC_COMBO3, combo_S);
	DDX_Control(pDX, IDC_EDIT1, edit_T);
	DDX_Control(pDX, IDC_EDIT2, edit_NT);
}


BEGIN_MESSAGE_MAP(TabOne, CDialogEx)
END_MESSAGE_MAP()


// TabOne 메시지 처리기
