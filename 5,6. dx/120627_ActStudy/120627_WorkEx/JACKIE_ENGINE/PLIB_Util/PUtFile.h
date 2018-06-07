#pragma once
#ifndef _PUTFILE_H_
#define _PUTFILE_H_

#include "putfilebase.h"

class CPUtFile :
	public CPUtFileBase
{
public:
	CPUtFile(void);
	virtual ~CPUtFile(void);
			
	/// READ / WRITE
	int		Read( void* pData, int nSize );
	int		Read( char* pszData );
	int		Write( void* pData, int nSize );
	int		Write( char* pszData );

};
//	CPUtFile

#endif	//	_PUTFILE_H_