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
//   �������� ���������� �ڵ�
//      dt�� ���� ����Ǳ⶧���� �������� �������� �ڵ��.
//      �ý����� �������� �� ���� ȣ��ȴ�.
//******************************************************************
// Animation( dt );

if( fs.Update(dt) )
{
//******************************************************************
//   �������� �������� �ڵ�
//      �̺κ��� frame skip�� ���� ���� ���������� ���� �����Ѵ�.
//******************************************************************
static long counter=0;
counter++;
if( counter%100 == 0 ) 
printf( "static frame rate code : %d\n", counter ); 
} 

if( ! fs.IsFrameSkip() ) 
{ 
//****************************************************************** 
//   ��쿡 ���� ȣ����� �ʾƵ� �Ǵ� �ڵ� 
//      �̺κ��� frame skip�� ���� skip�ɼ� �ִ�. 
//      ������������ �ð��� ���� ��ƸԴ� �ڵ带 �ִ´�. 
//      ���� �ý����� �������� �� ���� ȣ��ȴ�. 
//      ���ڴ� ���ý��ۿ��� ���� fps�Դϴ�. 
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