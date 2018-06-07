#include "Common.h"
#include "UITestDlg.h"
#include "PUIDlgResourceMgr.h"
#include "PUIListBox.h"
#include "PUIComboBox.h"



CUITestDlg::CUITestDlg(void)
{
	
}

CUITestDlg::~CUITestDlg(void)
{

}
//---------------------------------------------------------------------------------------
void	CUITestDlg::Init( bool bRegisterDlg )
{
	/// dlg skin & Pos & Size -----------------
	//!	[DIALOG]
	//!	[SKIN]			=	"TestUI\\Dlg.bmp"
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=	DT_VCENTER | DT_CENTER
	//!	[POS]			=	150, 100
	//! [SIZE]			=	100, 100
	
	std::vector<std::wstring>	DlgSkinFileList;
	DlgSkinFileList.push_back( L"TestUI\\Dlg.bmp" );
	int	nDlgSkinID	=	GetResMgr()->MakeCustomSkinElement( DlgSkinFileList, 0, DT_VCENTER | DT_CENTER );

	SetPos( 150, 100 );
	SetSize( 100, 100 );

	CPUIDlg::Init( nDlgSkinID, bRegisterDlg );
	/// ---------------------------------------



	/// button --------------------------------
	//!	[BUTTON]
	//!	[SKIN_ACT]		=	"TestUI\\Bttn_Act.bmp"
	//!	[SKIN_MOVER]	=	"TestUI\\Bttn_MouseOver.bmp"
	//!	[SKIN_CLICK]	=	"TestUI\\Bttn_Click.bmp"
	//!	[SKIN_UNACT]	=	"TestUI\\Bttn_UnAct.bmp"
	//!	[TEXT]			=	"Test��ư"
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=	DT_VCENTER | DT_CENTER
	//!	[POS]			=	200, 100
	//! [SIZE]			=	180, 30
	
	std::vector<std::wstring> FileList;
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\Bttn_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\Bttn_MouseOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\Bttn_Click.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\Bttn_UnAct.bmp") );

	int nSkinID = GetResMgr()->MakeCustomSkinElement( FileList, 0, DT_VCENTER | DT_CENTER );
	AddButton( eTESTDLGIDX_BUTTON, PUT_CSTR_UNI("Test��ư"), 200, 100, 180, 30, nSkinID );
	/// ---------------------------------------



	/// static --------------------------------
	//!	[STATIC]
	//!	[SKIN]			=	"TestUI\\Bttn_Act.bmp"	
	//!	[TEXT]			=	"Test ����ƽ"
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=
	//!	[POS]			=	400, 150
	//! [SIZE]			=	180, 30

	FileList.clear();
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\Static_Background.bmp") );
	nSkinID = GetResMgr()->MakeCustomSkinElement( FileList, 0 );
	AddStatic( eTESTDLGIDX_STATIC, PUT_CSTR_UNI("Test ����ƽ"), 400, 150, 180, 30, nSkinID );
	/// ---------------------------------------



	/// RadioButton ---------------------------
	//!	[RADIOBUTTON]
	//!	[SKIN_CHK_ACT]		=	"TestUI\\RadioBttn_Chk_Act.bmp"
	//!	[SKIN_CHK_MOVER]	=	"TestUI\\RadioBttn_Chk_MOver.bmp"
	//!	[SKIN_CHK_CLICK]	=	"TestUI\\RadioBttn_Chk_Click.bmp"
	//!	[SKIN_CHK_UNACT]	=	"TestUI\\RadioBttn_Chk_UnAct.bmp"

	//!	[SKIN_UNCHK_ACT]	=	"TestUI\\RadioBttn_UnChk_Act.bmp"
	//!	[SKIN_UNCHK_MOVER]	=	"TestUI\\RadioBttn_UnChk_MOver.bmp"
	//!	[SKIN_UNCHK_CLICK]	=	"TestUI\\RadioBttn_UnChk_Click.bmp"
	//!	[SKIN_UNCHK_UNACT]	=	"TestUI\\RadioBttn_UnChk_UnAct.bmp"

	//!	[CTRLCNT]		=	3

	//!	[TEXT]			=	"���� ��ư - 1"	
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=
	//!	[POS]			=	200, 200
	//! [SIZE]			=	150, 30

	//!	[TEXT]			=	"���� ��ư - 2"	
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=
	//!	[POS]			=	400, 200
	//! [SIZE]			=	150, 30

	//!	[TEXT]			=	"���� ��ư - 3"	
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=
	//!	[POS]			=	600, 200
	//! [SIZE]			=	150, 30

	FileList.clear();
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\RadioBttn_Chk_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\RadioBttn_Chk_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\RadioBttn_Chk_Click.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\RadioBttn_Chk_UnAct.bmp") );

	FileList.push_back( PUT_CSTR_UNI("TESTUI\\RadioBttn_UnChk_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\RadioBttn_UnChk_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\RadioBttn_UnChk_Click.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\RadioBttn_UnChk_UnAct.bmp") );

	nSkinID	=	GetResMgr()->MakeCustomSkinElement( FileList, 0 );

	AddRadioButton( eTESTDLGIDX_RADIOBTTN_1, 
		eTESTDLGIDX_RADIOBTTN_GROUP_1, 
		PUT_CSTR_UNI("���� ��ư - 1"), 
		200, 200, 150, 30, nSkinID );

	AddRadioButton( eTESTDLGIDX_RADIOBTTN_2,		
		eTESTDLGIDX_RADIOBTTN_GROUP_1, 
		PUT_CSTR_UNI("���� ��ư - 2"), 
		400, 200, 150, 30, nSkinID );

	AddRadioButton( eTESTDLGIDX_RADIOBTTN_3,		
		eTESTDLGIDX_RADIOBTTN_GROUP_1, 
		PUT_CSTR_UNI("���� ��ư - 3"), 
		600, 200, 150, 30, nSkinID );
	/// ---------------------------------------



	/// CheckBox ------------------------------

	//!	[CHECKBOX]
	//!	[SKIN_CHK_ACT]		=	"TestUI\\CheckBox_Chk_Act.bmp"
	//!	[SKIN_CHK_MOVER]	=	"TestUI\\CheckBox_Chk_MOver.bmp"
	//!	[SKIN_CHK_CLICK]	=	"TestUI\\CheckBox_Chk_Click.bmp"
	//!	[SKIN_CHK_UNACT]	=	"TestUI\\CheckBox_Chk_UnAct.bmp"

	//!	[SKIN_UNCHK_ACT]	=	"TestUI\\CheckBox_UnChk_Act.bmp"
	//!	[SKIN_UNCHK_MOVER]	=	"TestUI\\CheckBox_UnChk_MOver.bmp"
	//!	[SKIN_UNCHK_CLICK]	=	"TestUI\\CheckBox_UnChk_Click.bmp"
	//!	[SKIN_UNCHK_UNACT]	=	"TestUI\\CheckBox_UnChk_UnAct.bmp"

	//!	[CTRLCNT]		=	2

	//!	[TEXT]			=	"üũ �ڽ� 1"
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=
	//!	[POS]			=	100, 50
	//! [SIZE]			=	100, 30

	//!	[TEXT]			=	"üũ �ڽ� 1"
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=
	//!	[POS]			=	300, 50
	//! [SIZE]			=	100, 30

	FileList.clear();
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\CheckBox_Chk_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\CheckBox_Chk_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\CheckBox_Chk_Click.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\CheckBox_Chk_UnAct.bmp") );

	FileList.push_back( PUT_CSTR_UNI("TESTUI\\CheckBox_UnChk_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\CheckBox_UnChk_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\CheckBox_UnChk_Click.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\CheckBox_UnChk_UnAct.bmp") );

	nSkinID	=	GetResMgr()->MakeCustomSkinElement( FileList, 0 );
	AddCheckBox( eTESTDLGIDX_CHECKBOX_1, PUT_CSTR_UNI("üũ �ڽ� 1"), 100, 50, 100, 30, nSkinID );
	AddCheckBox( eTESTDLGIDX_CHECKBOX_2, PUT_CSTR_UNI("üũ �ڽ� 2"), 300, 50, 100, 30, nSkinID );
	/// ---------------------------------------



	/// Slider --------------------------------

	//!	[SLIDER]
	//!	[SKIN_TRACK]	=	"TestUI\\Slider_Track.bmp"
	//!	[SKIN_ACT]		=	"TestUI\\Slider_Btn_Act.bmp"
	//!	[SKIN_MOVER]	=	"TestUI\\Slider_Btn_MOver.bmp"
	//!	[SKIN_CLICK]	=	"TestUI\\Slider_Btn_Click.bmp"
	//!	[SKIN_UNACT]	=	"TestUI\\Slider_Btn_UnAct.bmp"
	//!	[TEXT]			=	
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=	
	//!	[POS]			=	100, 480
	//! [SIZE]			=	200, 30

	FileList.clear();
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\Slider_Track.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\Slider_Btn_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\Slider_Btn_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\Slider_Btn_Click.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\Slider_Btn_UnAct.bmp") );
	nSkinID	=	GetResMgr()->MakeCustomSkinElement( FileList, 0 );
	AddSlider( eTESTDLGIDX_SLIDER, 100, 480, 200, 30, nSkinID );
	/// ---------------------------------------



	/// ListBox -------------------------------

	//!	[LISTBOX]
	//!	[SKIN_BCKGRND]			=	"TestUI\\List_BackGround.bmp"
	//!	[SKIN_SELECT]			=	"TestUI\\List_Select.bmp"

	//!	[SKIN_TRACKBAR]			=	"TestUI\\ScrollBar_TrackBar.bmp"

	//!	[SKIN_PREBTN_ACT]		=	"TestUI\\ScrollBar_PreBtn_Act.bmp"
	//!	[SKIN_PREBTN_MOVER]		=	"TestUI\\ScrollBar_PreBtn_MOver.bmp"
	//!	[SKIN_PREBTN_CLICK]		=	"TestUI\\ScrollBar_PreBtn_Click.bmp"

	//!	[SKIN_NEXTBTN_ACT]		=	"TestUI\\ScrollBar_NextBtn_Act.bmp"
	//!	[SKIN_NEXTBTN_MOVER]	=	"TestUI\\ScrollBar_NextBtn_MOver.bmp"
	//!	[SKIN_NEXTBTN_CLICK]	=	"TestUI\\ScrollBar_NextBtn_Click.bmp"

	//!	[SKIN_THUMBBTTN_ACT]	=	"TestUI\\ScrollBar_ThumbBtn_Act.bmp"
	//!	[SKIN_THUMBBTTN_MOVER]	=	"TestUI\\ScrollBar_ThumbBtn_MOver.bmp"
	//!	[SKIN_THUMBBTTN_CLICK]	=	"TestUI\\ScrollBar_ThumbBtn_Click.bmp"

	//!	[TEXT]			=	
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=	
	//!	[POS]			=	10, 300
	//! [SIZE]			=	200, 120

	CPUIListBox	*pListBox	=	NULL;
	FileList.clear();
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\List_BackGround.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\List_Select.bmp") );
	nSkinID	=	GetResMgr()->MakeCustomSkinElement( FileList, 0 );

	FileList.clear();
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_TrackBar.bmp") );

	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_PreBtn_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_PreBtn_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_PreBtn_Click.bmp") );

	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_NextBtn_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_NextBtn_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_NextBtn_Click.bmp") );

	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_ThumbBtn_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_ThumbBtn_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_ThumbBtn_Click.bmp") );

	int nScrollID	=	GetResMgr()->MakeCustomSkinElement( FileList, 0 );	

	AddListBox( eTESTDLGIDX_LISTBOX, 10, 300, 200, 120, nSkinID, nScrollID, 0, &pListBox );
	pListBox->AddItem( PUT_CSTR_UNI("����Ʈ1"), NULL );
	pListBox->AddItem( PUT_CSTR_UNI("����Ʈ2"), NULL );
	pListBox->AddItem( PUT_CSTR_UNI("����Ʈ3"), NULL );
	pListBox->AddItem( PUT_CSTR_UNI("����Ʈ4"), NULL );
	pListBox->AddItem( PUT_CSTR_UNI("����Ʈ5"), NULL );
	pListBox->AddItem( PUT_CSTR_UNI("����Ʈ6"), NULL );
	pListBox->AddItem( PUT_CSTR_UNI("����Ʈ7"), NULL );
	pListBox->AddItem( PUT_CSTR_UNI("����Ʈ8"), NULL );
	pListBox->AddItem( PUT_CSTR_UNI("����Ʈ9"), NULL );
	pListBox->AddItem( PUT_CSTR_UNI("����Ʈ10"), NULL );
	/// ---------------------------------------



	/// ComboBox ------------------------------

	//!	[COMBOBOX]
	//!	[SKIN_EDIT]			=	"TestUI\\ComboBox_Edit.bmp"
	//!	[SKIN_DROPDOWN]		=	"TestUI\\ComboBox_DropDown.bmp"
	//!	[SKIN_SELECTION]	=	"TestUI\\ComboBox_Selection.bmp"

	//!	[SKIN_BTTN_ACT]		=	"TestUI\\ComboBox_Bttn_Act.bmp"
	//!	[SKIN_BTTN_MOVER]	=	"TestUI\\ComboBox_Bttn_MOver.bmp"
	//!	[SKIN_BTTN_CLICK]	=	"TestUI\\ComboBox_Bttn_Click.bmp"

	//!	[SKIN_TRACKBAR]		=	"TestUI\\ScrollBar_TrackBar.bmp"

	//!	[SKIN_PREBTN_ACT]		=	"TestUI\\ScrollBar_PreBtn_Act.bmp"
	//!	[SKIN_PREBTN_MOVER]		=	"TestUI\\ScrollBar_PreBtn_MOver.bmp"
	//!	[SKIN_PREBTN_CLICK]		=	"TestUI\\ScrollBar_PreBtn_Click.bmp"

	//!	[SKIN_NEXTBTN_ACT]		=	"TestUI\\ScrollBar_NextBtn_Act.bmp"
	//!	[SKIN_NEXTBTN_MOVER]	=	"TestUI\\ScrollBar_NextBtn_MOver.bmp"
	//!	[SKIN_NEXTBTN_CLICK]	=	"TestUI\\ScrollBar_NextBtn_Click.bmp"

	//!	[SKIN_THUMBBTTN_ACT]	=	"TestUI\\ScrollBar_ThumbBtn_Act.bmp"
	//!	[SKIN_THUMBBTTN_MOVER]	=	"TestUI\\ScrollBar_ThumbBtn_MOver.bmp"
	//!	[SKIN_THUMBBTTN_CLICK]	=	"TestUI\\ScrollBar_ThumbBtn_Click.bmp"

	//!	[TEXT]			=	
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=	
	//!	[POS]			=	10, 90
	//! [SIZE]			=	200, 25
	//! [DROPHEIGHT]	=	100
	CPUIComboBox *pCombo	=	NULL;	
	FileList.clear();
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ComboBox_Edit.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ComboBox_DropDown.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ComboBox_Selection.bmp") );

	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ComboBox_Bttn_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ComboBox_Bttn_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ComboBox_Bttn_Click.bmp") );

	nSkinID	=	GetResMgr()->MakeCustomSkinElement( FileList, 0 );

	FileList.clear();
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_TrackBar.bmp") );

	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_PreBtn_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_PreBtn_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_PreBtn_Click.bmp") );

	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_NextBtn_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_NextBtn_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_NextBtn_Click.bmp") );

	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_ThumbBtn_Act.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_ThumbBtn_MOver.bmp") );
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\ScrollBar_ThumbBtn_Click.bmp") );

	nScrollID	=	GetResMgr()->MakeCustomSkinElement( FileList, 0 );	

	AddComboBox( eTESTDLGIDX_COMBOBOX, 10, 90, 200, 25, nSkinID, nScrollID, 0, false, &pCombo );

	pCombo->SetDropHeight( 100 );
	//	for( size_t unCur = 0; unCur < 10; ++unCur )
	//		pCombo->AddItem( PUT_CSTR_UNI("�޺�"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_1"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_2"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_3"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_4"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_5"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_6"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_7"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_8"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_9"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_10"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_11"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_12"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_13"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_14"), NULL );
	pCombo->AddItem( PUT_CSTR_UNI("�޺�_15"), NULL );
	/// ---------------------------------------


	/// IMEEditBox ----------------------------

	//!	[IMEEDITBOX]
	//!	[SKIN]			=	"TestUI\\EditBox_BackGrnd.bmp"	
	//!	[TEXT]			=	"Test����Ʈ�ڽ�"
	//!	[FONTIDX]		=	0
	//!	[TEXTFORMAT]	=
	//!	[POS]			=	400, 150
	//! [SIZE]			=	184, 30

	FileList.clear();
	FileList.push_back( PUT_CSTR_UNI("TESTUI\\EditBox_BackGrnd.bmp") );
	nSkinID = GetResMgr()->MakeCustomSkinElement( FileList, 0 );
	AddIMEEditBox( eTESTDLGIDX_EDITBOX, PUT_CSTR_UNI("Test����Ʈ�ڽ�"), 400, 100, 184, 30, nSkinID );
	/// ---------------------------------------


	SetCallBack( CUITestDlg::Callback );
}
//---------------------------------------------------------------------------------------
void CALLBACK CUITestDlg::Callback( UINT nEvent, int nControlID, CPUICtrl* pControl, void* pUserContext )
{
	int aaa = 0;
	aaa = 0;
}
