// Interface for the CMcCamera class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _McCamera_H_
#define _McCamera_H_

class CMcCamera
{
protected:
	LPDIRECT3DDEVICE9	m_pDev;
	
	D3DXMATRIX		m_mtViw;													// View Matrix
	D3DXMATRIX		m_mtPrj;													// Projection Matrix
	

	// For View Matrix
	D3DXVECTOR3		m_vcEye;													// Camera position
	D3DXVECTOR3		m_vcLook;													// Look vector
	D3DXVECTOR3		m_vcUp;														// up vector

	// For Projection Matrix
	FLOAT			m_fFov;														// Field of View
	FLOAT			m_fAsp;														// Aspect
	FLOAT			m_fNr;														// Near
	FLOAT			m_fFr;														// Far

	D3DXVECTOR3		m_vcBasis;			// Look Pos
	FLOAT			m_fEpslnY;			// Epsilon Y
	FLOAT			m_fGap;				// Distance Between Camera and Basis
	
public:
	CMcCamera();
	virtual ~CMcCamera();

	INT		Create(LPDIRECT3DDEVICE9 pDev);
	INT		FrameMove();

public:
	D3DXMATRIX	GetMatrixView()			{	return m_mtViw;		}
	D3DXMATRIX	GetMatrixProj()			{	return m_mtPrj;		}
	
	void		SetParamView(	D3DXVECTOR3 vcEye
							,	D3DXVECTOR3 vcLook
							,	D3DXVECTOR3 vcUp)
	{
		m_vcEye		= vcEye;
		m_vcLook	= vcLook;
		m_vcUp		= vcUp;
	}

	void		SetParamProjection(FLOAT fFov,FLOAT fAsp,FLOAT fNear,FLOAT fFar)
	{
		m_fFov	= fFov;
		m_fAsp	= fAsp;
		m_fNr	= fNear;
		m_fFr	= fFar;
	}
	

	void		UpdateViewProj();

	void		SetBasis(D3DXVECTOR3 _vcP)	{	m_vcBasis =_vcP;	}
	D3DXVECTOR3	GetBasis()					{	return m_vcBasis;	}

	void		SetEpsilonY(FLOAT _fY)		{	m_fEpslnY =_fY;		}
	FLOAT		GetEpsilonY()				{	return m_fEpslnY;	}

	void		SetGap(FLOAT _fG)			{	m_fGap =_fG;		}
	FLOAT		GetGap()					{	return m_fGap;		}

protected:
	void		MoveSideward(FLOAT	fSpeed);
	void		MoveForward	(FLOAT	fSpeed, FLOAT fY=0);
	void		Rotate(const D3DXVECTOR3* vcDelta, float fSpeed);
};

#endif
