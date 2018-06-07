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
 * 스키닝 메시 클래스
 *
 */
class ZSkinnedMesh : public ZMesh
{
private:
	// 소프트웨어 스키닝을 위해서 정점버퍼와 똑같은 정점배열을 한 카피 보관해 둔다.
	vector<ZSkinnedVertex>	m_vtx;	/// skinning 정점 배열
	// 소프트웨어 스키닝을 위해서 인덱스버퍼와 똑같은 인덱스배열을 한 카피 보관해 둔다.
	vector<Index3w>			m_idx;	/// 인덱스 배열

	int _CreateVIB( ZCMesh* pMesh );
public:
	ZSkinnedMesh( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh );
	~ZSkinnedMesh();

	int Draw();
};


#endif // _ZSKINNEDMESH_H_