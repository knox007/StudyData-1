//====================================================
#pragma once
#include "CObject.h"
//====================================================
class CView : public CObject
{
public:
	void OnCreate();
	void OnDraw();
	void OnDestroy();
	void OnLButtonDown();

};
//====================================================
extern CView g_View;
//====================================================