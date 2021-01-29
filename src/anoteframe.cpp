
#include "anoteframe.h"

#include "bitmap.h"

extern const char *Anote_MAJOR_VERSION;
extern const char *Anote_MINOR_VERSION;
extern const char *GIT_REV;
extern const char *GIT_TAG;
extern const char *GIT_BRANCH;
extern const char *GIT_NUMBER;

AnoteFrame::AnoteFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800,600)) {
  wxInitAllImageHandlers();
  initialize_images();
  wxIcon frame_icon;
  frame_icon.CopyFromBitmap(*_img_anote_icon);
  SetIcon(frame_icon);

  _create_controls();
  _create_menubar();
  _create_statusbar();
  _connect_events();
}

void AnoteFrame::_connect_events() {
  Bind(wxEVT_MENU, &AnoteFrame::OnQuit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &AnoteFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &AnoteFrame::OnGenerate, this, m_menu_generate->GetId());
}

void AnoteFrame::_create_statusbar() {
  CreateStatusBar(2);
  wxString myVersion;
  myVersion << "Version: " << Anote_MAJOR_VERSION << "." << Anote_MINOR_VERSION << "." << GIT_NUMBER;
  myVersion << "(" << GIT_REV << ")";
  SetStatusText(myVersion, 1);
}

void AnoteFrame::_create_menubar() {
  wxMenuBar* m_menubar1;
  m_menubar1 = new wxMenuBar( 0 );
  wxMenu* filemenu;
  filemenu = new wxMenu();
  m_menu_generate = new wxMenuItem( filemenu, wxID_ANY, wxString( _("Generate comment") ) + wxT('\t') + wxT("Ctrl+G"), wxEmptyString, wxITEM_NORMAL );
  filemenu->Append( m_menu_generate );

  m_menu_exit = new wxMenuItem( filemenu, wxID_EXIT, wxString( _("Quit") ) + wxT('\t') + wxT("Ctrl+Q"), wxEmptyString, wxITEM_NORMAL );
  filemenu->Append( m_menu_exit );

  m_menubar1->Append( filemenu, _("&File") );

  wxMenu* helpmenu;
  helpmenu = new wxMenu();
  m_menu_about = new wxMenuItem( helpmenu, wxID_ABOUT, wxString( _("About...") ) , wxEmptyString, wxITEM_NORMAL );
  helpmenu->Append( m_menu_about );

  m_menubar1->Append( helpmenu, _("Help") );

  this->SetMenuBar( m_menubar1 );
}

void AnoteFrame::OnQuit(wxCommandEvent &WXUNUSED(event)) {
  Close(true);
}

void AnoteFrame::OnAbout(wxCommandEvent &WXUNUSED(event)) {
  wxMessageBox(wxString::Format("Welcome to Anote!\n"
                                "\n"
                                "%s\n"
                                "running under %s.",
                                wxVERSION_STRING, wxGetOsDescription()),
               "About Anote", wxOK | wxICON_INFORMATION, this);
}

void AnoteFrame::OnGenerate(wxCommandEvent &WXUNUSED(event)) {
  wxLogError("Generating comments here!!!!");
}

void AnoteFrame::_create_controls() {
  this->SetSizeHints( wxDefaultSize, wxDefaultSize );

  wxBoxSizer* bSizer1;
  bSizer1 = new wxBoxSizer( wxVERTICAL );

  wxPanel* m_panel1;
  m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
  wxBoxSizer* bSizer2;
  bSizer2 = new wxBoxSizer( wxVERTICAL );

  m_ctrl_notebook = new wxNotebook( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
  m_ctrl_panel_general = new wxPanel( m_ctrl_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
  wxBoxSizer* bSizer4;
  bSizer4 = new wxBoxSizer( wxVERTICAL );

  wxFlexGridSizer* fgSizer1;
  fgSizer1 = new wxFlexGridSizer( 0, 3, 0, 0 );
  fgSizer1->AddGrowableCol( 1 );
  fgSizer1->SetFlexibleDirection( wxBOTH );
  fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

  wxStaticText* m_staticText2;
  m_staticText2 = new wxStaticText( m_ctrl_panel_general, wxID_ANY, _("Brief:"), wxDefaultPosition, wxDefaultSize, 0 );
  m_staticText2->Wrap( -1 );
  fgSizer1->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

  m_ctrl_general_brief = new wxTextCtrl( m_ctrl_panel_general, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  fgSizer1->Add( m_ctrl_general_brief, 0, wxALL|wxEXPAND, 5 );


  fgSizer1->Add( 0, 0, 1, wxEXPAND, 5 );

  wxStaticText* m_staticText4;
  m_staticText4 = new wxStaticText( m_ctrl_panel_general, wxID_ANY, _("File name:"), wxDefaultPosition, wxDefaultSize, 0 );
  m_staticText4->Wrap( -1 );
  fgSizer1->Add( m_staticText4, 0, wxALL, 5 );

  m_ctrl_general_filename = new wxTextCtrl( m_ctrl_panel_general, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  fgSizer1->Add( m_ctrl_general_filename, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

  wxStaticText* m_staticText6;
  m_staticText6 = new wxStaticText( m_ctrl_panel_general, wxID_ANY, _("*Only for files"), wxDefaultPosition, wxDefaultSize, 0 );
  m_staticText6->Wrap( -1 );
  fgSizer1->Add( m_staticText6, 0, wxALL, 5 );


  bSizer4->Add( fgSizer1, 0, wxEXPAND, 5 );

  wxStaticBoxSizer* sbSizer1;
  sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_ctrl_panel_general, wxID_ANY, _("Description") ), wxVERTICAL );

  m_ctrl_general_description = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
  sbSizer1->Add( m_ctrl_general_description, 1, wxALL|wxEXPAND, 5 );


  bSizer4->Add( sbSizer1, 1, wxEXPAND|wxALL, 5 );


  m_ctrl_panel_general->SetSizer( bSizer4 );
  m_ctrl_panel_general->Layout();
  bSizer4->Fit( m_ctrl_panel_general );
  m_ctrl_notebook->AddPage( m_ctrl_panel_general, _("General"), false );
  m_ctrl_panel_function = new wxPanel( m_ctrl_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
  wxBoxSizer* bSizer6;
  bSizer6 = new wxBoxSizer( wxVERTICAL );

  wxFlexGridSizer* fgSizer2;
  fgSizer2 = new wxFlexGridSizer( 0, 3, 0, 0 );
  fgSizer2->AddGrowableCol( 1 );
  fgSizer2->SetFlexibleDirection( wxBOTH );
  fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

  wxStaticText* m_staticText7;
  m_staticText7 = new wxStaticText( m_ctrl_panel_function, wxID_ANY, _("Function definition:"), wxDefaultPosition, wxDefaultSize, 0 );
  m_staticText7->Wrap( -1 );
  fgSizer2->Add( m_staticText7, 0, wxALL, 5 );

  m_ctrl_function_def = new wxTextCtrl( m_ctrl_panel_function, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  fgSizer2->Add( m_ctrl_function_def, 0, wxALL|wxEXPAND, 5 );

  m_ctrl_paste_btn = new wxButton( m_ctrl_panel_function, wxID_ANY, _("Paste"), wxDefaultPosition, wxDefaultSize, 0 );
  fgSizer2->Add( m_ctrl_paste_btn, 0, wxALL, 5 );

  wxStaticText* m_staticText8;
  m_staticText8 = new wxStaticText( m_ctrl_panel_function, wxID_ANY, _("Brief:"), wxDefaultPosition, wxDefaultSize, 0 );
  m_staticText8->Wrap( -1 );
  fgSizer2->Add( m_staticText8, 0, wxALL, 5 );

  m_ctrl_function_brief = new wxTextCtrl( m_ctrl_panel_function, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  fgSizer2->Add( m_ctrl_function_brief, 0, wxALL|wxEXPAND, 5 );


  fgSizer2->Add( 0, 0, 1, wxEXPAND, 5 );


  bSizer6->Add( fgSizer2, 0, wxEXPAND, 5 );

  wxStaticBoxSizer* sbSizer2;
  sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_ctrl_panel_function, wxID_ANY, _("Description") ), wxVERTICAL );

  m_ctrl_function_desc = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  sbSizer2->Add( m_ctrl_function_desc, 2, wxALL|wxEXPAND, 5 );


  bSizer6->Add( sbSizer2, 2, wxEXPAND|wxALL, 5 );

  wxStaticBoxSizer* sbSizer3;
  sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_ctrl_panel_function, wxID_ANY, _("Parameters") ), wxVERTICAL );

  m_ctrl_function_list = new wxListCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_EDIT_LABELS|wxLC_ICON|wxLC_REPORT );
  sbSizer3->Add( m_ctrl_function_list, 2, wxALL|wxEXPAND, 5 );


  bSizer6->Add( sbSizer3, 3, wxEXPAND|wxALL, 5 );


  m_ctrl_panel_function->SetSizer( bSizer6 );
  m_ctrl_panel_function->Layout();
  bSizer6->Fit( m_ctrl_panel_function );
  m_ctrl_notebook->AddPage( m_ctrl_panel_function, _("Function"), false );

  bSizer2->Add( m_ctrl_notebook, 1, wxEXPAND | wxALL, 5 );

  wxBoxSizer* bSizer3;
  bSizer3 = new wxBoxSizer( wxVERTICAL );


  bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );


  m_panel1->SetSizer( bSizer2 );
  m_panel1->Layout();
  bSizer2->Fit( m_panel1 );
  bSizer1->Add( m_panel1, 1, wxEXPAND, 5 );


  this->SetSizer( bSizer1 );
  this->Layout();

}

