// m_first.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC_0620.h"
#include "m_first.h"
#include "afxdialogex.h"


// m_first 대화 상자

IMPLEMENT_DYNAMIC(m_first, CDialogEx)

m_first::m_first(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

m_first::~m_first()
{
}

void m_first::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO1, m_first_combo1);
	DDX_Control(pDX, IDC_COMBO2, m_first_combo2);
	DDX_Control(pDX, IDC_COMBO3, m_first_combo3);
	DDX_Control(pDX, IDC_COMBO4, m_first_combo4);
	DDX_Control(pDX, IDC_EDIT1, m_first_time);
	DDX_Control(pDX, IDC_EDIT2, m_first_late);
}


BEGIN_MESSAGE_MAP(m_first, CDialogEx)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &m_first::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &m_first::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &m_first::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &m_first::OnCbnSelchangeCombo4)
	ON_EN_CHANGE(IDC_EDIT1, &m_first::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &m_first::OnEnChangeEdit2)
END_MESSAGE_MAP()


// m_first 메시지 처리기


void m_first::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void m_first::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void m_first::OnCbnSelchangeCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void m_first::OnCbnSelchangeCombo4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void m_first::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void m_first::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
