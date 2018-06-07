#include "stdafx.h"
#include "PRCommonFunc.h"


//-----------------------------------------------------------------------------
// Vector
//-----------------------------------------------------------------------------
D3DXVECTOR3*	PRDVec3Norm( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV )
{
	return D3DXVec3Normalize( pOut, pV );

}//	PRDVec3Norm
//-----------------------------------------------------------------------------
D3DXVECTOR4*	PRDVec4Trsfrm( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV, CONST D3DXMATRIX *pM )
{
	return D3DXVec4Transform( pOut, pV, pM );

}//	PRDVec4Transform
//-----------------------------------------------------------------------------
//	Matrix
//-----------------------------------------------------------------------------
PRDXMat*	PRDXMatInit( PRDXMat *pOut )
{
	return D3DXMatrixIdentity( pOut );
}
//-----------------------------------------------------------------------------
PRDXMat*	PRDXMatTranslation( PRDXMat*	pOut, FLOAT x, FLOAT y, FLOAT z )
{
	return D3DXMatrixTranslation( pOut, x, y, z );
}
//-----------------------------------------------------------------------------
PRDXMat*	PRDXMatRotX( PRDXMat*	pOut, FLOAT Angle )
{
	return D3DXMatrixRotationX( pOut, Angle );
}
//-----------------------------------------------------------------------------
PRDXMat*	PRDXMatRotY( PRDXMat*	pOut, FLOAT Angle )
{
	return D3DXMatrixRotationY( pOut, Angle );
}
//-----------------------------------------------------------------------------
PRDXMat*	PRDXMatRotZ( PRDXMat *pOut, FLOAT Angle )
{
	return D3DXMatrixRotationZ( pOut, Angle );
}
//-----------------------------------------------------------------------------
D3DXMATRIX*	PRDXMatInv( PRDXMat *pOut, FLOAT *pDeterminant, CONST PRDXMat *pM )
{
	return D3DXMatrixInverse( pOut, pDeterminant, pM );
}
//-----------------------------------------------------------------------------
D3DXMATRIX*	PRDXMatTranspose( D3DXMATRIX *pOut, CONST D3DXMATRIX *pM )
{
	return D3DXMatrixTranspose( pOut, pM );
}
//-----------------------------------------------------------------------------
//	EOF