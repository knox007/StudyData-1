#ifndef _ZNODE_H_
#define _ZNODE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "define.h"
#include "ZCMesh.h"
#include "zdefine.h"

/**
 * 모든 3D오브젝트의 최상위 클래스
 *
 */
class ZNode
{
protected:
	enum NODETYPE { NODE_NODE, NODE_BONE, NODE_MESH };	// 현재 지원하는 노드의 종류

	int						m_nNodeType;	/// 노드의 종류
	int						m_nObjectID;	/// 오브젝트 ID
	int						m_nParentID;	/// 부모의ID
	int						m_nMaterialID;	/// 재질의 ID
	D3DXVECTOR3				m_bboxMax;		/// 바운딩 박스의 최대값(max)
	D3DXVECTOR3				m_bboxMin;		/// 바운딩 박스의 최소값(min)
	D3DXMATRIXA16			m_matLocal;		/// local TM 행렬(불변)
	D3DXMATRIXA16			m_matAni;		/// animation 행렬(변화)

	/// m_matTM = m_matAni * m_matLocal * (mom's m_matTM) * (grandmom's m_matTM) * ...
	D3DXMATRIXA16			m_matTM;		/// 최종 TM 행렬(변화)

	LPDIRECT3DDEVICE9		m_pDev;			/// D3D디바이스
public:
	ZNode( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh );
	~ZNode();

	/// 메시의 ID값을 얻는다
	int	GetObjectID() { return m_nObjectID; }

	/// 부모메시의 ID값을 얻는다
	int	GetParentID() { return m_nParentID; }

	int	GetMaterialID() { return m_nMaterialID; }

	/// 현재의 TM값을 얻는다
	D3DXMATRIXA16* GetMatrixTM() { return &m_matTM; }

	/// 경계상자의 값을 얻는다
	void GetBBox( D3DXVECTOR3* pMin, D3DXVECTOR3* pMax )
	{ *pMin = m_bboxMin; *pMax = m_bboxMax; }

	/// ZTrack으로부터 m_matAni를 구해서 m_matTM을 만든다
	D3DXMATRIXA16* Animate( float fFrame, D3DXMATRIXA16* pParentTM );

	/// 노드를 그린다.
	virtual int Draw() { return 1; }

	/// 경계상자를 그린다
	virtual int DrawBBox() { return 1; }
};

#endif // _ZNODE_H_