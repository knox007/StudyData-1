
// CustomMFCView.cpp: CCustomMFCView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CustomMFC.h"
#endif

#include "CustomMFCDoc.h"
#include "CustomMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCustomMFCView

IMPLEMENT_DYNCREATE(CCustomMFCView, CView)

BEGIN_MESSAGE_MAP(CCustomMFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CCustomMFCView 생성/소멸

CCustomMFCView::CCustomMFCView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCustomMFCView::~CCustomMFCView()
{
}

BOOL CCustomMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCustomMFCView 그리기

void CCustomMFCView::OnDraw(CDC* /*pDC*/)
{
	CCustomMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCustomMFCView 인쇄

BOOL CCustomMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCustomMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCustomMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CCustomMFCView 진단

#ifdef _DEBUG
void CCustomMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CCustomMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCustomMFCDoc* CCustomMFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustomMFCDoc)));
	return (CCustomMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CCustomMFCView 메시지 처리기


void CCustomMFCView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	dc.TextOutW(30, 30, TEXT("OnPaint"));
}


void CCustomMFCView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	MessageBox(TEXT("OnDestroy()"), TEXT("CUSTOM MFC"), MB_OK | MB_ICONINFORMATION );
}


void CCustomMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str;
	str.Format(TEXT("OnLButtonDown %d, %d"), point.x, point.y);
	MessageBox(str, TEXT("CUSTOM MFC"), MB_OK | MB_ICONINFORMATION);
	CView::OnLButtonDown(nFlags, point);
}


int CCustomMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	MessageBox(TEXT("OnCreate()"), TEXT("CUSTOM MFC"), MB_OK | MB_ICONINFORMATION);
	return 0;
}
