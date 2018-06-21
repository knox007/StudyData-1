#pragma once

#include "DrawObject.h"
#include "TextDraw.h"
#include "BeeLineDraw.h"
#include "FillDraw.h"
#include "PencilDraw.h"
#include "EllipseDraw.h"
#include "RectangleDraw.h"
#include "PolygonDraw.h"


class YKPainterDoc : public CDocument {
private:
	CPtrList m_DrawObjs;
	DrawObject* m_Cur;

protected:
	YKPainterDoc();

public:
	TOOLTYPE CurDrawType;	//���� ���õ� �׸��� ���

	virtual ~YKPainterDoc();
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);   // ���� ��/����� ���� �����ǵǾ����ϴ�.

	CPtrList& getDrawObjects();

	TextDraw* getTextDraw(BOOL bNew=FALSE);
	BeeLineDraw* getBeeLineDraw(bool bNew=FALSE);
	FillDraw* getFillDraw(bool bNew=FALSE);
	PencilDraw* getPencilDraw(bool bNew=FALSE);
	EllipseDraw* getEllipseDraw(bool bNew=FALSE);
	RectangleDraw* getRactangleDraw(bool bNew=FALSE);
	PolygonDraw* getPolygonDraw(bool bNew=FALSE);
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_DYNCREATE(YKPainterDoc)
	DECLARE_MESSAGE_MAP()	
};
