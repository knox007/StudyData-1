#ifndef _ZMESH_H_
#define _ZMESH_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "define.h"
#include "ZCMesh.h"
#include "zdefine.h"
#include "ZNode.h"
#include "ZTrack.h"

/**
 * 3D������Ʈ�� �޽üӼ��� ���� Ŭ����
 *
 */
class ZMesh : public ZNode
{
protected:
	BOOL					m_isSkinned;	/// ��Ű���� ����Ǵ� �޽��ΰ�?

	DWORD					m_nVerts;		/// ��ü ������ ����
	DWORD					m_nTriangles;	/// �׷��� �ﰢ���� ����
	DWORD					m_dwFVF;		/// ������ fvf��
	LPDIRECT3DVERTEXBUFFER9	m_pVB;			/// ���� ����
	LPDIRECT3DINDEXBUFFER9	m_pIB;			/// �ε��� ����
protected:
	/// �����迭�� ���۸� �����Ѵ�
	virtual	int _CreateVIB( ZCMesh* pMesh ) { return 1; }
public:
	ZMesh( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh );
	~ZMesh();
	
	/// �޽ø� �׸���
	virtual int	Draw();
};

#endif // _ZMESH_H_