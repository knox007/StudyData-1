#ifndef _CPRXFILEENTITY_H_
#define _CPRXFILEENTITY_H_

#pragma once

#include "probject.h"
#include "PRXFileCommon.h"
#include "PRXMeshHierachy.h"

#include <string>


class CPRXFileEntity :	public CPRObject
{
public:
	CPRXFileEntity()			{ InitMembers(); }
	virtual ~CPRXFileEntity()	{ ClearMembers(); }

	bool	Init( LPDIRECT3DDEVICE9 pDev, char *pszXFile, D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, bool bRepeatAni );

	bool	Load( LPDIRECT3DDEVICE9 pDev, const char *pszFName );
	void	OnUpdate( float fElapsedTime = 0 );
	HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );	

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
	
	D3DMATERIAL9*		GetMtrls()						{ return GetMeshHierachy()->GetMtrls(); }
	D3DMATERIAL9		GetMtrl( int nIdx )				{ return GetMeshHierachy()->GetMtrl( nIdx ); }
	LPDIRECT3DTEXTURE9*	GetTextures()					{ return GetMeshHierachy()->GetTextures(); }
	LPDIRECT3DTEXTURE9	GetTexture( int nIdx )			{ return GetMeshHierachy()->GetTexture( nIdx ); }
	int					GetMtrlSize()					{ return GetMeshHierachy()->GetMtrlSize(); }

	LPD3DXFRAME			GetRootFrame()					{ return m_pFrameRoot; }


	
private:
	void	InitMembers();
	void	ClearMembers();

	void	UpdateFrameMatrices( const LPD3DXFRAME pFrameBase, const D3DXMATRIX	*pmatParent );
	void	DrawFrame( LPDIRECT3DDEVICE9 pDev, LPD3DXFRAME pFrame ) const;	
	void	DrawMeshContainer( LPDIRECT3DDEVICE9 pDev, LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase ) const;
	void	SetupBoneMatrices( LPDIRECT3DDEVICE9 pDev, sPRD3DXFRAMEEx *pFrame, LPD3DXMATRIX pmatParent );
	CPRXMeshHierachy*	GetMeshHierachy()	{ return m_pXMeshHierachy; }

	//	애니메이션에 필요한 정보.
	LPD3DXFRAME					m_pFrameRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAniCtrl;
	sPRD3DXMESHCONTAINEREx		*m_pFirstMesh;

	UINT	m_unCurAniSet;
	UINT	m_unNumAniSets;
	UINT	m_unCurTrack;
	float	m_fCurTime;
	float	m_fSpeedAdjust;

	//	카메라위치를 위한 경계구
	D3DXVECTOR3	m_vecSphereCenter;
	float		m_fSphereRadius;

	//	본 정보
	D3DXMATRIX	*m_pmatBone;
	int			m_nMaxBones;

	double		m_fAniStartTime;			//	애니메이션 시작 시간 설정.
	bool		m_bAni;						//	애니메이션 플래그
	bool		m_bRepeatAni;				//	반복 플래그.
	bool		m_bProcessAni;				//	애니메이션 시작.	
	double		m_fExtraTime;			

	std::string	m_strFileName;

	D3DXMATRIX		m_matWorld;				//	객체의 월드 행렬.
	D3DXVECTOR3		m_vecScale;				//	스케일
	D3DXVECTOR3		m_vecPos;				//	위치
	D3DXVECTOR3		m_vecRot;				//	회전
	D3DXQUATERNION  m_quartOrientation;
	
	CPRXMeshHierachy	*m_pXMeshHierachy;

};


#endif	//	_CPRXFILEENTITY_H_