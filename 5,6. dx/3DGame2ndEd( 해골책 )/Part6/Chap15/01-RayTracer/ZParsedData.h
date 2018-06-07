#ifndef _ZPARSEDDATA_H_
#define _ZPARSEDDATA_H_

#include "ZPreDefines.h"
#include "ZNode.h"

/// XML파일을 파싱한 결과 클래스
class ZParsedData
{
public:
	SceneInfo				m_info;				/// 이 파일에 관한 여러가지 정보
	vector<Material>		m_materialTable;	/// 재질배열
	list<ZNode*>			m_nodeList;			/// 노드 리스트
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


