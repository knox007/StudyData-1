#ifndef _ZSKINNEDMESH_H_
#define _ZSKINNEDMESH_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "define.h"
#include "ZCMesh.h"
#include "zdefine.h"
#include "ZNode.h"
#include "ZTrack.h"
#include "ZMesh.h"

/**
 * ��Ű�� �޽� Ŭ����
 *
 */
class ZSkinnedMesh : public ZMesh
{
private:
	// ����Ʈ���� ��Ű���� ���ؼ� �������ۿ� �Ȱ��� �����迭�� �� ī�� ������ �д�.
	vector<ZSkinnedVertex>	m_vtx;	/// skinning ���� �迭
	// ����Ʈ���� ��Ű���� ���ؼ� �ε������ۿ� �Ȱ��� �ε����迭�� �� ī�� ������ �д�.
	vector<Index3w>			m_idx;	/// �ε��� �迭

	int _CreateVIB( ZCMesh* pMesh );
public:
	ZSkinnedMesh( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh );
	~ZSkinnedMesh();

	int Draw();
};


#endif // _ZSKINNEDMESH_H_