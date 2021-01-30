
#include "anoteframe.h"
#include "settingsdialog.h"
#include "anotecomment.h"
#include "bitmap.h"
#include "wx/clipbrd.h"
#include "wx/tokenzr.h"

extern const char* Anote_MAJOR_VERSION;
extern const char* Anote_MINOR_VERSION;
extern const char* GIT_REV;
extern const char* GIT_TAG;
extern const char* GIT_BRANCH;
extern const char* GIT_NUMBER;

AnoteFrame::AnoteFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
  wxInitAllImageHandlers();
  initialize_images();
  wxIconBundle myBundle;
  wxIcon frame_icon16;
  frame_icon16.CopyFromBitmap(*_img_anote_icon16);
  wxIcon frame_icon128;
  frame_icon128.CopyFromBitmap(*_img_anote_icon128);
  myBundle.AddIcon(frame_icon16);
  myBundle.AddIcon(frame_icon128);
  SetIcons(myBundle);

  _create_controls();
  _create_menubar();
  _create_statusbar();
  _connect_events();

  m_ctrl_function_list->AppendColumn("Name", wxLIST_FORMAT_LEFT, 100);
  m_ctrl_function_list->AppendColumn("Description", wxLIST_FORMAT_LEFT, 400);
  m_ctrl_function_list->AppendColumn("Type", wxLIST_FORMAT_LEFT, 200);
  m_settings.LoadFromIni();
}

void AnoteFrame::_connect_events() {
  Bind(wxEVT_MENU, &AnoteFrame::OnQuit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &AnoteFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &AnoteFrame::OnGenerate, this, m_menu_generate->GetId());
  Bind(wxEVT_MENU, &AnoteFrame::OnSettings, this, m_menu_settings->GetId());
  Bind(wxEVT_BUTTON, &AnoteFrame::OnFunctionPaste, this, m_ctrl_paste_btn->GetId());
  Bind(wxEVT_TEXT, &AnoteFrame::OnFunctionTxtUpdate, this, m_ctrl_function_def->GetId());
  Bind(wxEVT_LIST_ITEM_ACTIVATED, &AnoteFrame::OnFunctionListDoubleClick, this, m_ctrl_function_list->GetId());
  Bind(wxEVT_LIST_KEY_DOWN, &AnoteFrame::OnFunctionListDelete, this, m_ctrl_function_list->GetId());
}

void AnoteFrame::_create_statusbar() {
  SetStatusBarPane(-1);
  CreateStatusBar(1);
  wxString myVersion;
  myVersion << "Version: " << Anote_MAJOR_VERSION << "." << Anote_MINOR_VERSION << "." << GIT_NUMBER;
  myVersion << " (" << GIT_REV << ")";
  SetStatusText(myVersion, 0);
}

void AnoteFrame::_create_menubar() {
  wxMenuBar* m_menubar1;
  m_menubar1 = new wxMenuBar(0);
  wxMenu* filemenu;
  filemenu = new wxMenu();
  m_menu_generate = new wxMenuItem(filemenu, wxID_ANY, wxString(_("Generate comment")) + wxT('\t') + wxT("Ctrl+G"),
                                   wxEmptyString, wxITEM_NORMAL);
  filemenu->Append(m_menu_generate);

  m_menu_settings = new wxMenuItem(filemenu, wxID_PREFERENCES, wxString(_("Settings...")) + wxT('\t') + wxT("Ctrl+,"),
                                   wxEmptyString, wxITEM_NORMAL);
  filemenu->Append(m_menu_settings);

  m_menu_exit = new wxMenuItem(filemenu, wxID_EXIT, wxString(_("Quit")) + wxT('\t') + wxT("Ctrl+Q"), wxEmptyString,
                               wxITEM_NORMAL);
  filemenu->Append(m_menu_exit);

  m_menubar1->Append(filemenu, _("&File"));

  wxMenu* helpmenu;
  helpmenu = new wxMenu();
  m_menu_about = new wxMenuItem(helpmenu, wxID_ABOUT, wxString(_("About...")), wxEmptyString, wxITEM_NORMAL);
  helpmenu->Append(m_menu_about);

  m_menubar1->Append(helpmenu, _("Help"));

  this->SetMenuBar(m_menubar1);
}

void AnoteFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
  Close(true);
}

void AnoteFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
  wxMessageBox(wxString::Format("Welcome to Anote!\n"
                                "\n"
                                "%s\n"
                                "running under %s.",
                                wxVERSION_STRING, wxGetOsDescription()),
               "About Anote", wxOK | wxICON_INFORMATION, this);
}

void AnoteFrame::OnGenerate(wxCommandEvent& WXUNUSED(event)) {
  // getting all comment parameters
  AnoteCommentParameters param;
  param.m_gen_filename = m_ctrl_general_filename->GetValue();
  param.m_gen_brief = m_ctrl_general_brief->GetValue();
  param.m_gen_description = m_ctrl_general_description->GetValue();
  param.m_function_brief = m_ctrl_function_brief->GetValue();
  param.m_function_description = m_ctrl_function_desc->GetValue();
  for(int i = 0; i<m_ctrl_function_list->GetItemCount();i++){
    param.AddFunctionParameter(m_ctrl_function_list->GetItemText(i, 0),
                               m_ctrl_function_list->GetItemText(i, 1),
                               AnoteCommentParameters::GetFunctionTypes().Index(m_ctrl_function_list->GetItemText(i,2)));
  }
  if(m_ctrl_notebook->GetSelection() == 1){
    param.m_generic_comment = false;
  }

  // sending settigns to the comment
  AnoteComment myComment;
  myComment.SetTemplateIndex(m_settings.m_selected_template);
  myComment.SetAuthor(m_settings.m_author_name);
  myComment.SetCommentLength(m_settings.m_comment_length);
  if (m_settings.m_use_date){
    myComment.SetDate(m_settings.m_date.FormatISODate());
  }

  // generating comments
  wxString my_txt = myComment.GenerateComment(param);
  if (my_txt == wxEmptyString) {
    wxLogWarning(_("Comment is empty!"));
    return;
  }

  // copy to the clipboard
  if (wxTheClipboard->Open()) {
    wxTheClipboard->SetData(new wxTextDataObject(my_txt));
    wxTheClipboard->Close();
  }
}

void AnoteFrame::OnSettings(wxCommandEvent& WXUNUSED(event)) {
  SettingsDialog my_dlg(this);
  my_dlg.SetSettings(m_settings);
  if (my_dlg.ShowModal() != wxID_OK){
    return;
  }
  m_settings = my_dlg.GetSettings();
  m_settings.SaveToIni();
}

void AnoteFrame::OnFunctionPaste(wxCommandEvent& WXUNUSED(event)) {
  if (wxTheClipboard->Open()) {
    if (wxTheClipboard->IsSupported(wxDF_TEXT) || wxTheClipboard->IsSupported(wxDF_UNICODETEXT) || wxTheClipboard->IsSupported(wxDF_HTML)) {
      wxTextDataObject data;
      wxTheClipboard->GetData(data);
      m_ctrl_function_def->SetValue(data.GetText());
    }
    wxTheClipboard->Close();
  }
}

void AnoteFrame::OnFunctionTxtUpdate(wxCommandEvent& event) {
  if(m_ctrl_function_def->GetValue() == wxEmptyString){
    return;
  }

  wxArrayString my_function_parameters_txt;
  wxStringTokenizer tokenizer(m_ctrl_function_def->GetValue(), " ");
  while ( tokenizer.HasMoreTokens() ){
    my_function_parameters_txt.Add(tokenizer.GetNextToken());
  }

  m_ctrl_function_list->DeleteAllItems();
  for(unsigned int i = 0; i<my_function_parameters_txt.GetCount(); i++){
    m_ctrl_function_list->InsertItem(i, my_function_parameters_txt[i]);
    m_ctrl_function_list->SetItem(i, 2, AnoteCommentParameters::GetFunctionTypes()[0]);
  }

}

void AnoteFrame::OnFunctionListDoubleClick(wxListEvent& event) {
  // get item value
  wxString myparam = m_ctrl_function_list->GetItemText(event.GetIndex(), 0);
  wxString mydesc = m_ctrl_function_list->GetItemText(event.GetIndex(), 1);
  wxString mytype = m_ctrl_function_list->GetItemText(event.GetIndex(), 2);

  // get column clicked
  wxPoint mouse_pos = m_ctrl_function_list->ScreenToClient(wxGetMousePosition());
#if defined(__WXMSW__)  // this works on Windows but didn't work on osx.
  int x = -m_ctrl_function_list->GetScrollPos(wxHORIZONTAL);
#else
  wxPoint my_scroll_pos = m_ctrl_function_list->CalcScrolledPosition(mouse_pos);
  int x = my_scroll_pos.x - mouse_pos.x;
#endif
  int column;
  for (column = 0; column < m_ctrl_function_list->GetColumnCount(); column++) {
    x += m_ctrl_function_list->GetColumnWidth(column);
    if (x > mouse_pos.x) {
      break;
    }
  }
  // wxLogDebug("column clicked: %d", column);
  if (column == 1) {  // description
    wxTextEntryDialog dlg(this, _("Description"), _("Description"), mydesc);
    if (dlg.ShowModal() != wxID_OK) {
      return;
    }
    m_ctrl_function_list->SetItem(event.GetIndex(), 1, dlg.GetValue());
    return;
  }
  if (column == 2) {
    wxSingleChoiceDialog dlg(this, _("Type"), _("Select a type:"), AnoteCommentParameters::GetFunctionTypes());
    dlg.SetSelection(AnoteCommentParameters::GetFunctionTypes().Index(mytype));
    if (dlg.ShowModal() != wxID_OK) {
      return;
    }
    m_ctrl_function_list->SetItem(event.GetIndex(), 2, dlg.GetStringSelection());
  }
}

void AnoteFrame::OnFunctionListDelete(wxListEvent& event) {
  int my_key_code = event.GetKeyCode();
  if (my_key_code == WXK_DELETE || my_key_code == WXK_BACK){
    m_ctrl_function_list->DeleteItem(event.GetIndex());
  }
  event.Skip();
}

void AnoteFrame::_create_controls() {
  this->SetSizeHints(wxDefaultSize, wxDefaultSize);

  wxBoxSizer* bSizer1;
  bSizer1 = new wxBoxSizer(wxVERTICAL);

  wxPanel* m_panel1;
  m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
  wxBoxSizer* bSizer2;
  bSizer2 = new wxBoxSizer(wxVERTICAL);

  m_ctrl_notebook = new wxNotebook(m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
  m_ctrl_panel_general = new wxPanel(m_ctrl_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
  wxBoxSizer* bSizer4;
  bSizer4 = new wxBoxSizer(wxVERTICAL);

  wxFlexGridSizer* fgSizer1;
  fgSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
  fgSizer1->AddGrowableCol(1);
  fgSizer1->SetFlexibleDirection(wxBOTH);
  fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  wxStaticText* m_staticText2;
  m_staticText2 = new wxStaticText(m_ctrl_panel_general, wxID_ANY, _("Brief:"), wxDefaultPosition, wxDefaultSize, 0);
  m_staticText2->Wrap(-1);
  fgSizer1->Add(m_staticText2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  m_ctrl_general_brief =
      new wxTextCtrl(m_ctrl_panel_general, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
  fgSizer1->Add(m_ctrl_general_brief, 0, wxALL | wxEXPAND, 5);

  fgSizer1->Add(0, 0, 1, wxEXPAND, 5);

  wxStaticText* m_staticText4;
  m_staticText4 =
      new wxStaticText(m_ctrl_panel_general, wxID_ANY, _("File name:"), wxDefaultPosition, wxDefaultSize, 0);
  m_staticText4->Wrap(-1);
  fgSizer1->Add(m_staticText4, 0, wxALL, 5);

  m_ctrl_general_filename =
      new wxTextCtrl(m_ctrl_panel_general, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
  fgSizer1->Add(m_ctrl_general_filename, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

  wxStaticText* m_staticText6;
  m_staticText6 =
      new wxStaticText(m_ctrl_panel_general, wxID_ANY, _("*Only for files"), wxDefaultPosition, wxDefaultSize, 0);
  m_staticText6->Wrap(-1);
  fgSizer1->Add(m_staticText6, 0, wxALL, 5);

  bSizer4->Add(fgSizer1, 0, wxEXPAND, 5);

  wxStaticBoxSizer* sbSizer1;
  sbSizer1 = new wxStaticBoxSizer(new wxStaticBox(m_ctrl_panel_general, wxID_ANY, _("Description")), wxVERTICAL);

  m_ctrl_general_description = new wxTextCtrl(sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
                                              wxSize(-1, -1), wxTE_MULTILINE);
  sbSizer1->Add(m_ctrl_general_description, 1, wxALL | wxEXPAND, 5);

  bSizer4->Add(sbSizer1, 1, wxEXPAND | wxALL, 5);

  m_ctrl_panel_general->SetSizer(bSizer4);
  m_ctrl_panel_general->Layout();
  bSizer4->Fit(m_ctrl_panel_general);
  m_ctrl_notebook->AddPage(m_ctrl_panel_general, _("General"), false);
  m_ctrl_panel_function = new wxPanel(m_ctrl_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
  wxBoxSizer* bSizer6;
  bSizer6 = new wxBoxSizer(wxVERTICAL);

  wxFlexGridSizer* fgSizer2;
  fgSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
  fgSizer2->AddGrowableCol(1);
  fgSizer2->SetFlexibleDirection(wxBOTH);
  fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  wxStaticText* m_staticText7;
  m_staticText7 =
      new wxStaticText(m_ctrl_panel_function, wxID_ANY, _("Function definition:"), wxDefaultPosition, wxDefaultSize, 0);
  m_staticText7->Wrap(-1);
  fgSizer2->Add(m_staticText7, 0, wxALL, 5);

  m_ctrl_function_def =
      new wxTextCtrl(m_ctrl_panel_function, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
  fgSizer2->Add(m_ctrl_function_def, 0, wxALL | wxEXPAND, 5);

  m_ctrl_paste_btn = new wxButton(m_ctrl_panel_function, wxID_ANY, _("Paste"), wxDefaultPosition, wxDefaultSize, 0);
  fgSizer2->Add(m_ctrl_paste_btn, 0, wxALL, 5);

  wxStaticText* m_staticText8;
  m_staticText8 = new wxStaticText(m_ctrl_panel_function, wxID_ANY, _("Brief:"), wxDefaultPosition, wxDefaultSize, 0);
  m_staticText8->Wrap(-1);
  fgSizer2->Add(m_staticText8, 0, wxALL, 5);

  m_ctrl_function_brief =
      new wxTextCtrl(m_ctrl_panel_function, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
  fgSizer2->Add(m_ctrl_function_brief, 0, wxALL | wxEXPAND, 5);

  fgSizer2->Add(0, 0, 1, wxEXPAND, 5);

  bSizer6->Add(fgSizer2, 0, wxEXPAND, 5);

  wxStaticBoxSizer* sbSizer2;
  sbSizer2 = new wxStaticBoxSizer(new wxStaticBox(m_ctrl_panel_function, wxID_ANY, _("Description")), wxVERTICAL);

  m_ctrl_function_desc =
      new wxTextCtrl(sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
  sbSizer2->Add(m_ctrl_function_desc, 2, wxALL | wxEXPAND, 5);

  bSizer6->Add(sbSizer2, 2, wxEXPAND | wxALL, 5);

  wxStaticBoxSizer* sbSizer3;
  sbSizer3 = new wxStaticBoxSizer(new wxStaticBox(m_ctrl_panel_function, wxID_ANY, _("Parameters")), wxVERTICAL);

  m_ctrl_function_list = new wxListCtrl(sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                        wxLC_EDIT_LABELS | wxLC_REPORT);
  sbSizer3->Add(m_ctrl_function_list, 2, wxALL | wxEXPAND, 5);

  bSizer6->Add(sbSizer3, 3, wxEXPAND | wxALL, 5);

  m_ctrl_panel_function->SetSizer(bSizer6);
  m_ctrl_panel_function->Layout();
  bSizer6->Fit(m_ctrl_panel_function);
  m_ctrl_notebook->AddPage(m_ctrl_panel_function, _("Function"), false);

  bSizer2->Add(m_ctrl_notebook, 1, wxEXPAND | wxALL, 5);

  wxBoxSizer* bSizer3;
  bSizer3 = new wxBoxSizer(wxVERTICAL);

  bSizer2->Add(bSizer3, 1, wxEXPAND, 5);

  m_panel1->SetSizer(bSizer2);
  m_panel1->Layout();
  bSizer2->Fit(m_panel1);
  bSizer1->Add(m_panel1, 1, wxEXPAND, 5);

  this->SetSizer(bSizer1);
  this->Layout();
}
