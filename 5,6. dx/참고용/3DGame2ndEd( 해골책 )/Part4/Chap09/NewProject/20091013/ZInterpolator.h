#pragma once


class ZInterpolator
{
protected:
	enum INTERPOL { INTP_LINEAR, INTP_SPLINE, INTP_HERMIT };	// ����� LINEAR�� ����

public:
	ZInterpolator(void);
	virtual ~ZInterpolator(void);

	inline float _GetAlpha( float v1, float v2, float value )
	{
		return ( (value-v1) / (v2-v1) );
	}

	_GetValue( float value )
};
