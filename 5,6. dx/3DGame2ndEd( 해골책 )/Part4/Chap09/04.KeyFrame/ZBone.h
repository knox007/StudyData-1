#ifndef _ZBONE_H_
#define _ZBONE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "define.h"
#include "ZCMesh.h"
#include "zdefine.h"
#include "ZNode.h"
#include "ZTrack.h"

/// single mesh container
class ZBone : public ZNode
{
public:
	ZBone( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh );
	~ZBone();
	
	/// 메시를 그린다
	virtual int	Draw();
};

#endif // _ZBONE_H_