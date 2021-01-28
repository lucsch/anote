/////////////////////////////////////////////////////////////////////////////
// Name:        anoteresults.cpp
// Purpose:     
// Author:      Lucien Schreiber
// Modified by: 
// Created:     Mon 12 Nov 09:07:11 2007
// RCS-ID:      
// Copyright:   (c) 2007 CREALP
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "../include/anoteresults.h"

////@begin XPM images
////@end XPM images


/*!
 * AnoteResults type definition
 */
IMPLEMENT_DYNAMIC_CLASS( AnoteResults, wxDialog )


/*!
 * AnoteResults event table definition
 */
BEGIN_EVENT_TABLE( AnoteResults, wxDialog )
	EVT_BUTTON(wxID_CLOSE, AnoteResults::OnCloseDialog)
END_EVENT_TABLE()


/*!
 * AnoteResults constructors
 */
AnoteResults::AnoteResults()
{
    Init();
}

AnoteResults::AnoteResults( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * AnoteResults creator
 */
bool AnoteResults::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
}


/*!
 * AnoteResults destructor
 */
AnoteResults::~AnoteResults()
{
}


/*!
 * Member initialisation
 */
void AnoteResults::Init()
{
    m_ResultTxt = NULL;
    m_ResultStatusBar = NULL;
}


/*!
 * Control creation for AnoteResults
 */
void AnoteResults::CreateControls()
{    
    AnoteResults* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    m_ResultTxt = new wxTextCtrl( itemDialog1, ID_RESULT_TXT, _T(""), wxDefaultPosition, wxSize(300, 200), wxTE_MULTILINE );
    itemBoxSizer2->Add(m_ResultTxt, 1, wxGROW|wxALL, 5);

    wxButton* itemButton4 = new wxButton( itemDialog1, wxID_CLOSE, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton4->SetDefault();
    itemBoxSizer2->Add(itemButton4, 0, wxALIGN_RIGHT|wxALL, 5);

    m_ResultStatusBar = new wxStatusBar( itemDialog1, ID_RESULT_STATUS, wxST_SIZEGRIP|wxNO_BORDER );
    m_ResultStatusBar->SetFieldsCount(1);
    itemBoxSizer2->Add(m_ResultStatusBar, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
}


/*!
 * Should we show tooltips?
 */
bool AnoteResults::ShowToolTips()
{
    return true;
}

void AnoteResults::SetResults(wxString &myResult, int iNumber)
{
	m_ResultTxt->SetValue(myResult);
	m_ResultStatusBar->SetStatusText(wxString::
		Format(_("%d Line(s) of comments copied to the clipboard"),
		iNumber));
}

void AnoteResults:: OnCloseDialog(wxCommandEvent & event)
{
	this->Hide();
	event.Skip();
}

