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
protected:
	int _CreateVIB( ZCMesh* pMesh );
public:
	ZRigidMesh( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh );
	virtual ~ZRigidMesh();

	virtual int	Draw( D3DXMATRIX* pTM );
};


#endif // _ZRIGIDMESH_H_