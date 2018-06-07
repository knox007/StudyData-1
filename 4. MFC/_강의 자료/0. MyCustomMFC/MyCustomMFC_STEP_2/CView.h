//====================================================
#pragma once
#include "CObject.h"
//====================================================
class CView;
typedef void (CView::*CViewFuncPt)();
//====================================================
struct MessageMap
{
	UINT iMsg;
	CViewFuncPt _fp;
};

//====================================================
class CView : public CObject
{	
public:		
	static MessageMap messageMap[];	
	void OnCreate();
	void OnDraw();
	void OnDestroy();
	void OnLButtonDown();
};
extern CViewFuncPt fpCViewGlobal;
//====================================================
extern CView g_View;
//====================================================