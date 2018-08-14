//============================================
#include "Global.h"
//============================================
CDxGrid::CDxGrid()
{
	m_pDev	= NULL;
	m_pLine	= NULL;

}//	CDxGrid::CDxGrid()
//============================================
CDxGrid::~CDxGrid()	{ Destroy(); }
//============================================
INT CDxGrid::Create(LPDIRECT3DDEVICE9 pDev)
{
	m_pDev	= pDev;

	INT		i;
	INT		j;
	FLOAT	fMax;

	fMax = 10000;
	m_pLine = (SVtxD*)malloc( (6 + 20*4 ) * 2 * sizeof(SVtxD));	

	m_pLine[ 0] = SVtxD(-fMax,     0,     0, 0xFFFF0000);
	m_pLine[ 1] = SVtxD(    0,     0,     0, 0xFFFF0000);
	m_pLine[ 2] = SVtxD(    0,     0,     0, 0xFFFF0000);
	m_pLine[ 3] = SVtxD( fMax,     0,     0, 0xFFFF0000);
	
	m_pLine[ 4] = SVtxD(    0, -fMax,     0, 0xFF00FF00);
	m_pLine[ 5] = SVtxD(    0,     0,     0, 0xFF00FF00);
	m_pLine[ 6] = SVtxD(    0,     0,     0, 0xFF00FF00);
	m_pLine[ 7] = SVtxD(    0,  fMax,     0, 0xFF00FF00);
	
	m_pLine[ 8] = SVtxD(    0,     0, -fMax, 0xFF0000FF);
	m_pLine[ 9] = SVtxD(    0,     0,     0, 0xFF0000FF);
	m_pLine[10] = SVtxD(    0,     0,     0, 0xFF0000FF);
	m_pLine[11] = SVtxD(    0,     0,  fMax, 0xFF0000FF);

	j =6 * 2;

	DWORD	d1 = 0xFF999999;
	DWORD	d2 = 0xFF555555;

	SVtxD*	pLine = &m_pLine[j];

	for(i=0; i<20; ++i)
	{
		pLine[8*i +0 ] = SVtxD(-200, 0,  10* (i+1), (i%2)? d1 : d2);
		pLine[8*i +1 ] = SVtxD( 200, 0,  10* (i+1), (i%2)? d1 : d2);
		pLine[8*i +2 ] = SVtxD(-200, 0, -10* (i+1), (i%2)? d1 : d2);
		pLine[8*i +3 ] = SVtxD( 200, 0, -10* (i+1), (i%2)? d1 : d2);

		pLine[8*i +4 ] = SVtxD(  10* (i+1), 0,-200, (i%2)? d1 : d2);
		pLine[8*i +5 ] = SVtxD(  10* (i+1), 0, 200, (i%2)? d1 : d2);
		pLine[8*i +6 ] = SVtxD( -10* (i+1), 0,-200, (i%2)? d1 : d2);
		pLine[8*i +7 ] = SVtxD( -10* (i+1), 0, 200, (i%2)? d1 : d2);
	
	}//	for(i=0; i<20; ++i)

	return 0;

}//	INT CDxGrid::Create(LPDIRECT3DDEVICE9 pDev)
 //============================================
void CDxGrid::Destroy()
{
	if(m_pLine)
	{
		free(m_pLine);
		m_pLine = NULL;
	}

}//	void CDxGrid::Destroy()
//============================================
INT	CDxGrid::FrameMove()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);	
	m_pDev->SetTransform(D3DTS_WORLD, &matWorld);			// ����̽��� ���� ����� �����Ѵ�.

	return 0;

}//	INT	CDxGrid::FrameMove()
//============================================
void CDxGrid::Render()
{
	//	���� �ʿ� ����.
	m_pDev->SetRenderState( D3DRS_LIGHTING,  FALSE);

	//	�ؽ��� �ʿ� ����.
	m_pDev->SetTexture(0, 0);
	m_pDev->SetFVF(SVtxD::FVF);

	//	���ؽ� ���۸� �������� �ʰ� �ý��� �޸��� ���������� �������� �׸�.
	//	�ý��� �޸��� ������ gpu �� ����ϱ� ������ �ӵ��� ����.
	//	UP : User Point
	m_pDev->DrawPrimitiveUP
	(
		D3DPT_LINELIST,	//	���� �׸��� Ÿ��.
		6 + 4*20,		//	�׸� ������ ����.
		m_pLine,		//	���ؽ� ������ ������ �迭 ������.
		sizeof(SVtxD)	//	���ؽ� ���� �ϳ��� ũ��.
	);

}//	void CDxGrid::Render()
 //============================================