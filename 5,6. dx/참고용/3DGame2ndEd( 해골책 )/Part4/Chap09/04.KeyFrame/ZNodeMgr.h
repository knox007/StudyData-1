#ifndef _ZNODEMGR_H_
#define _ZNODEMGR_H_
#include "define.h"
#include "ZCParsedData.h"
#include "zdefine.h"
#include "ZMesh.h"
#include "ZBone.h"
#include "ZSkinnedMesh.h"
#include "ZRigidMesh.h"

/**
 * ������ �����ϱ����� Ŭ����
 *
 */
class ZNodeMgr
{
protected:
	ZObjectInfo				m_info;			/// ���� �����ü�� ���� ����
	vector<ZMaterial>		m_materials;	/// ������ �迭
	vector<ZNode*>			m_nodes;		/// ����
	LPDIRECT3DDEVICE9		m_pDev;			/// D3D����̽�
	D3DXMATRIXA16			m_matTM;		/// �ڽ� ��� ��ü�� ����� TM

	BOOL _IsBone( int n )
	{
		for( int i = 0 ; i < m_info.BoneTable.size() ; i++ )
			if( m_info.BoneTable[i] == n ) return TRUE;

		return FALSE;
	}

public:
	ZNodeMgr( LPDIRECT3DDEVICE9 pDev, ZCParsedData* pData );
	~ZNodeMgr();

	/// ��������ü�� �����͸� ��ȯ�Ѵ�
	ZObjectInfo*	GetInfo() { return &m_info; }

	/// TM�� ���´�
	D3DXMATRIXA16*	GetTM() { &m_matTM; }

	/// TM�� �����Ѵ�
	void SetTM( D3DXMATRIXA16* pTM ) { m_matTM = *pTM; }

	/// �ִϸ��̼� ����� �����
	int Animate( float fFrame );

	/// �����ü�� �׸���.
	int Draw( int nNodeType );
	int DrawBBox( int nNodeType );
};

#endif // _ZNODEMGR_H_