#include "Common.h"
#include "PUtCommon.h"

#if defined(_DEBUG) || defined(DEBUG)
#include "vld.h"
#include "PUTLog.h"
#endif

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{	
	CPFrFrameWork*		pFrame	=	NULL;
	CJGameInterface*	pGame	=	NULL;
	PUTNEW( pFrame, CPFrFrameWork );
	PUTNEW( pGame, CJGameInterface );

#if defined(_DEBUG) || defined(DEBUG)
	gUtLog->StartLog( JLOG_WINDOW );
#endif
	
	pFrame->LinkApp( pGame ); 
	pFrame->Run( g_ptszWndTitle, hInstance, 640,480, true );	

#if defined(_DEBUG) || defined(DEBUG)
	gUtLogDestroy;
#endif

	PUT_SAFE_DELETE( pFrame );
	return true;
}
//	EOF