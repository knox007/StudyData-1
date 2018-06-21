#include "StdAfx.h"
#include "EllipseDraw.h"

EllipseDraw::EllipseDraw(void)
{
}

EllipseDraw::~EllipseDraw(void)
{
}

void EllipseDraw::draw(CDC* pDc) {
	if (m_type == BORDERONLY) {
		CPen pen(PS_SOLID, m_Thickness, m_lineColor);

		CPen *oldPen = pDc->SelectObject(&pen);
		CGdiObject* oldBrush = pDc->SelectStockObject(NULL_BRUSH);
		
		pDc->Ellipse(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);

	} else if (m_type == BORDERFILL) {
		CPen pen(PS_SOLID, m_Thickness, m_lineColor);
		CBrush brush(m_fillColor);

		CPen* oldPen = pDc->SelectObject(&pen);
		CBrush* oldBrush = pDc->SelectObject(&brush);

		pDc->Ellipse(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);

	} else if (m_type == NOBORDERFILL) {
		CBrush brush(m_fillColor);

		CGdiObject* oldPen = pDc->SelectStockObject(NULL_PEN);
		CBrush* oldBrush = pDc->SelectObject(&brush);

		pDc->Ellipse(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);
	}
}

int EllipseDraw::drawType(void) {
	return CIRCLE;
}

void EllipseDraw::setRect(CPoint& topLeft, CPoint& bottomRight) {
	m_topLeft = topLeft;
	m_bottomRight = bottomRight;
}

void EllipseDraw::setCircle(CPoint& center, int radius)
{
	m_topLeft.x = center.x - radius;
	m_topLeft.y = center.y - radius;

	m_bottomRight.x = center.x + radius;
	m_bottomRight.y = center.y + radius;
}

void EllipseDraw::setProps(FIGURETYPE type, int& lineWidth, COLORREF& lineColor, COLORREF& fillColor) {
	m_type = type;
	m_Thickness = lineWidth;
	m_lineColor = lineColor;
	m_fillColor = fillColor;
}

void EllipseDraw::serialize(CArchive& ar) {
	int type = m_type;
	ar << drawType();
	ar << m_topLeft << m_bottomRight << type << m_Thickness << m_lineColor << m_fillColor;
}

void EllipseDraw::deserialize(CArchive& ar) {
	int type;

	ar >> m_topLeft >> m_bottomRight >> type >> m_Thickness >> m_lineColor >> m_fillColor;
	m_type = (FIGURETYPE)type;
}