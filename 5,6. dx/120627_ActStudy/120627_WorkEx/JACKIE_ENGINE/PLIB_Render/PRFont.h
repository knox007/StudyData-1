#ifndef _JRFONT_H_
#define _JRFONT_H_
#pragma once

//	UI에 있는데 또 만들필요 없다.
//	나중에 정리하자
//	JACKIENOTE_12/03/07

enum FONTALIGNMENT
{ 
	FA_LEFT, 
	FA_CENTER, 
	FA_RIGHT, 
	FA_TOPRIGHT, 
	FA_TOPLEFT, 
	FA_BOTTOMRIGHT, 
	FA_BOTTOMLEFT 
};

class CPRFont
{
public:
	CPRFont()			{ InitMembers(); }
	virtual ~CPRFont()	{ ClearMembers(); }
	void	InitMembers()	{ m_pFont = NULL; }
	void	ClearMembers();
	

	bool	Init(	LPDIRECT3DDEVICE9 pDev, WCHAR* ptszFaceName, int nSize, bool bBold = false, bool bItalic = false );
	void	Print(	TCHAR* ptszText, int nPosX, int nPosY, DWORD dwColor, 
					LPD3DXSPRITE sprite = NULL, int nTextBoxWid = 0, int nTextBoxHei = 0, FONTALIGNMENT alignment = FA_LEFT );
	void	OnLostDevice();
	void	OnResetDevice();

private:
	LPD3DXFONT	m_pFont;
};

#endif	//	_JRFONT_H_