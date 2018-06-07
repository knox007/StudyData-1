#include "stdafx.h"
#include "PUtCypher.h"
#include "PUtCommonStr.h"
#include "PUTCommonVerIntegrate.h"
#include "PUtFile.h"
#include "PreDef_UT.h"



//-------------------------------------------------------------------------------------
unsigned	char	CypherROR( unsigned char ucVal, unsigned char ucAmount )
{
	for( unsigned char ucCur = 0; ucCur < ucAmount; ++ucCur )
		ucVal	=	( (ucVal&1) ? 128 : 0) | (ucVal>>1);
	return ucVal;
}
//-------------------------------------------------------------------------------------
unsigned	char	CypherROL( unsigned char ucVal, unsigned char ucAmount )
{
	for( unsigned char ucCur = 0; ucCur < ucAmount; ++ucCur )
		ucVal	=	( (ucVal&0x80) ? 1 : 0) | (ucVal<<1);
	return ucVal;
}
//-------------------------------------------------------------------------------------
bool	IsCypherDecode( CPUtFile *pFile )
{
	char	szCypher[CYPHER_DEFKEY_LENGTH + 1] = {0,};

	if( !pFile->Read( szCypher, CYPHER_DEFKEY_LENGTH ) )
	{
		pFile->Seek( 0 );
		return false;
	}

	szCypher[CYPHER_DEFKEY_LENGTH]	=	0;

	if( PUT_StrCmp( szCypher, CYPHER_DEFKEY) )
		return true;

	pFile->Seek( 0 );
	return false;
}
//-------------------------------------------------------------------------------------
bool	IsCypherFile( char *pszFileName )
{
	FILE *pF = NULL;
#ifndef _ENGCLI_VS2003_VS2008_
	fopen_s( &pF, pszFileName, "rb" );
#else
	PUT_FOpen( &pF, pszFileName, "rb" );
#endif
	

	if( !pF )
		return false;

	char	szCypher[ CYPHER_DEFKEY_LENGTH + 1 ] = {0,};
	fread( szCypher, CYPHER_DEFKEY_LENGTH, 1, pF );
	szCypher[ CYPHER_DEFKEY_LENGTH ] = 0;

	fclose( pF );

	if( PUT_StrCmp( szCypher, CYPHER_DEFKEY ) )
		return true;

	return false;
}
//-------------------------------------------------------------------------------------
bool	CypherDecode( char *pszBuffer, int nBuffer, const char* pszKey )
{
	size_t nLenBuffer	=	nBuffer;
	size_t	nLenKey		=	strlen( pszKey );

	size_t nTmp		=	0;
	for( size_t nCur = 0; nCur < nLenBuffer; ++nCur )
	{
		nTmp			=	nCur % nLenKey;
		pszBuffer[nCur]	=	CypherROR( pszBuffer[nCur], pszKey[nTmp] );
	}

	return true;
}
//-------------------------------------------------------------------------------------
bool	CypherEncode( char *pszBuffer, int nBuffer, const char* pszKey )
{
	size_t nLenBuffer	=	nBuffer;
	size_t nLenKey		=	strlen( pszKey );

	size_t nTmp		=	0;
	for( size_t nCur = 0; nCur < nLenBuffer; ++nCur )
	{
		nTmp			=	nCur % nLenKey;
		pszBuffer[nCur]	=	CypherROL( pszBuffer[nCur], pszKey[nTmp] );
	}

	return true;
}
//-------------------------------------------------------------------------------------
//	EOF