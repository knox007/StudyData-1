#ifndef _ZNODEMGR_H_
#define _ZNODEMGR_H_

#include "define.h"
#include "ZCParsedData.h"
#include "zdefine.h"
#include "ZMesh.h"
#include "ZBone.h"
#include "ZRigidMesh.h"
#include "ZSkinnedMesh.h"
#include "ZFFSkinnedMesh.h"
#include "ZSWSkinnedMesh.h"
#include "ZMaterialMgr.h"
//#include "ZSceneMgr.h"

class ZSceneMgr;
/**
 * ������ �����ϱ����� Ŭ����
 *
 */
class ZNodeMgr
{
public:
	enum SKINMETHOD
	{ 
		SKINMETHOD_SW,	// SoftWare ��Ű��
		SKINMETHOD_FF,	// D3D Fixed Function ��Ű��
		SKINMETHOD_VS	// Vertex Shader ��Ű��
	};

protected:
	ZTObjectInfo			m_info;			/// ���� �����ü�� ���� ����
	std::vector<ZNode*>		m_nodes;		/// ����
	LPDIRECT3DDEVICE9		m_pDev;			/// D3D����̽�
	D3DXMATRIXA16			m_matTM;		/// �ڽ� ��� ��ü�� ����� TM
	std::vector<D3DXMATRIX>	m_matPalette;
	D3DXVECTOR3				m_bboxMaxOrig;	/// �ٿ�� �ڽ��� ���� �ִ밪(max)
	D3DXVECTOR3				m_bboxMinOrig;	/// �ٿ�� �ڽ��� ���� �ּҰ�(min)
	float					m_fRadius;

	BOOL _IsBone( int n )
	{
		for( int i = 0 ; i < m_info.BoneTable.size() ; i++ )
			if( m_info.BoneTable[i] == n ) return TRUE;

		return FALSE;
	}

public:
	ZNodeMgr( LPDIRECT3DDEVICE9 pDev, ZCParsedData* pData, SKINMETHOD sm );
	~ZNodeMgr();

	/// ��������ü�� �����͸� ��ȯ�Ѵ�
	ZTObjectInfo*	GetInfo() { return &m_info; }

	/// TM�� ���´�
	D3DXMATRIXA16*	GetTM() { &m_matTM; }

	/// TM�� �����Ѵ�
	void SetTM( D3DXMATRIXA16* pTM ) { m_matTM = *pTM; }
	float GetRadius() { return m_fRadius; }

	/// �ִϸ��̼� ����� �����
	int Animate( float fFrame );
	int SetFrame( float fFrame ) { return Animate( fFrame ); }

	/// �����ü�� �׸���.
	int Draw( int nNodeType );
	int DrawBBox( int nNodeType );
};

#endif // _ZNODEMGR_H_