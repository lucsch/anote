/////////////////////////////////////////////////////////////////////////////
// Name:        anoteresults.h
// Purpose:     
// Author:      Lucien Schreiber
// Modified by: 
// Created:     Mon 12 Nov 09:07:11 2007
// RCS-ID:      
// Copyright:   (c) 2007 CREALP
// Licence:     
/////////////////////////////////////////////////////////////////////////////


#ifndef _ANOTERESULTS_H_
#define _ANOTERESULTS_H_

/*!
 * Includes
 */

////@begin includes
#include "wx/statusbr.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxStatusBar;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_ANOTERESULTS 10018
#define ID_RESULT_TXT 10022
#define ID_RESULT_STATUS 10023
#define SYMBOL_ANOTERESULTS_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_ANOTERESULTS_TITLE _("Results")
#define SYMBOL_ANOTERESULTS_IDNAME ID_ANOTERESULTS
#define SYMBOL_ANOTERESULTS_SIZE wxSize(400, 300)
#define SYMBOL_ANOTERESULTS_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * AnoteResults class declaration
 */

class AnoteResults: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( AnoteResults )
    DECLARE_EVENT_TABLE()
	
	void OnCloseDialog(wxCommandEvent & event);

public:
    /// Constructors
    AnoteResults();
    AnoteResults( wxWindow* parent, wxWindowID id = SYMBOL_ANOTERESULTS_IDNAME, const wxString& caption = SYMBOL_ANOTERESULTS_TITLE, const wxPoint& pos = SYMBOL_ANOTERESULTS_POSITION, const wxSize& size = SYMBOL_ANOTERESULTS_SIZE, long style = SYMBOL_ANOTERESULTS_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ANOTERESULTS_IDNAME, const wxString& caption = SYMBOL_ANOTERESULTS_TITLE, const wxPoint& pos = SYMBOL_ANOTERESULTS_POSITION, const wxSize& size = SYMBOL_ANOTERESULTS_SIZE, long style = SYMBOL_ANOTERESULTS_STYLE );

    /// Destructor
    ~AnoteResults();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin AnoteResults member variables
    wxTextCtrl* m_ResultTxt;
    wxStatusBar* m_ResultStatusBar;
////@end AnoteResults member variables
	
	void SetResults(wxString &myResult, int iNumber);
};

#endif
    // _ANOTERESULTS_H_
