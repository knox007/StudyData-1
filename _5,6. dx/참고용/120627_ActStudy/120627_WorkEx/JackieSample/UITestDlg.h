#pragma once
#include "PUIdlg.h"

class CUITestDlg :
	public CPUIDlg
{
public:

	enum eTESTDLGIDX_
	{
		eTESTDLGIDX_BUTTON = 300,
		eTESTDLGIDX_EDITBOX,
		eTESTDLGIDX_STATIC,
		eTESTDLGIDX_CHECKBOX_1,
		eTESTDLGIDX_CHECKBOX_2,

		eTESTDLGIDX_RADIOBTTN_1,
		eTESTDLGIDX_RADIOBTTN_2,
		eTESTDLGIDX_RADIOBTTN_3,
		eTESTDLGIDX_RADIOBTTN_GROUP_1,

		eTESTDLGIDX_COMBOBOX,
		eTESTDLGIDX_SLIDER,
		eTESTDLGIDX_LISTBOX,

		eTESTDLGIDX_MAX
	};


	CUITestDlg(void);
	virtual ~CUITestDlg(void);	

	void	Init( bool bRegisterDlg = true );

private:	
	static	void CALLBACK Callback( UINT nEvent, int nControlID, CPUICtrl* pControl, void* pUserContext );	
};
