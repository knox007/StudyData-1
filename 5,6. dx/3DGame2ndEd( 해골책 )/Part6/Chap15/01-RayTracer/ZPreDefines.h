/** \brief global definitions, macro funcs, basic template, basic typedef, etc...
 *
 */

#ifndef _ZPREDEFINES_H_
#define _ZPREDEFINES_H_

//#pragma warning(disable:4786)	// to reduce STL warning in VC++6.0, not needed with VS.NET

#ifdef MAINBODY
#define DECLARE
#else
#define DECLARE extern
#endif

#pragma comment( lib, "d3dx9" )
#pragma comment( lib, "d3d9" )
/** 
 * For Using STL
 */
#include <assert.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
using namespace std;

/** 
 * For Using Direct3D helper struct & func
 */
#include <d3d9.h>
#include <d3dx9.h>

/** 
 * Macro Functions
 */
#define S_REL(p) { if(p) p->Release(); p = NULL; }
#define S_DEL(p) { if(p) delete p; p = NULL; }
#define S_DELS(p) { if(p) delete[] p; }

/**
 * Basic constants
 */
#define BIGFLOAT		9999.0f
#define EPSILON			0.0001f

/** \brief singleton template(from Game Programming Gems I)
 *
 */
template<class T> 
class ZTSingleton
{
	static T* m_pInstance;
public:
	ZTSingleton()
	{
		assert( !m_pInstance );
		int offset = (int)(T*)1-(int)(ZTSingleton<T>*)(T*)1;
		m_pInstance = (T*)((int)this + offset );
	}
	~ZTSingleton() { assert( m_pInstance ); m_pInstance = 0; }
	static T& GetInstance() { assert( m_pInstance ); return (*m_pInstance ); }
	static T* GetInstancePtr() { return m_pInstance; }
};

template <class T> T* ZTSingleton<T>::m_pInstance = 0;


/** \brief stl container wiping class except vector
 *
 */
template<typename TContainer>
inline void stl_wipe(TContainer& container)
{
	for( TContainer::iterator i = container.begin() ; i != container.end() ; ++i )
		delete *i;
	container.clear();
}

/** \brief stl vector wiping class
 *
 */
template<typename T>
void stl_wipe_vector(vector<T>& rVector)
{
	vector<T> emptyData;
	rVector.swap( emptyData );
}

/**
 * basic type definitions
 */
typedef D3DXVECTOR2 Vector2f;
typedef D3DXVECTOR3 Vector3f;
typedef D3DXVECTOR4 Vector4f;
typedef D3DXCOLOR Color4f;
typedef D3DXMATRIX Mat4x4;
/*
class Vector2f : public D3DXVECTOR2 {};
class Vector3f : public D3DXVECTOR3 {};
class Vector4f : public D3DXVECTOR4 {};
class Quat : public D3DXQUATERNION {};
class Color4f : public D3DXCOLOR {};
class Mat4x4 : public D3DXMATRIXA16 {};
*/

struct Color3f
{
	float	r;
	float	g;
	float	b;
	Color3f() : r(0.0f), g(0.0f), b(0.0f) {} 
	Color3f( float _r, float _g, float _b ) : r(_r), g(_g), b(_b) {} 
};

struct Index3w
{
	unsigned short i[3];
};

struct Index3i
{
	int		i[3];
};

struct Triangle
{
	Index3i	index;
};

struct TriangleWithID
{
	int		ID;
	Index3i	index;
};

struct Material
{
	Color3f	ambient;
	Color3f	diffuse;
	Color3f	specular;
	Color3f	emissive;
	float	power;
	float	opacity;
	string	strMapDiffuse;
	string	strMapSpecular;
	string	strMapBump;
	string	strMapDisplace;
};

#endif // _ZPREDEFINES_H_