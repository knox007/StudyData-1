
// MyFirstMFCView.cpp: CMyFirstMFCView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MyFirstMFC.h"
#endif

#include "MyFirstMFCDoc.h"
#include "MyFirstMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyFirstMFCView

IMPLEMENT_DYNCREATE(CMyFirstMFCView, CView)

BEGIN_MESSAGE_MAP(CMyFirstMFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()	
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMyFirstMFCView 생성/소멸

CMyFirstMFCView::CMyFirstMFCView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMyFirstMFCView::~CMyFirstMFCView()
{
}

BOOL CMyFirstMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMyFirstMFCView 그리기

void CMyFirstMFCView::OnDraw(CDC* pDC)
{
	CMyFirstMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//	(참고 9)
	pDC->TextOutW(100, 100, GetDocument()->_szData);
}


// CMyFirstMFCView 인쇄

BOOL CMyFirstMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMyFirstMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMyFirstMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMyFirstMFCView 진단

#ifdef _DEBUG
void CMyFirstMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMyFirstMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFirstMFCDoc* CMyFirstMFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFirstMFCDoc)));
	return (CMyFirstMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyFirstMFCView 메시지 처리기


void CMyFirstMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	//	(참고 11)
	/*
	GetDocument()->_szData = str;
	Invalidate();
	//*/

	//	(참고 7)
	CString str;
	str.Format(TEXT("%d, %d"), point.x, point.y);

	CClientDC dc(this);
	dc.TextOutW(point.x, point.y, str);
	
	CView::OnLButtonDown(nFlags, point);
}

void CMyFirstMFCView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	dc.TextOutW(100, 100, TEXT("OnPaint()"));	//	(참고 8)
	
	//	dc.TextOutW(100, 150, GetDocument()->_szData );	//	(참고 11)

}
