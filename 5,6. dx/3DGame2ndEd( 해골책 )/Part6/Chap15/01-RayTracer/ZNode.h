#ifndef _ZNODE_H_
#define _ZNODE_H_

#include "ZPreDefines.h"
#include "ZFLog.h"

#define NODE_CAMERA_CLASS		"Targetcamera"
#define NODE_CAMERATARGET_CLASS	"Targetobject"
#define NODE_LIGHT_CLASS		"Omnilight"
#define NODE_MESH_CLASS			"Editable_mesh"
#define NODE_SPHERE_CLASS		"Sphere"
#define NODE_CYLINDER_CLASS		"Cylinder"
#define NODE_
/** \brief Bounding Sphere structure
 *
 */
typedef struct tagBSphere
{
	Vector3f	vCenter;			/// center of sphere
	float		fRadius;			/// radius of sphere
} BSphere;

/** \brief Bounding Box structure
 *
 */
typedef struct tagBBox
{
	Vector3f	vMax;				/// �ٿ�� �ڽ��� �ִ밪(max)
	Vector3f	vMin;				/// �ٿ�� �ڽ��� �ּҰ�(min)
} BBox;

struct ZRay
{
	Vector3f	vPos;
	Vector3f	vDir;
	ZRay() : vPos(0,0,0), vDir(0,0,0) {}
	ZRay( Vector3f v0, Vector3f v1 ) { vPos = v0; vDir = v1; }
};

struct SceneInfo
{
	string			strFilename;
	int				nObjectCount;
	int				nGeometryCount;
	vector<string>	strObjectNameTable;
	~SceneInfo()
	{ 
		stl_wipe_vector( strObjectNameTable );
	}
};

/** \brief 3D������Ʈ���� baseŬ����
 *
 */
class ZNode
{
public:
	string		m_strNodeType;			/// ����� ����(string)
	int			m_nNodeType;			/// ����� ����(ID)
	int			m_nObjectID;			/// ������Ʈ ID
	Mat4x4		m_tmLocal;				/// Local TM ���
	Mat4x4		m_tmWorld;				/// World TM ���
public:
	enum NODETYPE { NODE, LIGHT, CAMERA, CAMERATARGET, MESH, SPHERE, CYLINDER };
public:
			ZNode() : m_nObjectID( -1 ) {}
	virtual	~ZNode() {}
			Vector3f	GetPos() { return Vector3f( m_tmWorld._41, m_tmWorld._42, m_tmWorld._43 ); }
};

/** \brief ���� Ŭ����
 *  not yet implemented
 *
 */
class ZLight : public ZNode
{
public:
	Vector3f	m_pos;
	Color4f		m_color;
public:
	ZLight() {}
	virtual ~ZLight() {}
};

/** \brief ī�޶� Ŭ����
 *  not yet implemented
 *
 */
class ZCamera: public ZNode
{
public:
	Vector3f	m_vFrom;
	Vector3f	m_vTo;
	Vector3f	m_vUp;
	Mat4x4		m_matView;		/// view ���
	Mat4x4		m_matProj;		/// proj ���
public:
	void GenerateMatrix()
	{
		D3DXMatrixLookAtLH( &m_matView, &m_vFrom, &m_vTo, &m_vUp );
		D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
	}
	ZCamera() {}
	virtual ~ZCamera() {}
};


/** \brief base class of Geometric objects
 *
 */
class ZGeometry : public ZNode
{
public:
	BBox		m_bbox;			/// bounding box
	BSphere		m_bsphere;		/// bounding sphare
	int			m_nMaterialID;
public:
			Vector3f	GetCenter() { return m_bsphere.vCenter; }
			float		GetRadius() { return m_bsphere.fRadius; }
			int			GetMaterialID() { return m_nMaterialID; }
	virtual	void		CalcBounder() {}
	virtual	bool		GetIntersectPos( ZRay* ray, float& t0, float& t1 ) { return false; }
	virtual	bool		IsIntersect( ZRay* ray ) { return false; }
	virtual Color3f		GetColor(  ZLight* pLight, ZRay* ray ) { return Color3f( 0, 0, 0 ); }
			ZGeometry() {}
	virtual ~ZGeometry() {}
};

/** \brief ��(sphere) Ŭ����
 *
 */
class ZSphere : public ZGeometry
{
public:
	float	m_fRadius;
public:
	virtual void CalcBounder()
	{
		m_bsphere.vCenter = Vector3f( m_tmWorld._41, m_tmWorld._42, m_tmWorld._43 ); 
		m_bsphere.fRadius = m_fRadius;
		m_bbox.vMax = Vector3f( m_bsphere.vCenter.x + m_fRadius, m_bsphere.vCenter.y + m_fRadius, m_bsphere.vCenter.z + m_fRadius );
		m_bbox.vMin = Vector3f( m_bsphere.vCenter.x - m_fRadius, m_bsphere.vCenter.y - m_fRadius, m_bsphere.vCenter.z - m_fRadius );
	}

	virtual	bool GetIntersectPos( ZRay* ray, float& t0, float& t1 )
	{
		Mat4x4		tmInv;
		Vector3f	q, v, c, q_minus_c;
		float		A, B, C, D;	// Ax^2 + 2Bx + C = 0

		q = ray->vPos;
		v = ray->vDir;
		c = GetPos();
		q_minus_c = q - c;

		A = D3DXVec3Dot( &v, &v );
		B = D3DXVec3Dot( &v, &q_minus_c );
		C = D3DXVec3Dot( &q_minus_c, &q_minus_c ) - m_fRadius * m_fRadius;

		D = B * B - A * C;			// ���� �Ǻ��� D=B^2-AC
//		g_pLog->Log( "D:%f", D );
		if( D < 0 ) 
			return false; // ����̹Ƿ� ������ ����

		t0 = -( B + sqrt( D ) ) / A;					// ���� ��
		t1 = -( B - sqrt( D ) ) / A;					// ���� ��
		if(t0<0 && t1<0) return false;
		return true;
	}

	virtual	bool IsIntersect( ZRay* ray )
	{
		float	t0, t1;
		return GetIntersectPos( ray, t0, t1 );
	}

	virtual Color3f GetColor(  ZLight* pLight, ZRay* ray )
	{
		float	t, t0, t1;
		Vector3f	vLight;
		Vector3f	vPos;
		Color3f		c;
		c = Color3f( 1, 1, 0 );
		if( !GetIntersectPos( ray, t0, t1 ) ) return Color3f( 0, 0, 0 );

		if( pLight ) vLight = pLight->GetPos();
		t = max( t0, t1 );
		vPos = ray->vPos + t * ray->vDir;
		vLight = vLight - vPos;
		vPos = vPos - GetPos();
		D3DXVec3Normalize( &vPos, &vPos );
		D3DXVec3Normalize( &vLight, &vLight );
		float f = D3DXVec3Dot( &vPos, &vLight );
		f = max( 0, f );
		c.r *= f;
		c.g *= f;
		c.b *= f;

		return c;
	}

	ZSphere() {}
	virtual ~ZSphere() {}
};

/** \brief �Ǹ��� Ŭ����, ���������� ����ϸ� �ȵ�
 *
 */
class ZCylinder : public ZGeometry
{
public:
	float	m_fRadius;
	float	m_fHeight;
public:
	virtual void CalcBounder() {}
	virtual	bool		GetIntersectPos( ZRay* ray, float& t0, float& t1 ) { return false; }
	virtual	bool		IsIntersect( ZRay* ray ) { return false; }
	virtual Color3f		GetColor(  ZLight* pLight, ZRay* ray ) { return Color3f( 0, 0, 0 ); }

	ZCylinder() {}
	virtual ~ZCylinder() {}
};

/** \brief �޽� Ŭ����
 *
 */
class ZMesh : public ZGeometry
{
public:
	vector<Vector3f>		m_vertex;				/// ������ ��ġ����
	vector<Vector3f>		m_normal;				/// ������ �������
	vector<Vector2f>		m_tvertex;				/// �ؽ��� ����
	vector<TriangleWithID>	m_triindex;				/// �ﰢ���� �ε���
	vector<Triangle>		m_texindex;				/// �ؽ����� �ε���
public:
	virtual void CalcBounder()
	{
		Vector3f	vMax = Vector3f( 0, 0, 0 );
		Vector3f	vMin = Vector3f( 0, 0, 0 );
		for( unsigned int i = 0 ; i < m_vertex.size() ; i++ )
		{
			if( m_vertex[i].x > vMax.x ) vMax.x = m_vertex[i].x;
			if( m_vertex[i].y > vMax.y ) vMax.y = m_vertex[i].y;
			if( m_vertex[i].z > vMax.z ) vMax.z = m_vertex[i].z;
			if( m_vertex[i].x < vMin.x ) vMin.x = m_vertex[i].x;
			if( m_vertex[i].y < vMin.y ) vMin.y = m_vertex[i].y;
			if( m_vertex[i].z < vMin.z ) vMin.z = m_vertex[i].z;
		}
		m_bbox.vMax = vMax;
		m_bbox.vMin = vMin;

		m_bsphere.vCenter = (vMax+vMin)/2;
		m_bsphere.fRadius = D3DXVec3Length( &(vMax - m_bsphere.vCenter) );
	}

	virtual	bool		GetIntersectPos( ZRay* ray, float& t0, float& t1 ) { return false; }
	virtual	bool		IsIntersect( ZRay* ray ) { return false; }
	virtual Color3f		GetColor(  ZLight* pLight, ZRay* ray ) { return Color3f( 0, 0, 0 ); }

	ZMesh() {}
	virtual ~ZMesh()
	{
		stl_wipe_vector( m_vertex );
		stl_wipe_vector( m_normal );
		stl_wipe_vector( m_tvertex );
		stl_wipe_vector( m_triindex );
		stl_wipe_vector( m_texindex );
	}
};

#endif // _ZNODE_H_