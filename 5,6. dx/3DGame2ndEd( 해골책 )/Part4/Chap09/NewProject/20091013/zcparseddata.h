#ifndef _ZCPARSEDDATA_H_
#define _ZCPARSEDDATA_H_

#include "define.h"
#include "zcmesh.h"
#include "ZMaterialMgr.h"

/// XML������ �Ľ��� ��� Ŭ����
class ZCParsedData
{
public:
	Info					m_info;				/// �� ���Ͽ� ���� �������� ����
	Camera					m_camera;
	std::vector<ZTMaterial>	m_materials;		/// �����迭
	std::list<ZCMesh*>		m_meshList;			/// �޽�(���) ����Ʈ
public:
	ZCParsedData() {}
	~ZCParsedData() 
	{ 
		stl_wipe_vector( m_materials );
		stl_wipe( m_meshList );
	}
};

#endif // _ZCPARSEDDATA_H_