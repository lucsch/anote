/*!
@header main.cpp
 @abstract   (description)
 @discussion (description)
 */

#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "../include/main.h"

extern const char* Anote_MAJOR_VERSION;
extern const char* Anote_MINOR_VERSION;
extern const char* GIT_REV;
extern const char* GIT_TAG;
extern const char* GIT_BRANCH;
extern const char* GIT_NUMBER;


/* Application initialisation */
bool AnoteApp::OnInit()
{
	ANote * MyNote = new ANote(NULL,0L);
	MyNote->Show();
	SetTopWindow(MyNote);	
	return true;
}

BEGIN_EVENT_TABLE (ANote, wxDialog)
	EVT_CLOSE (ANote::OnQuit)
	EVT_BUTTON(wxID_CLOSE,ANote::OnCloseButton)
	EVT_BUTTON(ID_BUTTON_GENERATE,ANote::OnButtonGenerate)
	EVT_TEXT(ID_SETTINGS_TEXT_AUTHOR,ANote::OnAuthorTextChange)
	EVT_CHECKBOX (ID_SETTINGS_DATE_CHECK,ANote::OnCheckDate)
	EVT_CHOICE (ID_GENERAL_LIST_TYPE, ANote::OnChangeGeneralListType)
	EVT_TEXT(ID_SETTINGS_COMMENTWIDTH,ANote::OnChangeCommentWidth)
	EVT_DATE_CHANGED(ID_DATEPICKERCTRL,ANote::OnChangeDate)
	EVT_TEXT(ID_FUNCTION_TEXT_CODE,ANote::OnFunctionTextChange)
	EVT_CHOICE(ID_LISTPARAM_CHOICE,ANote::OnChangeParamType)
END_EVENT_TABLE()



ANote::ANote()
{
    Init();
}

ANote::ANote( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
	PostInit();
}


/*!
 * ANote creator
 */
bool ANote::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin ANote creation
    //SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    //Centre();
////@end ANote creation
    return true;
}

void ANote::PostInit()
{
	// post init controls
	m_Function_List_Param->SetChoiceList(m_Listparam_Choice);

        wxString my_app_name = wxString::Format("Anote - %s.%s.%s", Anote_MAJOR_VERSION, Anote_MINOR_VERSION, GIT_NUMBER);
	SetTitle(my_app_name);
	
	// load settings from config here
	wxString myTempAuthor = _T("");
	int myTempCommentWidth = -1;
	
	if (m_Config.GetConfigItemAuthor(myTempAuthor))
		m_Settings_Text_Author->SetValue(myTempAuthor);
		
	if (m_Config.GetConfigItemCommentWidth() > -1)
		m_Settings_CommentWidth->SetValue(m_Config.GetConfigItemCommentWidth());
		
	m_Settings_Date_Check->SetValue(m_Config.GetConfigItemCheckDate());
	m_Check_ShowOutput->SetValue(m_Config.GetConfigItemShowResult());
	
	// process settings
	wxCommandEvent myevent;
	OnAuthorTextChange(myevent);
	OnCheckDate(myevent);
	OnChangeCommentWidth(myevent);
}

/*!
 * ANote destructor
 */
ANote::~ANote()
{
	dlgResult->Destroy();
	delete dlgResult;
	
	// write configuration
	m_Config.SetConfigItemAuthor(m_Settings_Text_Author->GetValue());
	m_Config.SetConfigItemCommentWidth(m_Settings_CommentWidth->GetValue());
	m_Config.SetConfigItemCheckDate(m_Settings_Date_Check->GetValue());
	m_Config.SetConfigItemShowResult(m_Check_ShowOutput->GetValue());

}


void ANote::Init()
{
	dlgResult = new  AnoteResults(this,wxID_ANY);
	
   m_Notebook_Comment_Settings = NULL;
    m_Notebook_General_Function = NULL;
    m_GeneralBoxPanelSizer = NULL;
    m_General_Sizer = NULL;
    m_General_List_Type = NULL;
    m_General_Static_Name = NULL;
    m_General_Text_Name = NULL;
    m_General_Text_Brief = NULL;
    m_General_Text_Description = NULL;
    m_Function_Text_Code = NULL;
    m_Function_Text_Brief = NULL;
    m_Function_Text_Description = NULL;
    m_Function_List_Param = NULL;
    m_Listparam_Choice = NULL;
    m_Settings_Text_Author = NULL;
    m_Settings_CommentWidth = NULL;
    m_Settings_Date_Check = NULL;
    m_DatePickerCtrl = NULL;
    m_Check_ShowOutput = NULL;
}



void ANote::CreateControls()
{    
 
     ANote* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    m_Notebook_Comment_Settings = new wxNotebook( itemDialog1, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* itemPanel4 = new wxPanel( m_Notebook_Comment_Settings, ID_PANEL_COMMENT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxVERTICAL);
    itemPanel4->SetSizer(itemBoxSizer5);

    m_Notebook_General_Function = new wxNotebook( itemPanel4, ID_NOTEBOOK2, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* itemPanel7 = new wxPanel( m_Notebook_General_Function, ID_PANEL_GENERAL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_GeneralBoxPanelSizer = new wxBoxSizer(wxVERTICAL);
    itemPanel7->SetSizer(m_GeneralBoxPanelSizer);

    m_General_Sizer = new wxFlexGridSizer(3, 2, 0, 0);
    m_General_Sizer->AddGrowableCol(1);
    m_GeneralBoxPanelSizer->Add(m_General_Sizer, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText10 = new wxStaticText( itemPanel7, wxID_STATIC, _("Type :"), wxDefaultPosition, wxDefaultSize, 0 );
    m_General_Sizer->Add(itemStaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString m_General_List_TypeStrings;
    m_General_List_TypeStrings.Add(_("File"));
    m_General_List_TypeStrings.Add(_("Classes, Variables, Structures,..."));
    m_General_List_Type = new wxChoice( itemPanel7, ID_GENERAL_LIST_TYPE, wxDefaultPosition, wxDefaultSize, m_General_List_TypeStrings, 0 );
    m_General_List_Type->SetStringSelection(_("File"));
    m_General_Sizer->Add(m_General_List_Type, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_General_Static_Name = new wxStaticText( itemPanel7, wxID_GENERAL_STATIC_NAME, _("Name :"), wxDefaultPosition, wxDefaultSize, 0 );
    m_General_Sizer->Add(m_General_Static_Name, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_General_Text_Name = new wxTextCtrl( itemPanel7, ID_GENERAL_TEXT_NAME, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    m_General_Sizer->Add(m_General_Text_Name, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText14 = new wxStaticText( itemPanel7, wxID_STATIC, _("Brief :"), wxDefaultPosition, wxDefaultSize, 0 );
    m_General_Sizer->Add(itemStaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_General_Text_Brief = new wxTextCtrl( itemPanel7, ID_GENERAL_TEXT_BRIEF, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    if (ANote::ShowToolTips())
        m_General_Text_Brief->SetToolTip(_("Insert a brief description of the file, classe or structure"));
    m_General_Sizer->Add(m_General_Text_Brief, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer16Static = new wxStaticBox(itemPanel7, wxID_ANY, _("Description"));
    wxStaticBoxSizer* itemStaticBoxSizer16 = new wxStaticBoxSizer(itemStaticBoxSizer16Static, wxVERTICAL);
    m_GeneralBoxPanelSizer->Add(itemStaticBoxSizer16, 1, wxGROW|wxALL, 5);
    m_General_Text_Description = new wxTextCtrl( itemPanel7, ID_GENERAL_TEXT_DESCRIPTION, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
    if (ANote::ShowToolTips())
        m_General_Text_Description->SetToolTip(_("Insert the full description of the file, class or structure"));
    itemStaticBoxSizer16->Add(m_General_Text_Description, 1, wxGROW, 5);

    m_Notebook_General_Function->AddPage(itemPanel7, _("General"));

    wxPanel* itemPanel18 = new wxPanel( m_Notebook_General_Function, ID_PANEL_FUNCTION, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxVERTICAL);
    itemPanel18->SetSizer(itemBoxSizer19);

    wxFlexGridSizer* itemFlexGridSizer20 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer20->AddGrowableCol(1);
    itemBoxSizer19->Add(itemFlexGridSizer20, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText21 = new wxStaticText( itemPanel18, wxID_STATIC, _("Function header :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer20->Add(itemStaticText21, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Function_Text_Code = new wxTextCtrl( itemPanel18, ID_FUNCTION_TEXT_CODE, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer20->Add(m_Function_Text_Code, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText23 = new wxStaticText( itemPanel18, wxID_STATIC, _("Brief :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer20->Add(itemStaticText23, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Function_Text_Brief = new wxTextCtrl( itemPanel18, ID_FUNCTION_TEXT_BRIEF, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer20->Add(m_Function_Text_Brief, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer25Static = new wxStaticBox(itemPanel18, wxID_ANY, _("Function description"));
    wxStaticBoxSizer* itemStaticBoxSizer25 = new wxStaticBoxSizer(itemStaticBoxSizer25Static, wxVERTICAL);
    itemBoxSizer19->Add(itemStaticBoxSizer25, 1, wxGROW|wxALL, 5);
    m_Function_Text_Description = new wxTextCtrl( itemPanel18, ID_FUNCTION_TEXT_DESCRIPTION, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
    itemStaticBoxSizer25->Add(m_Function_Text_Description, 1, wxGROW, 5);

    wxStaticBox* itemStaticBoxSizer27Static = new wxStaticBox(itemPanel18, wxID_ANY, _("Function parameters and return code"));
    wxStaticBoxSizer* itemStaticBoxSizer27 = new wxStaticBoxSizer(itemStaticBoxSizer27Static, wxVERTICAL);
    itemBoxSizer19->Add(itemStaticBoxSizer27, 2, wxGROW|wxALL, 5);
    m_Function_List_Param = new AFListParam( itemPanel18, ID_FUNCTION_LIST_PARAM );
    itemStaticBoxSizer27->Add(m_Function_List_Param, 2, wxGROW, 5);

    wxArrayString m_Listparam_ChoiceStrings;
    m_Listparam_ChoiceStrings.Add(_("parameter"));
    m_Listparam_ChoiceStrings.Add(_("return value"));
    m_Listparam_Choice = new wxChoice( itemPanel18, ID_LISTPARAM_CHOICE, wxDefaultPosition, wxDefaultSize, m_Listparam_ChoiceStrings, 0 );
    m_Listparam_Choice->SetStringSelection(_("parameter"));
    itemStaticBoxSizer27->Add(m_Listparam_Choice, 0, wxGROW|wxTOP, 5);

    m_Notebook_General_Function->AddPage(itemPanel18, _("Function"));

    itemBoxSizer5->Add(m_Notebook_General_Function, 1, wxGROW|wxALL, 5);

    m_Notebook_Comment_Settings->AddPage(itemPanel4, _("Comment"));

    wxPanel* itemPanel30 = new wxPanel( m_Notebook_Comment_Settings, ID_PANEL_SETTINGS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer31 = new wxBoxSizer(wxVERTICAL);
    itemPanel30->SetSizer(itemBoxSizer31);

    wxFlexGridSizer* itemFlexGridSizer32 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer32->AddGrowableCol(1);
    itemBoxSizer31->Add(itemFlexGridSizer32, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText33 = new wxStaticText( itemPanel30, wxID_STATIC, _("Author :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer32->Add(itemStaticText33, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Settings_Text_Author = new wxTextCtrl( itemPanel30, ID_SETTINGS_TEXT_AUTHOR, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer32->Add(m_Settings_Text_Author, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText35 = new wxStaticText( itemPanel30, wxID_STATIC, _("Comment width :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer32->Add(itemStaticText35, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Settings_CommentWidth = new wxSpinCtrl( itemPanel30, ID_SETTINGS_COMMENTWIDTH, _T("50"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 20, 100, 50 );
    itemFlexGridSizer32->Add(m_Settings_CommentWidth, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    wxBoxSizer* itemBoxSizer37 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer31->Add(itemBoxSizer37, 0, wxALIGN_RIGHT|wxALL, 5);
    m_Settings_Date_Check = new wxCheckBox( itemPanel30, ID_SETTINGS_DATE_CHECK, _("Add date"), wxDefaultPosition, wxDefaultSize, 0 );
    m_Settings_Date_Check->SetValue(true);
    if (ANote::ShowToolTips())
        m_Settings_Date_Check->SetToolTip(_("Add the setting's date in the comment if checked"));
    itemBoxSizer37->Add(m_Settings_Date_Check, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DatePickerCtrl = new wxDatePickerCtrl( itemPanel30, ID_DATEPICKERCTRL, wxDateTime(), wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
    itemBoxSizer37->Add(m_DatePickerCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Notebook_Comment_Settings->AddPage(itemPanel30, _("Settings"));

    itemBoxSizer2->Add(m_Notebook_Comment_Settings, 1, wxGROW|wxLEFT|wxRIGHT|wxTOP, 5);

    m_Check_ShowOutput = new wxCheckBox( itemDialog1, ID_CHECK_SHOWOUTPUT, _("Show output..."), wxDefaultPosition, wxDefaultSize, 0 );
    m_Check_ShowOutput->SetValue(true);
    if (ANote::ShowToolTips())
        m_Check_ShowOutput->SetToolTip(_("Show the comment once generated."));
    itemBoxSizer2->Add(m_Check_ShowOutput, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer41 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer41, 0, wxALIGN_RIGHT|wxALL, 5);

    wxButton* itemButton42 = new wxButton( itemDialog1, wxID_CLOSE, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer41->Add(itemButton42, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton43 = new wxButton( itemDialog1, ID_BUTTON_GENERATE, _("&Generate comment"), wxDefaultPosition, wxDefaultSize, 0 );
    if (ANote::ShowToolTips())
        itemButton43->SetToolTip(_("Generate the comment"));
    itemBoxSizer41->Add(itemButton43, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

}


/*!
 * Should we show tooltips?
 */

bool ANote::ShowToolTips()
{
    return true;
}


void ANote::OnQuit(wxCloseEvent & event)
{
	Destroy();
}


void ANote::OnCloseButton (wxCommandEvent & event)
{
	Destroy();
}


void ANote::OnButtonGenerate(wxCommandEvent & event)
{	
	int iNumOfItem = 0;
	AComment * myTempComment;
	ACommentFunction * myTempFunctionComment;
	wxString myCommentText = _T("");
	
	if(m_Notebook_General_Function->GetSelection()==0)
	{
		myTempComment = DoCommentGeneral();
	
	}
	else
	{
		myTempComment = DoCommentFunction();
	//	myCommentText = myTempFunctionComment->Write();
	//	iNumOfItem = myTempFunctionComment->ClearList();
	}
	 
	
	
		myCommentText = myTempComment->Write();	
		// delete items in the list
		iNumOfItem = myTempComment->ClearList();
			
	// show the result dlg (delete the dlg in the destructor)
	if (m_Check_ShowOutput->IsChecked()==TRUE) 
	{
		dlgResult->SetResults(myCommentText,iNumOfItem);
		dlgResult->Show(TRUE);
	}
	else
		dlgResult->Show(FALSE);
		
	// copy data to clipboard
	CopyTextToClipboard(myCommentText);
	
}

AComment * ANote::DoCommentGeneral()
{
	// get values from text ctrls
	m_CommentList.SetCommentText(COMMENT_FILE, m_General_Text_Name->GetValue());
	m_CommentList.SetCommentText(COMMENT_BRIEF,m_General_Text_Brief->GetValue());
	m_CommentList.SetCommentText(COMMENT_DESCRIPTION,m_General_Text_Description->GetValue());
	
	return &m_CommentList;
}


ACommentFunction * ANote::DoCommentFunction()
{

	wxString myTempText = m_Function_Text_Brief->GetValue();
	m_CommentFunctionList.SetCommentText(COMMENT_BRIEF, m_Function_Text_Brief->GetValue());
	m_CommentFunctionList.SetCommentText(COMMENT_DESCRIPTION,
			m_Function_Text_Description->GetValue());
	
	// get values from the list
	for (int i=0; i < m_Function_List_Param->GetItemCount(); i++)
	{
		
		ACOMMENTPOSITION iCommentType = (ACOMMENTPOSITION) m_Function_List_Param->GetParamType(m_Function_List_Param->GetItemColText(i, 2));
		m_CommentFunctionList.SetCommentFunctionList(m_Function_List_Param->GetItemColText(i, 0), 
			m_Function_List_Param->GetItemColText(i, 1), iCommentType);
	}
	
    return &m_CommentFunctionList;
}


void ANote::AuthorChange(wxString myAuthorName)
{
	m_CommentList.SetCommentText(COMMENT_AUTHOR, myAuthorName);
	m_CommentFunctionList.SetCommentText(COMMENT_AUTHOR, myAuthorName);
}

void ANote::OnAuthorTextChange (wxCommandEvent & event)
{
	AuthorChange(m_Settings_Text_Author->GetValue());
}



void ANote::OnCheckDate(wxCommandEvent & event)
{
	wxDateTime myDateTime = m_DatePickerCtrl->GetValue();
	
	if (m_Settings_Date_Check->IsChecked())
	{
		
		m_CommentList.SetCommentDate(myDateTime);
		m_CommentFunctionList.SetCommentDate(myDateTime);
	}
	else
	{
		myDateTime = wxInvalidDateTime;
		m_CommentList.SetCommentDate(myDateTime);
		m_CommentFunctionList.SetCommentDate(myDateTime);	
	}
}


void ANote::OnChangeGeneralListType(wxCommandEvent & event)
{
	if(m_General_List_Type->GetSelection()!=0)
	{
		m_General_Text_Name->SetValue(_T(""));
		m_General_Text_Name->Show(FALSE);
		m_General_Static_Name->Show(FALSE);
		m_General_Text_Brief->SetFocus();
		m_GeneralBoxPanelSizer->Layout();
		
	}
	else
	{
		m_General_Text_Name->Show(TRUE);
		m_General_Static_Name->Show(TRUE);
		m_GeneralBoxPanelSizer->Layout();
		
	}
}

void ANote::OnChangeCommentWidth(wxCommandEvent & event)
{
	m_CommentList.SetCommentWidth(m_Settings_CommentWidth->GetValue());
	m_CommentFunctionList.SetCommentWidth(m_Settings_CommentWidth->GetValue());
}

void ANote::OnChangeDate(wxDateEvent & event)
{
	wxCommandEvent myEvent;
	OnCheckDate(myEvent);
}

void ANote::CopyTextToClipboard(wxString myComment)
{
	if(wxTheClipboard->Open())
	{
	  wxTheClipboard->SetData( new wxTextDataObject(myComment) );
	  wxTheClipboard->Close();
	}
}


void ANote::OnFunctionTextChange (wxCommandEvent & event)
{	
	wxArrayString * myTokenizedString; // (m_Function_Text_Code->GetValue());
	//myTokenizedString.
	AParser myFunctionParser(m_Function_Text_Code->GetValue());
	myTokenizedString = myFunctionParser.GetParsedString();
	if (myTokenizedString != NULL)
	{
		// clear the list
		m_Function_List_Param->DeleteAllItems();
		
		for (unsigned int i=0; i < myTokenizedString->GetCount(); i++)
		{
			m_Function_List_Param->AddItemToParamList(myTokenizedString->Item(i),_T(""),COMMENT_PARAM);

		}
	}
}


void ANote::OnChangeParamType (wxCommandEvent & event)
{
	int iSelectedItem = m_Function_List_Param->GetSelectedItem();
	if (iSelectedItem != -1)
	{
		int iTempParam = m_Listparam_Choice->GetSelection();
		m_Function_List_Param->SetItemText(iSelectedItem, 2,
			m_Function_List_Param->GetParamType(iTempParam + COMMENT_PARAM));
	}
}
