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
 * 3D오브젝트중 메시속성을 가진 클래스
 *
 */
class ZMesh : public ZNode
{
protected:
	BOOL					m_isSkinned;	/// 스키닝이 적용되는 메시인가?

	DWORD					m_nVerts;		/// 전체 정점의 개수
	DWORD					m_nTriangles;	/// 그려질 삼각형의 개수
	DWORD					m_dwFVF;		/// 정점의 fvf값
	LPDIRECT3DVERTEXBUFFER9	m_pVB;			/// 정점 버퍼
	LPDIRECT3DINDEXBUFFER9	m_pIB;			/// 인덱스 버퍼
protected:
	/// 정점배열과 버퍼를 생성한다
	virtual	int _CreateVIB( ZCMesh* pMesh ) { return 1; }
public:
	ZMesh( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh );
	~ZMesh();
	
	/// 메시를 그린다
	virtual int	Draw();
};

#endif // _ZMESH_H_