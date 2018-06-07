#ifndef _ZPARSEDDATA_H_
#define _ZPARSEDDATA_H_

#include "ZPreDefines.h"
#include "ZNode.h"

/// XML������ �Ľ��� ��� Ŭ����
class ZParsedData
{
public:
	SceneInfo				m_info;				/// �� ���Ͽ� ���� �������� ����
	vector<Material>		m_materialTable;	/// �����迭
	list<ZNode*>			m_nodeList;			/// ��� ����Ʈ
	vector<ZGeometry*>		m_geomList;
	vector<ZLight*>			m_lightList;
	ZCamera*				m_pCamera;
public:
	ZParsedData() {}
	~ZParsedData() 
	{ 
		stl_wipe_vector( m_materialTable );
		stl_wipe( m_nodeList );
		stl_wipe_vector( m_geomList );
		stl_wipe_vector( m_lightList );
		S_DEL( m_pCamera );
	}
};

#endif // _ZPARSEDDATA_H_


