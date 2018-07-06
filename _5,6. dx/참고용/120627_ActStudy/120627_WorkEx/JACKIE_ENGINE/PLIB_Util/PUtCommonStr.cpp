#include "StdAfx.h"
#include "PUtCommonStr.h"
#include "PUTCommonVerIntegrate.h"

const	int		MAX_PARSE_LINE	=	512;
//----------------------------------------------------------------------------------------
void	PUT_Trim( TCHAR *ptszBuff )
{
	int iLen = 0;

	int	i=0;
	int iCnt=0;

	iLen = strlen(ptszBuff);

	if(iLen <1)
		return;


	// 문자 \r \n제거
	for(i=iLen-1; i>=0; --i)
	{
		char* p = ptszBuff + i;

		if( '\n' == *p || '\r' == *p)
		{
			*(ptszBuff + i) = '\0';
		}

		++iCnt;

		if(iCnt>2)
			break;
	}


	// 우측의 공백 제거
	iCnt = 0;
	iLen = strlen(ptszBuff);

	for(i=iLen-1; i>=0; --i)
	{
		char* p = ptszBuff + i;

		if( ' ' == *p || '\t' == *p)
			continue;

		*(ptszBuff + i+1) = '\0';
		break;
	}

	iLen = i+1 +1;

	// 좌측의 공백제거
	char sT[MAX_PARSE_LINE]={0};

	PUT_StrNcpy(sT, ptszBuff, iLen);

	for(i=0; i < iLen; ++i)
	{
		char* p = sT + i;

		if( ' ' == *p || '\t' == *p)
			continue;

		break;
	}

	PUT_Strcpy(ptszBuff, sT+i);

}//	PUT_Trim
//----------------------------------------------------------------------------------------
void	PUT_GetStrOneLineInFile( TCHAR* ptszDst, int nMaxLine, FILE* pf )
{
	fgets(ptszDst, nMaxLine, pf);
	PUT_Trim(ptszDst);

}//	PUT_GetStrOneLine
//----------------------------------------------------------------------------------------
void	PUT_GetStrInQuot( TCHAR* ptszDst, const TCHAR* ptszSrc )
{
	int iLen = strlen(ptszSrc);
	int	nBgn  =-1;
	int bStrt =0;
	int iRead =0;

	char* p = (char*)ptszSrc;

	while( 0 != *p)
	{
		if( '\"' == *p && 0 == bStrt)
			bStrt = 1;

		else if( '\"' == *p && 1 == bStrt)
		{
			*(ptszDst + nBgn) = 0;
			break;
		}

		if(nBgn>=0 && 1== bStrt)
			*(ptszDst + nBgn) = *p;

		if(1== bStrt)
			++nBgn;

		++p;

	}//	while( 0 != *p)

}//	PUT_GetStrInQuot
//----------------------------------------------------------------------------------------
//	EOF