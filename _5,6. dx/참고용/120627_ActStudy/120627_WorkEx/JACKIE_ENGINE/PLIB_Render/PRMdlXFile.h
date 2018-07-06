#ifndef _CPRMdlXFile_H_
#define _CPRMdlXFile_H_

#pragma once

#include "probject.h"
#include "PRXFileCommon.h"
#include "PRXMeshHierachy.h"

#include <string>


class CPRMdlXFile :	public CPRObject
{
public:
	CPRMdlXFile()			{ InitMembers(); }
	virtual ~CPRMdlXFile()	{ ClearMembers(); }

	bool	Init( LPDIRECT3DDEVICE9 pDev, char *pszXFile, D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, bool bRepeatAni );

	bool	Load( LPDIRECT3DDEVICE9 pDev, const char *pszFName );
	bool	OnUpdate( float fElapsedTime = 0 );
	HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );	
	void	OnReset( LPDIRECT3DDEVICE9 pDev )	{}
	void	OnLost()							{}

	void	SetAniSet( UINT unIdx );
	void	SetAniStart();
	void	SetAniNext();
	void	SetAniFaster();
	void	SetAniSlower();
	
	D3DXVECTOR3	GetInitCameraPos()	const;
	UINT		GetCurAniSet()		const	{ return m_unCurAniSet; }
	std::string	GetAniSetName( UINT unIdx );
	std::string	GetFName()					{ return m_strFileName; }
	void		SetFName( char *pszFName )	{ m_strFileName = pszFName; }

	void	SetScale( D3DXVECTOR3	vecScale )	{ m_vecScale	=	vecScale; }
	void	SetPos( D3DXVECTOR3	vecPos )		{ m_vecPos		=	vecPos; }
	void	SetRot( D3DXVECTOR3	vecRot );
	void	SetEnableRepeatAni( bool bRepeat )	{ m_bRepeatAni	=	bRepeat; }

	bool	GetEnableProcessAni()				{ return m_bProcessAni; }
	
	PRDMTRL9*		GetMtrls()						{ return GetMeshHierachy()->GetMtrls(); }
	PRDMTRL9		GetMtrl( int nIdx )				{ return GetMeshHierachy()->GetMtrl( nIdx ); }
	PRDXTXTRBUFF9*	GetTextures()					{ return GetMeshHierachy()->GetTextures(); }
	PRDXTXTRBUFF9	GetTexture( int nIdx )			{ return GetMeshHierachy()->GetTexture( nIdx ); }
	int					GetMtrlSize()					{ return GetMeshHierachy()->GetMtrlSize(); }

	LPD3DXFRAME			GetRootFrame()					{ return m_pFrameRoot; }


	
private:
	void	InitMembers();
	void	ClearMembers();

	void	UpdateFrameMatrices( const LPD3DXFRAME pFrameBase, const D3DXMATRIX	*pmatParent );
	void	DrawFrame( LPDIRECT3DDEVICE9 pDev, LPD3DXFRAME pFrame ) const;	
	void	DrawMeshContainer( LPDIRECT3DDEVICE9 pDev, PRDXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase ) const;
	void	SetupBoneMatrices( LPDIRECT3DDEVICE9 pDev, sPRDXXFRAMEEx *pFrame, LPD3DXMATRIX pmatParent );
	CPRXMeshHierachy*	GetMeshHierachy()	{ return m_pXMeshHierachy; }

	//	�ִϸ��̼ǿ� �ʿ��� ����.
	LPD3DXFRAME					m_pFrameRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAniCtrl;
	sPRDXXMESHCONTAINEREx		*m_pFirstMesh;

	UINT	m_unCurAniSet;
	UINT	m_unNumAniSets;
	UINT	m_unCurTrack;
	float	m_fCurTime;
	float	m_fSpeedAdjust;

	//	ī�޶���ġ�� ���� ��豸
	D3DXVECTOR3	m_vecSphereCenter;
	float		m_fSphereRadius;

	//	�� ����
	D3DXMATRIX	*m_pmatBone;
	int			m_nMaxBones;

	double		m_fAniStartTime;			//	�ִϸ��̼� ���� �ð� ����.
	bool		m_bAni;						//	�ִϸ��̼� �÷���
	bool		m_bRepeatAni;				//	�ݺ� �÷���.
	bool		m_bProcessAni;				//	�ִϸ��̼� ����.	
	double		m_fExtraTime;			

	std::string	m_strFileName;

	D3DXMATRIX		m_matWorld;				//	��ü�� ���� ���.
	D3DXVECTOR3		m_vecScale;				//	������
	D3DXVECTOR3		m_vecPos;				//	��ġ
	D3DXVECTOR3		m_vecRot;				//	ȸ��
	D3DXQUATERNION  m_quartOrientation;
	
	CPRXMeshHierachy	*m_pXMeshHierachy;

};


#endif	//	_CPRMdlXFile_H_