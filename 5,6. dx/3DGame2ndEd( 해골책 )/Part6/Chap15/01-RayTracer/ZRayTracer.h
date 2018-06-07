#ifndef _ZRAYTRACER_H_
#define _ZRAYTRACER_H_

#include "ZPreDefines.h"
#include "ZParsedData.h"
#include "ZParser.h"

class ZRayTracer
{
public:
	ZParsedData*	m_pData;
	int				m_cxScreen;
	int				m_cyScreen;
/*
	ZRay MakeRayFromMatrix( Mat4x4& matView, Mat4x4& matProj, int cxScreen, int cyScreen, int xPixel, int yPixel )
	{
		D3DXVECTOR4 ray_start_proj = D3DXVECTOR4(-2*xPixel+1, -2*yPixel+1, 0, 1);
		D3DXVECTOR4 ray_eye        = D3DXVECTOR4(0, 0, 0, 1);
		D3DXVECTOR4 ray_start;
		D3DXVECTOR4 ray_to;
		D3DXVECTOR4 ray_dir;
		D3DXMATRIX	matInv;

		D3DXMatrixInverse( &matInv, NULL, &matView );
		D3DXVec4Transform( &ray_start, &ray_eye,        &matInv );
		matInv = matView * matProj;
		D3DXMatrixInverse( &matInv, NULL, &matInv );
		D3DXVec4Transform( &ray_to,    &ray_start_proj, &matInv );
		D3DXVec4Scale( &ray_to,    &ray_to,    1.0f/ray_to.w   );// w=1 투영공간으로
		ray_dir = ray_to - ray_start;
		D3DXVec4Normalize(&ray_dir, &ray_dir);
		
		ZRay		ray;
		ray.vPos.x = ray_start.x;
		ray.vPos.y = ray_start.y;
		ray.vPos.z = ray_start.z;
		ray.vDir.x = ray_dir.x;
		ray.vDir.y = ray_dir.y;
		ray.vDir.z = ray_dir.z;
		
		return ray;
	}
*/

	ZRay MakeRayFromMatrix( Mat4x4& matView, Mat4x4& matProj, int cxScreen, int cyScreen, int xPixel, int yPixel )
	{
		ZRay		ray;
		Vector3f	v;
		Mat4x4		m;	// inverse(matView)

		// unprojection
		v.x = ((  ( ( xPixel*2.0f/cxScreen ) - 1.0f ) ) - matProj._31 ) / matProj._11;
		v.y = ((- ( ( yPixel*2.0f/cyScreen ) - 1.0f ) ) - matProj._32 ) / matProj._22;
//		v.x =   ( ( xPixel*2.0f/cxScreen ) - 1.0f );
//		v.y = - ( ( yPixel*2.0f/cyScreen ) - 1.0f );
		v.z =  0.0f;

		// unprojected space to view space
        D3DXMatrixInverse( &m, NULL, &matView );
		ray.vPos.x	= m._41;
		ray.vPos.y	= m._42;
		ray.vPos.z	= m._43;
        ray.vDir.x  = v.x*m._11 + v.y*m._21 + v.z*m._31;
        ray.vDir.y  = v.x*m._12 + v.y*m._22 + v.z*m._32;
        ray.vDir.z  = v.x*m._13 + v.y*m._23 + v.z*m._33;
		ray.vDir = ray.vDir - ray.vPos;
		D3DXVec3Normalize(&ray.vDir, &ray.vDir );
		return ray;
	}

	Color3f TraceRay( int cxScreen, int cyScreen, int xPixel, int yPixel )
	{
		ZRay	ray = MakeRayFromMatrix( m_pData->m_pCamera->m_matView, m_pData->m_pCamera->m_matProj, cxScreen, cyScreen, xPixel, yPixel );
		for( unsigned int i = 0 ; i < m_pData->m_geomList.size() ; i++ )
		{
			if( m_pData->m_geomList[i]->IsIntersect( &ray ) )
				return m_pData->m_geomList[i]->GetColor( m_pData->m_lightList[0], &ray );
		}
		return Color3f( 0,0,0 );
	}
	
	bool OpenXML( char* str )
	{
		S_DEL( m_pData );
		ZParser*	pParser = new ZParser();
		m_pData = new ZParsedData();

		if( !pParser->Parse( m_pData, (char*)str ) )
		{
            S_DEL( pParser );
			return false;
		}

		S_DEL( pParser );
		return true;
	}

	ZRayTracer()
	{
		m_pData = NULL;
		m_cxScreen = 640;
		m_cyScreen = 480;
	}
	ZRayTracer( int cxScreen, int cyScreen, char* szFilename )
	{
		m_pData = NULL;
		OpenXML( szFilename );
		m_cxScreen = cxScreen;
		m_cyScreen = cyScreen;
	}
	~ZRayTracer()
	{
		S_DEL( m_pData );
	}
};

#endif //  _ZRAYTRACER_H_