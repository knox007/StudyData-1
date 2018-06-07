#ifndef _PUTCYPHER_H_
#define _PUTCYPHER_H_

class CPUtFile;

const	char*	CYPHER_DEFKEY			=	"JACKIE_CYPHER";
const	int		CYPHER_DEFKEY_LENGTH	=	13;

bool	IsCypherDecode( CPUtFile* pFile );
bool	IsCypherFile( char *pszFileName );
bool	CypherEncode( char *pszBuffer, int nBuffer, const char* pszKey = "jackie_cypher" );
bool	CypherDecode( char *pszBuffer, int nBuffer, const char* pszKey = "jackie_cypher" );

#endif	//	_PUTCYPHER_H_