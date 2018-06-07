#ifndef _ZMATERIALMGR_H_
#define _ZMATERIALMGR_H_

#include <vector>
#include "ZCtrlBezierFloat.h"
#include "ZCtrlString.h"
#include "ZCtrlBool.h"
#include "ZCtrlInt.h"
#include "ZCtrlPoint3.h"
#include "ZCtrlPoint4.h"
#include "ZCtrlQuat.h"

struct ZTMaterial_Map_Coord
{
	ZCtrlBezierFloat	blur;
	ZCtrlInt			mapping;
	ZCtrlInt			mapChannel;
	ZCtrlInt			mappingType;
	ZCtrlInt			UVW_Type;
	ZCtrlBool			U_Mirror;
	ZCtrlBool			V_Mirror;
	ZCtrlBool			U_Tile;
	ZCtrlBool			V_Tile;
	ZCtrlBool			showMapOnBack;
	ZCtrlBool			Noise_On;
	ZCtrlBool			Noise_Animate;
	ZCtrlBezierFloat	phase;
	ZCtrlBezierFloat	U_Offset;
	ZCtrlBezierFloat	V_Offset;
	ZCtrlBezierFloat	U_Tiling;
	ZCtrlBezierFloat	V_Tiling;
	ZCtrlBezierFloat	U_Angle;
	ZCtrlBezierFloat	V_Angle;
	ZCtrlBezierFloat	W_Angle;
	ZCtrlBezierFloat	Noise_Amount;
	ZCtrlBezierFloat	Noise_Size;
	ZCtrlInt			Noise_Levels;
	ZCtrlBezierFloat	Blur_Offset;
};

struct ZTMaterial_Map
{
	ZCtrlBool			enabled;
	ZCtrlBezierFloat	amount;
	ZCtrlBezierFloat	clipu;
	ZCtrlBezierFloat	clipv;
	ZCtrlBezierFloat	clipw;
	ZCtrlBezierFloat	cliph;
	ZCtrlBezierFloat	jitter;
	ZCtrlBool			useJitter;
	ZCtrlBool			apply;
	ZCtrlInt			cropPlace;
	ZCtrlInt			filtering;
	ZCtrlInt			monoOutput;
	ZCtrlInt			rgbOutput;
	ZCtrlInt			alphaSource;
	ZCtrlBool			preMultAlpha;

	ZTMaterial_Map_Coord	coords;

	ZCtrlString			fileName;
	ZCtrlBezierFloat	startTime;
	ZCtrlBezierFloat	playBackRate;
	ZCtrlInt			endCondition;
	ZCtrlBool			tieTimeToMatIDs;
};

struct ZTMaterial
{
	ZCtrlInt			shaderType;
	ZCtrlBool			wire;
	ZCtrlBool			twoSided;
	ZCtrlBool			faceMap;
	ZCtrlBool			faceted;
	ZCtrlString			shaderByName;
	ZCtrlInt			opacityType;
	ZCtrlBezierFloat	opacity;
	ZCtrlInt			opacityFallOffType;
	ZCtrlBezierFloat	opacityFallOff;
	ZCtrlBezierFloat	ior;
	ZCtrlBezierFloat	wireSize;
	ZCtrlInt			wireUnits;
	ZCtrlBool			applyReflectionDimming;
	ZCtrlBezierFloat	dimLevel;
	ZCtrlBezierFloat	reflectionLevel;
	ZCtrlInt			sampler;
	ZCtrlBool			samplerEnable;
	ZCtrlBezierFloat	samplerAdaptThreshold;
	ZCtrlBool			samplerAdaptOn;
	ZCtrlBool			samplerAdvancedOptions;
	ZCtrlString			samplerByName;
	ZCtrlBezierFloat	UserParam0;
	ZCtrlBezierFloat	UserParam1;
	ZCtrlBool			samplerUseGlobal;
	ZCtrlBool			subSampleTextureOn;

	std::vector<ZTMaterial_Map>	map;

	ZCtrlBezierFloat	bounce;
	ZCtrlBezierFloat	staticFriction;
	ZCtrlBezierFloat	slidingFriction;
	ZCtrlPoint3			ambient;
	ZCtrlPoint3			diffuse;
	ZCtrlPoint3			specular;
	ZCtrlBool			adTextureLock;
	ZCtrlBool			adLock;
	ZCtrlBool			dsLock;
	ZCtrlBool			useSelfIllumColor;
	ZCtrlBezierFloat	selfIllumAmount;
	ZCtrlPoint3			selfIllumColor;
	ZCtrlBezierFloat	specularLevel;
	ZCtrlBezierFloat	glossiness;
	ZCtrlBezierFloat	soften;
};

class ZMaterialMgr
{
public:
//	enum CTRLTYPE { CTRLTYPE_BASE, CTRLTYPE_BOOL, CTRLTYPE_INT, CTRLTYPE_FLOAT, CTRLTYPE_POINT3, CTRLTYPE_POINT4, CTRLTYPE_QUAT };
	LPDIRECT3DDEVICE9				m_pDev;

protected:
	float							m_fFrame;
	float							m_fFrameRate;
	std::vector<ZTMaterial*>		m_pMaterials;

	void	_SetMaterialFrame( int nID );

public:
	ZMaterialMgr(void);
	ZMaterialMgr( LPDIRECT3DDEVICE9 pDev, float fFrameRate );
	~ZMaterialMgr(void);

	BOOL						AddMaterial( ZTMaterial* pMat );
	std::vector<ZTMaterial*>&	GetMaterials() { return m_pMaterials; }

	void	SetFrameRate( float f ) { m_fFrameRate = f; }
	void	SetTime( float fTime )	{ m_fFrame = fTime * m_fFrameRate; }
	void	SetFrame( float fFrame ) { m_fFrame = fFrame; }
	BOOL	ApplyMaterial( int nID );
};

#endif // _ZMATERIALMGR_H_