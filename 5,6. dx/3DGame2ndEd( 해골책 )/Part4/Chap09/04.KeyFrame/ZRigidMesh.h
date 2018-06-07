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
 * 스키닝 없는 메시 클래스
 *
 */
class ZRigidMesh : public ZMesh
{
private:
	// 정점버퍼와 똑같은 정점배열을 한 카피 보관해 둔다.
	vector<ZRigidVertex>	m_vtx;	/// skinning없는 정점 배열
	// 인덱스버퍼와 똑같은 인덱스배열을 한 카피 보관해 둔다.
	vector<Index3w>			m_idx;	/// 인덱스 배열

	int _CreateVIB( ZCMesh* pMesh );
public:
	ZRigidMesh( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh );
	~ZRigidMesh();

	int Draw();
};


#endif // _ZRIGIDMESH_H_