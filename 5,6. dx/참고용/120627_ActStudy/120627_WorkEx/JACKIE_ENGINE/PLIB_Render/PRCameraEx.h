#pragma once
#ifndef	_PRACAMERAEX_H_
#define _PRACAMERAEX_H_


class CPRCameraEx
{
public:
	//@	ī�޶� ���.
	enum	eCAMMAT_
	{
		eCAMMAT_WORLD,
		eCAMMAT_VIEW,
		eCAMMAT_PROJ,
		eCAMMAT_BILLBOARD,
		eCAMMAT_MAX
	};

	//@	ī�޶� ����.
	enum	eCAMVEC_
	{
		eCAMVEC_EYE,
		eCAMVEC_LOOKAT,
		eCAMVEC_UP,
		eCAMVEC_DIR,
		eCAMVEC_CROSS,
		eCAMVEC_DEFEYE,
		eCAMVEC_DEFLOOKAT,
		eCAMVEC_MAX
	};

	//@	ī�޶� ȸ��.
	enum	eROTVAL_
	{
		eROTVAL_YAW,
		eROTVAL_PITCH,
		eROTVAL_MAX
	};

	//@	ī�޶� ����.
	enum	eCAMSPEED_
	{
		eCAMSPEED_MOVE,
		eCAMSPEED_ROTATE,
		eCAMSPEED_BOOSTER,
		eCAMSPEED_MAX
	};

	//@	�������� ���.
	enum	ePROJECTION_
	{
		ePROJECTION_FOV,
		ePROJECTION_ASPECT,
		ePROJECTION_NEAR,
		ePROJECTION_FAR,
		ePROJECTION_MAX
	};
	 
	CPRCameraEx(void)			{ InitMember(); }
	virtual ~CPRCameraEx(void)	{ ReleaseMember(); }

	 
private:
	void	InitMember();
	void	ReleaseMember();

	LPDIRECT3DDEVICE9	m_pDev;
	 
};


#endif
//	_PRACAMERAEX_H_