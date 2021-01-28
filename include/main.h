// $Rev: 29 $


#ifndef MAIN_H
#define MAIN_H

////@begin includes
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/spinctrl.h"
#include "wx/datectrl.h"
#include "wx/dateevt.h"
#include "wx/datetime.h"
#include <wx/sizer.h>
#include <wx/clipbrd.h>
#include <wx/sysopt.h>
////@end includes

#include "../include/AComment.h"
#include "../include/anoteresults.h"
#include "../include/AParser.h"
#include "../include/af_listparam.h"
#include "../include/anoteconfig.h"

class wxNotebook;
class wxListCtrl;
class wxSpinCtrl;
class wxDatePickerCtrl;



////@begin control identifiers
#define ID_ANOTE 10000
#define ID_NOTEBOOK1 10001
#define ID_PANEL_COMMENT 10002
#define ID_NOTEBOOK2 10004
#define ID_PANEL_GENERAL 10005
#define ID_GENERAL_LIST_TYPE 10015
#define wxID_GENERAL_STATIC_NAME 10021
#define ID_GENERAL_TEXT_NAME 10016
#define ID_GENERAL_TEXT_BRIEF 10017
#define ID_GENERAL_TEXT_DESCRIPTION 10020
#define ID_PANEL_FUNCTION 10007
#define ID_FUNCTION_TEXT_CODE 10006
#define ID_FUNCTION_TEXT_BRIEF 10010
#define ID_FUNCTION_TEXT_DESCRIPTION 10011
#define ID_FUNCTION_LIST_PARAM 10012
#define ID_LISTPARAM_CHOICE 10024
#define ID_PANEL_SETTINGS 10003
#define ID_SETTINGS_TEXT_AUTHOR 10008
#define ID_SETTINGS_COMMENTWIDTH 10009
#define ID_SETTINGS_DATE_CHECK 10018
#define ID_DATEPICKERCTRL 10014
#define ID_CHECK_SHOWOUTPUT 10019
#define ID_BUTTON_GENERATE 10013
#define SYMBOL_ANOTE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_ANOTE_TITLE _("ANote")
#define SYMBOL_ANOTE_IDNAME ID_ANOTE
#define SYMBOL_ANOTE_SIZE wxDefaultSize
#define SYMBOL_ANOTE_POSITION wxDefaultPosition
////@end control identifiers
#define SYMBOL_ANOTE_REVISION _T("$Revision: 29 $")

class AnoteApp : public wxApp
{
public:
	virtual bool OnInit();
	
};
IMPLEMENT_APP(AnoteApp);



class ANote: public wxDialog
{    
    //DECLARE_DYNAMIC_CLASS( ANote )
	DECLARE_EVENT_TABLE()
	AComment m_CommentList;
	ACommentFunction m_CommentFunctionList;
	AnoteResults * dlgResult;
	AnoteConfig m_Config;
	
public:
    /// Constructors
    ANote();
    ANote( wxWindow* parent, wxWindowID id = SYMBOL_ANOTE_IDNAME, const wxString& caption = SYMBOL_ANOTE_TITLE, const wxPoint& pos = SYMBOL_ANOTE_POSITION, const wxSize& size = SYMBOL_ANOTE_SIZE, long style = SYMBOL_ANOTE_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ANOTE_IDNAME, const wxString& caption = SYMBOL_ANOTE_TITLE, const wxPoint& pos = SYMBOL_ANOTE_POSITION, const wxSize& size = SYMBOL_ANOTE_SIZE, long style = SYMBOL_ANOTE_STYLE );

    /// Destructor
    ~ANote();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();


    static bool ShowToolTips();


private :

	void PostInit();

	void OnQuit (wxCloseEvent & event);
	void OnCloseButton (wxCommandEvent & event);
	void OnButtonGenerate (wxCommandEvent & event);
	void OnAuthorTextChange (wxCommandEvent & event);
	void OnCheckDate (wxCommandEvent & event);
	void OnChangeDate (wxDateEvent & event);
	void OnChangeGeneralListType(wxCommandEvent & event);
	void OnChangeCommentWidth(wxCommandEvent & event);
	void OnFunctionTextChange (wxCommandEvent & event);
	void OnChangeParamType (wxCommandEvent & event);
	
	void AuthorChange(wxString myAuthorName);
	
	void CopyTextToClipboard(wxString myComment);
	
	
	AComment * DoCommentGeneral();
	ACommentFunction * DoCommentFunction();
	
	// controls variables
  wxNotebook* m_Notebook_Comment_Settings;
    wxNotebook* m_Notebook_General_Function;
    wxBoxSizer* m_GeneralBoxPanelSizer;
    wxFlexGridSizer* m_General_Sizer;
    wxChoice* m_General_List_Type;
    wxStaticText* m_General_Static_Name;
    wxTextCtrl* m_General_Text_Name;
    wxTextCtrl* m_General_Text_Brief;
    wxTextCtrl* m_General_Text_Description;
    wxTextCtrl* m_Function_Text_Code;
    wxTextCtrl* m_Function_Text_Brief;
    wxTextCtrl* m_Function_Text_Description;
    AFListParam* m_Function_List_Param;
    wxChoice* m_Listparam_Choice;
    wxTextCtrl* m_Settings_Text_Author;
    wxSpinCtrl* m_Settings_CommentWidth;
    wxCheckBox* m_Settings_Date_Check;
    wxDatePickerCtrl* m_DatePickerCtrl;
    wxCheckBox* m_Check_ShowOutput;

};


#endif
