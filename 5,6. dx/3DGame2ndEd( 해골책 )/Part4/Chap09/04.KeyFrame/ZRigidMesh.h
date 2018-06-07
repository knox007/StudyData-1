#ifndef _ZRIGIDMESH_H_
#define _ZRIGIDMESH_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "define.h"
#include "ZCMesh.h"
#include "zdefine.h"
#include "ZNode.h"
#include "ZTrack.h"
#include "ZMesh.h"

/**
 * ��Ű�� ���� �޽� Ŭ����
 *
 */
class ZRigidMesh : public ZMesh
{
private:
	// �������ۿ� �Ȱ��� �����迭�� �� ī�� ������ �д�.
	vector<ZRigidVertex>	m_vtx;	/// skinning���� ���� �迭
	// �ε������ۿ� �Ȱ��� �ε����迭�� �� ī�� ������ �д�.
	vector<Index3w>			m_idx;	/// �ε��� �迭

	int _CreateVIB( ZCMesh* pMesh );
public:
	ZRigidMesh( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh );
	~ZRigidMesh();

	int Draw();
};


#endif // _ZRIGIDMESH_H_