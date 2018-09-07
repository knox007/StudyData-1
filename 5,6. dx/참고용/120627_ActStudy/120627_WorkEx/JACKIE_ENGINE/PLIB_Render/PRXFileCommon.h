#ifndef _PRXFILECOMMON_H_
#define _PRXFILECOMMON_H_
#pragma once

#include "PRCommonTypeDef.h"

struct sPRDXXMESHCONTAINEREx	:	public D3DXMESHCONTAINER
{ 
	PRDXTXTRBUFF9	*_ppTexturesEx;
	D3DMATERIAL9	*_pMtrlsEx;

	//	��Ų �޽� ����
	ID3DXMesh			*_pSkinMeshEx;
	D3DXMATRIX			*_pmatBoneOffsetsEx;		//	�� �Ѱ��� ����� ����.
	D3DXMATRIX			**_ppmatFrameCombinedPtrEx;	//	������ ��� ������ �迭.
};


struct sPRDXXFRAMEEx			:	public	D3DXFRAME
{	
	D3DXMATRIX	_matCombinedTransformEx;
};

#endif	//	_PRXFILECOMMON_H_