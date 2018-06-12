// CDialogAddressContents.cpp: 구현 파일
//

#include "stdafx.h"
#include "AddressManager.h"
#include "CDialogAddressContents.h"
#include "afxdialogex.h"


// CDialogAddressContents 대화 상자

IMPLEMENT_DYNAMIC(CDialogAddressContents, CDialogEx)

CDialogAddressContents::CDialogAddressContents(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONTENT, pParent)
{
	
}

CDialogAddressContents::~CDialogAddressContents()
{
}

void CDialogAddressContents::InitCityCBBox()
{
	TCHAR *tszCity[] = { TEXT("서울특별시"), TEXT("인천광역시"), TEXT("경기도"),
		TEXT("충청도"),		TEXT("강원도"),		TEXT("경상도"),
		TEXT("전라도"), TEXT("제주도") };

	for (int cur = 0; cur < 8; ++cur)
		_cbboxCity.AddString(tszCity[cur]);

	_cbboxCity.SetCurSel(0);
}

void CDialogAddressContents::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CITY, _cbboxCity);

	InitCityCBBox();
}


BEGIN_MESSAGE_MAP(CDialogAddressContents, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CDialogAddressContents 메시지 처리기


int CDialogAddressContents::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.



	return 0;
}
