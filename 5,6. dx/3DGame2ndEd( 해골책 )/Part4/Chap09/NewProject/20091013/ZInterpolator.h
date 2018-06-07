#pragma once


class ZInterpolator
{
protected:
	enum INTERPOL { INTP_LINEAR, INTP_SPLINE, INTP_HERMIT };	// 현재는 LINEAR만 지원

public:
	ZInterpolator(void);
	virtual ~ZInterpolator(void);

	inline float _GetAlpha( float v1, float v2, float value )
	{
		return ( (value-v1) / (v2-v1) );
	}

	_GetValue( float value )
};
