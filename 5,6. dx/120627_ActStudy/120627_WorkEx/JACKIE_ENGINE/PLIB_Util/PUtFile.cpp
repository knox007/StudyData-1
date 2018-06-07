#include "StdAfx.h"
#include "PUtFile.h"
#include "PUtCommon.h"

//---------------------------------------------------------------------------------------
int		CPUtFile::Read( void* pData, int nSize )
{
	if( m_pFile )
	{
		if( m_nPosCur != ( m_nPosStart + m_nPosRelative ) )
			Seek( m_nPosRelative );

		int nSizeRead = (int)fread( pData, nSize, 1, m_pFile );

		m_nPosRelative	+=	nSize;
		m_nPosCur		+=	nSize;

		return nSizeRead;

	}//	if( m_pFile )

	return -1;

}//	Read( void* pData, int nSize )
//---------------------------------------------------------------------------------------
int		CPUtFile::Read( char* pszData )
{
	if( m_pFile )
	{
		if( m_nPosCur != ( m_nPosStart + m_nPosRelative ) )
			Seek( m_nPosRelative );

		int nSizeRead	=	0;

		int	nSize = 0;
		nSizeRead	=	(int)fread( &nSize, sizeof( int ), 1, m_pFile );
		if( nSize > 0 )
			nSizeRead += (int)fread( pszData, nSize, 1, m_pFile );

		m_nPosRelative	+=	nSizeRead;
		m_nPosCur		+=	nSizeRead;

		return nSizeRead;

	}//	if( m_pFile )

	return -1;

}//	Read( char* pszData )
//---------------------------------------------------------------------------------------
int		CPUtFile::Write( void* pData, int nSize )
{
	if( m_pFile )
	{
		if( m_nPosCur != ( m_nPosStart + m_nPosRelative ) )
			Seek( m_nPosRelative );

		int nSizeWrite = (int)fwrite( pData, 1, nSize, m_pFile );

		m_nPosRelative	+= nSize;
		m_nPosCur		+= nSize;

		return nSizeWrite;

	}//	if( m_pFile )

	return -1;

}//	Write( void* pData, int nSize )
//---------------------------------------------------------------------------------------
int		CPUtFile::Write( char* pszData )
{
	if( m_pFile )
	{
		if( m_nPosCur != ( m_nPosStart + m_nPosRelative ) )
			Seek( m_nPosRelative );

		int nSizeWrite = 0;

		int nLen	=	(int)strlen(pszData);
		nSizeWrite	=	(int)fwrite( &nLen, 1, sizeof( int ), m_pFile );

		if( nLen > 0)
			nSizeWrite	+=	(int)fwrite( pszData, 1, nLen, m_pFile );

		m_nPosRelative	+=	nSizeWrite;
		m_nPosCur		+=	nSizeWrite;

		return nSizeWrite;

	}//	if( m_pFile )

	return -1;

}//	Write( char* pszData )
//---------------------------------------------------------------------------------------
//	EOF