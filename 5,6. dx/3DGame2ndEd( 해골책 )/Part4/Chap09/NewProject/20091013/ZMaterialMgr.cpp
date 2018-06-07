#include ".\zmaterialmgr.h"
#include ".\ZSceneMgr.h"
#include "ZFLog.h"

//extern class ZSceneMgr*	g_pSceneMgr;

ZMaterialMgr::ZMaterialMgr(void)
{
	m_fFrame = 0.0f;
	m_fFrameRate = 30.0f;
}

ZMaterialMgr::ZMaterialMgr( LPDIRECT3DDEVICE9 pDev, float fFrameRate )
{
	m_pDev			= pDev;
	m_fFrame		= 0.0f;
	m_fFrameRate	= fFrameRate;
}

ZMaterialMgr::~ZMaterialMgr(void)
{
	stl_wipe_vector( m_pMaterials );
}

void ZMaterialMgr::_SetMaterialFrame( int nID )
{
	m_pMaterials[nID]->shaderType.SetFrame( m_fFrame );
	m_pMaterials[nID]->wire.SetFrame( m_fFrame );
	m_pMaterials[nID]->twoSided.SetFrame( m_fFrame );
	m_pMaterials[nID]->faceMap.SetFrame( m_fFrame );
	m_pMaterials[nID]->faceted.SetFrame( m_fFrame );
	m_pMaterials[nID]->shaderByName.SetFrame( m_fFrame );
	m_pMaterials[nID]->opacityType.SetFrame( m_fFrame );
	m_pMaterials[nID]->opacity.SetFrame( m_fFrame );
	m_pMaterials[nID]->opacityFallOffType.SetFrame( m_fFrame );
	m_pMaterials[nID]->opacityFallOff.SetFrame( m_fFrame );
	m_pMaterials[nID]->ior.SetFrame( m_fFrame );
	m_pMaterials[nID]->wireSize.SetFrame( m_fFrame );
	m_pMaterials[nID]->wireUnits.SetFrame( m_fFrame );
	m_pMaterials[nID]->applyReflectionDimming.SetFrame( m_fFrame );
	m_pMaterials[nID]->dimLevel.SetFrame( m_fFrame );
	m_pMaterials[nID]->reflectionLevel.SetFrame( m_fFrame );
	m_pMaterials[nID]->sampler.SetFrame( m_fFrame );
	m_pMaterials[nID]->samplerEnable.SetFrame( m_fFrame );
	m_pMaterials[nID]->samplerAdaptThreshold.SetFrame( m_fFrame );
	m_pMaterials[nID]->samplerAdaptOn.SetFrame( m_fFrame );
	m_pMaterials[nID]->samplerAdvancedOptions.SetFrame( m_fFrame );
	m_pMaterials[nID]->samplerByName.SetFrame( m_fFrame );
	m_pMaterials[nID]->UserParam0.SetFrame( m_fFrame );
	m_pMaterials[nID]->UserParam1.SetFrame( m_fFrame );
	m_pMaterials[nID]->samplerUseGlobal.SetFrame( m_fFrame );
	m_pMaterials[nID]->subSampleTextureOn.SetFrame( m_fFrame );

	int i, iSize;
	iSize = m_pMaterials[nID]->map.size();
	for( i = 0 ; i < iSize ; i++ )
	{	// map
		m_pMaterials[nID]->map[i].enabled.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].amount.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].clipu.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].clipv.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].clipw.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].cliph.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].jitter.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].useJitter.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].apply.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].cropPlace.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].filtering.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].monoOutput.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].rgbOutput.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].alphaSource.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].preMultAlpha.SetFrame( m_fFrame );

		{	// map coords
			m_pMaterials[nID]->map[i].coords.blur.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.mapping.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.mapChannel.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.mappingType.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.UVW_Type.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.U_Mirror.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.V_Mirror.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.U_Tile.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.V_Tile.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.showMapOnBack.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.Noise_On.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.Noise_Animate.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.phase.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.U_Offset.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.V_Offset.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.U_Tiling.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.V_Tiling.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.U_Angle.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.V_Angle.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.W_Angle.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.Noise_Amount.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.Noise_Size.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.Noise_Levels.SetFrame( m_fFrame );
			m_pMaterials[nID]->map[i].coords.Blur_Offset.SetFrame( m_fFrame );
		}

		m_pMaterials[nID]->map[i].fileName.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].startTime.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].playBackRate.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].endCondition.SetFrame( m_fFrame );
		m_pMaterials[nID]->map[i].tieTimeToMatIDs.SetFrame( m_fFrame );
	}

	m_pMaterials[nID]->bounce.SetFrame( m_fFrame );
	m_pMaterials[nID]->staticFriction.SetFrame( m_fFrame );
	m_pMaterials[nID]->slidingFriction.SetFrame( m_fFrame );
	m_pMaterials[nID]->ambient.SetFrame( m_fFrame );
	m_pMaterials[nID]->diffuse.SetFrame( m_fFrame );
	m_pMaterials[nID]->specular.SetFrame( m_fFrame );
	m_pMaterials[nID]->adTextureLock.SetFrame( m_fFrame );
	m_pMaterials[nID]->adLock.SetFrame( m_fFrame );
	m_pMaterials[nID]->dsLock.SetFrame( m_fFrame );
	m_pMaterials[nID]->useSelfIllumColor.SetFrame( m_fFrame );
	m_pMaterials[nID]->selfIllumAmount.SetFrame( m_fFrame );
	m_pMaterials[nID]->selfIllumColor.SetFrame( m_fFrame );
	m_pMaterials[nID]->specularLevel.SetFrame( m_fFrame );
	m_pMaterials[nID]->glossiness.SetFrame( m_fFrame );
	m_pMaterials[nID]->soften.SetFrame( m_fFrame );
}

BOOL ZMaterialMgr::AddMaterial( ZTMaterial* pMat )
{
	m_pMaterials.push_back( pMat );
	return TRUE; 
}

BOOL ZMaterialMgr::ApplyMaterial( int nID )
{
	int				i, n;
	float			a;
	D3DCOLORVALUE	c;
	D3DMATERIAL9	d3dmaterial;
	D3DXMATRIXA16	matTexture;
	ZTKeyBool		keyBool;
	ZTKeyInt		keyInt;
	ZTKeyFloat		keyFloat;
	ZTKeyPoint3		keyPoint3;
	ZTKeyString		keyString;

	ZeroMemory( &d3dmaterial, sizeof d3dmaterial );

	{// 기본 D3D material적용
		
		_SetMaterialFrame( nID );

		// opacity
		m_pMaterials[nID]->opacity.GetKey( (ZTKeyBase*)&keyFloat );
		a = keyFloat.value / 100.0f;
		c.a = a;

		// ambient
		m_pMaterials[nID]->ambient.GetKey( (ZTKeyBase*)&keyPoint3 );
		c.r = keyPoint3.value.x; c.g = keyPoint3.value.y; c.b = keyPoint3.value.z;
		d3dmaterial.Ambient = c;

		// diffuse
		m_pMaterials[nID]->diffuse.GetKey( (ZTKeyBase*)&keyPoint3 );
		c.r = keyPoint3.value.x; c.g = keyPoint3.value.y; c.b = keyPoint3.value.z;
		d3dmaterial.Diffuse = c;

		// specular
		m_pMaterials[nID]->specular.GetKey( (ZTKeyBase*)&keyPoint3 );
		c.r = keyPoint3.value.x; c.g = keyPoint3.value.y; c.b = keyPoint3.value.z;
		d3dmaterial.Specular = c;

		// emissive
		m_pMaterials[nID]->useSelfIllumColor.GetKey( (ZTKeyBase*)&keyBool );
		if( keyBool.value )
		{
			m_pMaterials[nID]->selfIllumColor.GetKey( (ZTKeyBase*)&keyPoint3 );
			c.r = keyPoint3.value.x; c.g = keyPoint3.value.y; c.b = keyPoint3.value.z;
			d3dmaterial.Emissive = c;
		}

		// specular power
		m_pMaterials[nID]->specularLevel.GetKey( (ZTKeyBase*)&keyFloat );
		d3dmaterial.Power = keyFloat.value;

		m_pDev->SetMaterial( &d3dmaterial );
		m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		m_pDev->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pDev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	}

	n = m_pMaterials[nID]->map.size();
	D3DXMatrixIdentity( &matTexture );

	for( i = 0 ; i < 8 ; i++ )
	{
		m_pDev->SetTransform( D3DTRANSFORMSTATETYPE(D3DTS_TEXTURE0 + i), &matTexture );
		m_pDev->SetTextureStageState( i, D3DTSS_TEXCOORDINDEX, 0 );		// i번 텍스처 : 0번 텍스처 인덱스 사용
		m_pDev->SetTexture( i, NULL );
	}

	for( i = 0 ; i < n ; i++ )
	{
		m_pMaterials[nID]->map[i].enabled.GetKey( (ZTKeyBase*)&keyBool );
		if( m_pMaterials[nID]->map[i].fileName.HasKey() && keyBool.value )
		{
			// 텍스처 세팅
			m_pMaterials[nID]->map[i].fileName.GetKey( (ZTKeyBase*)&keyString );
			m_pDev->SetTexture( i, g_pSceneMgr->GetTextureMgr()->GetItem( keyString.value.c_str() ) );

			// 텍스처 행렬 세팅
			m_pMaterials[nID]->map[i].coords.U_Offset.GetKey( (ZTKeyBase*)&keyFloat );
			matTexture._31 = keyFloat.value;
			
//			g_pLog->Log( "[%d]->map[%d].U_Offset=%f", nID, i, keyFloat.value );

			m_pMaterials[nID]->map[i].coords.V_Offset.GetKey( (ZTKeyBase*)&keyFloat );
			matTexture._32 = keyFloat.value;

			m_pMaterials[nID]->map[i].coords.U_Tiling.GetKey( (ZTKeyBase*)&keyFloat );
			matTexture._11 = keyFloat.value;

			m_pMaterials[nID]->map[i].coords.V_Tiling.GetKey( (ZTKeyBase*)&keyFloat );
			matTexture._22 = keyFloat.value;

			m_pDev->SetTransform( D3DTRANSFORMSTATETYPE(D3DTS_TEXTURE0 + i), &matTexture );
			// i번 스테이지의 텍스처는 텍스처변환 행렬(D3DTS_TEXTURE0)과 곱해지도록 한다.
			m_pDev->SetTextureStageState( i, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2 );


		}

		m_pMaterials[nID]->opacity.GetKey( (ZTKeyBase*)&keyFloat );
		DWORD c = D3DCOLOR_ARGB( (int)(keyFloat.value * 2.55f), 0xff, 0xff, 0xff );
		m_pDev->SetRenderState( D3DRS_TEXTUREFACTOR, c );
	}

	return TRUE;
}
