#ifndef _PRXFILECOMMON_H_
#define _PRXFILECOMMON_H_
#pragma once

#include "PRCommonTypeDef.h"

struct sPRDXXMESHCONTAINEREx	:	public D3DXMESHCONTAINER
{ 
	PRDXTXTRBUFF9	*_ppTexturesEx;
	D3DMATERIAL9	*_pMtrlsEx;

	//	스킨 메쉬 변수
	ID3DXMesh			*_pSkinMeshEx;
	D3DXMATRIX			*_pmatBoneOffsetsEx;		//	본 한개당 본행렬 편차.
	D3DXMATRIX			**_ppmatFrameCombinedPtrEx;	//	프레임 행렬 포인터 배열.
};


struct sPRDXXFRAMEEx			:	public	D3DXFRAME
{	
	D3DXMATRIX	_matCombinedTransformEx;
};

#endif	//	_PRXFILECOMMON_H_