#pragma once
#ifndef _PUTFILEBASE_H_
#define _PUTFILEBASE_H_

class CPUtFileBase
{

public:
	CPUtFileBase(void)					{ InitMembers(); }
	virtual ~CPUtFileBase(void)			{ ClearMembers(); }

	/// FilePtr
	FILE*	GetFilePtr()				{ return m_pFile; }


	///	Position
	void	SetPosStart( int nPos )
			{ m_nPosStart = nPos; }	
	int		GetPosStart()
			{ return m_nPosStart; }
	int		GetPosition();
	bool	Seek( int nPos );

	
	
	/// FilePath
	void	SetFilePath( const char* pszName );
	char*	GetFilePath()				
			{ return m_szFilePath; }


	/// Access
	bool	OpenThis( const char* pcAcess );
	bool	Open( const char* pszFName, const char* pcAccess );
	bool	IsOpen()
			{ return (m_pFile != 0); }
	void	Close()
			{
				if( m_pFile )
					fclose( m_pFile );
				m_pFile = NULL;
			}

	/// Size
	int		GetSize();


	/// READ / WRITE
	virtual int		Read( void* pData, int nSize )	=	0;
	virtual int		Read( char* pszData )			=	0;
	virtual int		Write( void* pData, int nSize )	=	0;
	virtual int		Write( char* pszData )			=	0;
	


private:
	void	InitMembers();	
	void	ClearMembers();


protected:
	FILE*	m_pFile;
	char	m_szFilePath[MAX_PATH];
	int		m_nPosStart;
	int		m_nPosRelative;		//	파일내 포인터의 파일시작점을 기준으로 상대적 위치
	int		m_nPosCur;			//	파일내 포인터의 현재 위치

};


#endif	//	_PUTFILEBASE_H_