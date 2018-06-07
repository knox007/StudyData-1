#pragma once
#ifndef _PUTFRAMESKIP_H_
#define _PUTFRAMESKIP_H_


class CPUtFrameSkip
{
public:
	CPUtFrameSkip()		{ InitMembers(); }
	~CPUtFrameSkip()	{ }

	void	Init( float fFps );

	bool	Update( float fElapsed );

	bool	IsFrameSkip()	{ return (m_fTimer >= 0.0f); }

private:
	void	InitMembers()	{ m_fTimer = 0.0f; m_fSecPerFrame = 0.0f; }

	float	m_fTimer;
	float	m_fSecPerFrame;
};



/**

http://www.gamza.net/ 

void   Main( HWND hWnd, float dt )
{
//******************************************************************
//   프레임율 비의존적인 코드
//      dt에 의해 진행되기때문에 가능한한 빨리도는 코드들.
//      시스템이 좋을수록 더 자주 호출된다.
//******************************************************************
// Animation( dt );

if( fs.Update(dt) )
{
//******************************************************************
//   프레임율 의존적인 코드
//      이부분은 frame skip에 의해 고정 프레임율을 갖고 동작한다.
//******************************************************************
static long counter=0;
counter++;
if( counter%100 == 0 ) 
printf( "static frame rate code : %d\n", counter ); 
} 

if( ! fs.IsFrameSkip() ) 
{ 
//****************************************************************** 
//   경우에 따라 호출되지 않아도 되는 코드 
//      이부분은 frame skip에 의해 skip될수 있다. 
//      렌더링따위의 시간을 많이 잡아먹는 코드를 넣는다. 
//      역시 시스템이 좋을수록 더 자주 호출된다. 
//      숫자는 제시스템에서 나온 fps입니다. 
//****************************************************************** 
Sleep( 0.8f*1000 );   // 10fps 
//Sleep( 0.2f*1000 );   // 10fps 
//Sleep( 0.05f*1000 );   // 20fps 
//Sleep( 0.02f*1000 );   // 50fps 
//Sleep( 0.002f*1000 );   // 100fps 
} 

// printf frame / sec 
PrintFPS( dt ); 
}
*/

#endif	//	_PUTFRAMESKIP_H_