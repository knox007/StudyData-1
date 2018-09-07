#include "stdafx.h"
#include "PRCommonFunc.h"

//--------------------------------------------------------------------------------
HRESULT devVtxLock( PRDXVTXBUFF9 pVtx, UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags )
{
	return pVtx->Lock( OffsetToLock, SizeToLock, ppbData, Flags );

}//	devVtxLock
//--------------------------------------------------------------------------------
HRESULT devIdxLock( PRDXIDXBUFF9 pIdx, UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags)
{
	return pIdx->Lock( OffsetToLock, SizeToLock, ppbData, Flags );

}//	devIdxLock
//--------------------------------------------------------------------------------
HRESULT devVtxUnlock( PRDXVTXBUFF9 pVtx )
{
	return pVtx->Unlock();

}//	devVtxUnlock
//--------------------------------------------------------------------------------
HRESULT devIdxUnlock( PRDXIDXBUFF9 pIdx )
{
	return pIdx->Unlock();

}//	devIdxUnlock
//--------------------------------------------------------------------------------
HRESULT	devSetFVF( PRLPD3DDEV9 pDev, DWORD dwFVF )
{
	return pDev->SetFVF( dwFVF );

}//	devSetFVF
//--------------------------------------------------------------------------------
HRESULT devSetStreamSrc( PRLPD3DDEV9 pDev, UINT unStreamNum, PRDXVTXBUFF9 pVB, UINT unOffsetInBytes, UINT unStride )
{
	return pDev->SetStreamSource( unStreamNum, pVB, unOffsetInBytes, unStride );

}//	devSetStreamSrc
//--------------------------------------------------------------------------------
HRESULT devSetIdx( PRLPD3DDEV9 pDev, PRDXIDXBUFF9 pIB )
{
	return pDev->SetIndices( pIB );

}//	devSetIdx
//--------------------------------------------------------------------------------
HRESULT	devCreateVtxBuff( PRLPD3DDEV9 pDev, UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle )
{
	return pDev->CreateVertexBuffer( Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle );

}//	devCreateVtxBuff
//--------------------------------------------------------------------------------
HRESULT	devCreateIdxBuff( PRLPD3DDEV9 pDev, UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle)
{
	return pDev->CreateIndexBuffer( Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle );

}//	devCreateIdxBuff
//--------------------------------------------------------------------------------

//	EOF