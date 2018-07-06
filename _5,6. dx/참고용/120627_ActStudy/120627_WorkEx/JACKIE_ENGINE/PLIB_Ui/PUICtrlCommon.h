#ifndef _JUICTRLCOMMON_H_
#define _JUICTRLCOMMON_H_
#pragma once

#include <vector>
#include "PUTCommon.h"
#include "PRCommonTypeDef.h"
//-----------------------------------------------------------------
//@	��Ʈ�� Ÿ��
enum eCTRLTYPE_
{
	eCTRLTYPE_NONE = -1,
	eCTRLTYPE_BUTTON,
	eCTRLTYPE_STATIC,
	eCTRLTYPE_CHECKBOX,
	eCTRLTYPE_RADIOBUTTON,
	eCTRLTYPE_COMBOBOX,
	eCTRLTYPE_SLIDER,
	eCTRLTYPE_EDITBOX,
	eCTRLTYPE_IMEEDITBOX,
	eCTRLTYPE_LISTBOX,
	eCTRLTYPE_SCROLLBAR,
	eCTRLTYPE_MAX
};
//-----------------------------------------------------------------
//@	��Ʈ�� �̺�Ʈ
enum eCTRLEVENT_
{
	eCTRLEVENT_BUTTON_CLICKED = 1,
	eCTRLEVENT_COMBOBOX_SELECTION_CHANGED,
	eCTRLEVENT_RADIOBUTTON_CHANGED,
	eCTRLEVENT_CHECKBOX_CHANGED,
	eCTRLEVENT_SLIDER_VALUE_CHANGED,
	eCTRLEVENT_EDITBOX_STRING,
	eCTRLEVENT_EDITBOX_CHANGED,
	eCTRLEVENT_LISTBOX_ITEM_DBLCLK,
	eCTRLEVENT_LISTBOX_SELECTION,
	eCTRLEVENT_LISTBOX_SELECTION_END
};
//-----------------------------------------------------------------
//@	��Ʈ�� ����
enum eCTRLSTATE_
{
	eCTRLSTATE_NORMAL = 0,
	eCTRLSTATE_DISABLED,
	eCTRLSTATE_HIDDEN,
	eCTRLSTATE_FOCUS,
	eCTRLSTATE_MOUSEOVER,
	eCTRLSTATE_PRESSED,
	eCTRLSTATE_MAX
};
//-----------------------------------------------------------------
class CPUIBlendColor
{
public:
	CPUIBlendColor()	{ InitMembers(); }
	~CPUIBlendColor()	{}

	void InitMembers();

	void Init( D3DCOLOR colDefault, D3DCOLOR colDisabled = D3DCOLOR_ARGB( 200, 128, 128, 128 ), D3DCOLOR colHidden = 0 );
	void Blend( UINT iState, float fElapsedTime, float fRate = 0.7f );
	
	void SetStateColor( int nState, D3DCOLOR col )
	{
		m_colState[ nState ] = col;
	}
	void SetCurrentColor( D3DCOLOR col )
	{
		m_colCurrent = col;
	}
	D3DCOLOR GetStateColor( int nState )
	{
		return m_colState[ nState ];
	}

	D3DXCOLOR	GetCurrentColor()	{ return m_colCurrent; }

private:
	D3DCOLOR	m_colState[eCTRLSTATE_MAX];
	D3DXCOLOR	m_colCurrent;

};// CPUIBlendColor End
//-----------------------------------------------------------------
class CPUIElement
{
public:
	CPUIElement()	{ InitMembers(); }
	void	InitMembers();

	void	SetTex( int unTexId, RECT* prtTex, D3DCOLOR colDefault = D3DCOLOR_ARGB( 255, 255, 255, 255 ) );
	void	SetFont( int unFontId, D3DCOLOR colDefault = D3DCOLOR_ARGB( 255, 255, 255, 255 ), DWORD dwTexFormat = DT_CENTER | DT_VCENTER );
	void	Refresh();

	CPUIBlendColor&	GetFontColor()		{ return m_colFont; }
	CPUIBlendColor&	GetTexColor()	{ return m_colTex; }

	int		GetFontID()			const	{ return m_nFontIdx; }
	void	SetFontID( int nFontID )	{ m_nFontIdx = nFontID; }

	int		GetTexID()		const	{ return m_nTexIdx; }
	void	SetTexID( int nTexID )	{ m_nTexIdx = nTexID; }

	DWORD	GetTextFormat()		const	{ return m_dwTexFormat; }
	void	SetTexFormat( DWORD dwTexFormat )	{ m_dwTexFormat = dwTexFormat; }
	RECT	GetTexRect()	const { return m_rtTexBounding; }
	void	SetTexRect( int nLeft, int nTop, int nRight, int nBotttom )	
	{ m_rtTexBounding.left = nLeft, m_rtTexBounding.top = nTop, m_rtTexBounding.right = nRight, m_rtTexBounding.bottom = nBotttom; }


private:
	int		m_nTexIdx;
	int		m_nFontIdx;
	DWORD	m_dwTexFormat;
	RECT	m_rtTexBounding;

	CPUIBlendColor	m_colTex;
	CPUIBlendColor	m_colFont;
};
// CPUIElement End
//-----------------------------------------------------------------
typedef	std::vector<CPUIElement>	CUSTOMSKINELEARR;
typedef CUSTOMSKINELEARR::iterator	CUSTOMSKINELEARRITER;
//-----------------------------------------------------------------
class CPUITexNode
{
public:
	CPUITexNode()	{ InitMembers(); }	
	~CPUITexNode()	{ PUT_SAFE_RELEASE(m_pTex); }
	void	InitMembers();
	
	HMODULE				m_hResourceModule;
	int					m_nResourceID;
	WCHAR				m_wszFilename[MAX_PATH];
	PRDXTXTRBUFF9		m_pTex;
	DWORD				m_dwWidth;
	DWORD				m_dwHeight;
	bool				m_bFileSource;
};
//	CPUITexNode End
//-----------------------------------------------------------------
class CPUIFontNode
{
public:
	CPUIFontNode()		{ InitMembers(); }
	void	InitMembers();

	WCHAR		m_tszFace[MAX_PATH];
	LPD3DXFONT	m_pFont;
	UINT		m_unHeight;
	UINT		m_unWeight;
};
//	CPUIFontNode End
//-----------------------------------------------------------------
class CPUIElementHolder
{
public:
	CPUIElementHolder()	{ InitMembers(); }
	void InitMembers();

	UINT unCtrlType;
	UINT unIDx;

	CPUIElement Element;
};
// CPUIElementHolder End
//-----------------------------------------------------------------


//	JUI_MAX_EDITBOXLENGTH�� ����Ʈ �ڽ����� ����Ҽ� �ִ� �������ڸ� ������ �ִ���� �����̴�..
//	���Ͻ�ũ������ 16��Ʈ�� �Ѵ� ���ڿ��� �������� �ʴ´�. 
//	�̴� �ι��ڸ� �����ؼ� 65536 ���ڼ��� �Ѿ �ȵȴٴ� ����.
#define JUI_MAX_EDITBOXLENGTH 0xFFFF





#endif	//	_JUICTRLCOMMON_H_