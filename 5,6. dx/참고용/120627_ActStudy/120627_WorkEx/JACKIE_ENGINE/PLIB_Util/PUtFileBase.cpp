#include "stdafx.h"
#include "PUtFileBase.h"
#include "PUtCommon.h"
#include "PUtCommonStr.h"
#include "PreDef_UT.h"
#include "PUTCommonVerIntegrate.h"

//------------------------------------------------------------------------------
void	CPUtFileBase::InitMembers()	
{
	PUT_ZERO_MEMORY(m_szFilePath);
	m_pFile			=	0;
	m_nPosStart		=	0;
	m_nPosRelative	=	0;
	m_nPosCur		=	0;

}//	InitMembers
//-------------------------------------------------------------------------------
void	CPUtFileBase::ClearMembers()
{
	Close();

}//	ClearMembers
//------------------------------------------------------------------------------
bool	CPUtFileBase::Open( const char* pszFName, const char* pcAccess )
{
#ifndef _ENGCLI_VS2003_VS2008_
	strcpy_s( m_szFilePath, sizeof(m_szFilePath), pszFName );
#else
	PUT_Strcpy( m_szFilePath, pszFName );
#endif
	return OpenThis( pcAccess );

}//	Open
//------------------------------------------------------------------------------
bool	CPUtFileBase::OpenThis( const char* pcAcess )
{	
#ifndef _ENGCLI_VS2003_VS2008_
	fopen_s( &m_pFile, m_szFilePath, pcAcess );
#else
	PUT_FOpen( &m_pFile, m_szFilePath, pcAcess );
#endif

	if( !m_pFile )
		return false;

	m_nPosRelative	=	0;

	return true;

}//	OpenThis
//------------------------------------------------------------------------------
int		CPUtFileBase::GetSize()
{
	if( m_pFile )
	{
		int nPosCur	=	0;
		int	nSize	=	0;
		
		/*
		SEEK_SET ���� ���½� ������ ù�Ӹ��� ��Ÿ���� ��� 
		SEEK_END ������ ������ �������� ��Ÿ���� ���
		SEEK_CUR ���� ��ġ
		ftell(?) ���� �۾����� ��ġ
		*/

		nPosCur	=	ftell( m_pFile );	//	���� �۾����� ��ġ. ���� �������� ó���� ����Ŵ
		
		fseek( m_pFile, 0, SEEK_END );	//	fseek(	����,
										//			����(offset) ���������κ��� ������ �Ÿ�,
										//			������(SET,CUR,END));

		nSize	=	ftell( m_pFile );

		fseek( m_pFile, nPosCur, SEEK_SET );

		return nSize;

	}//	if( m_pFile )

	return -1;

}//	GetSize
//------------------------------------------------------------------------------
int		CPUtFileBase::GetPosition()
{
	if( m_pFile )
	{
		int nPosCur =	0;
		nPosCur		=	ftell( m_pFile );
		return nPosCur;
	}

	return -1;

}//	GetPosition
//------------------------------------------------------------------------------
bool	CPUtFileBase::Seek( int nPos )
{
	int nPosReal	=	nPos + m_nPosStart;

	if( m_pFile )
	{
		fseek( m_pFile, nPosReal, SEEK_SET );
		m_nPosCur		=	nPosReal;
		m_nPosRelative	=	nPos;
		return true;
	}

	return false;

}//	Seek
//------------------------------------------------------------------------------
void	CPUtFileBase::SetFilePath( const char* pszName )	
{ 
#ifndef _ENGCLI_VS2003_VS2008_
	strcpy_s( m_szFilePath, sizeof(m_szFilePath), pszName );
#else
	PUT_Strcpy( m_szFilePath, pszName );
#endif
	

}//	SetFilePath
//------------------------------------------------------------------------
//	EOF