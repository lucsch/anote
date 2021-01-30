#include "settingsdialog.h"
#include "anotecomment.h"

const AnoteSettings& SettingsDialog::GetSettings() const {
  return m_settings;
}

void SettingsDialog::SetSettings(const AnoteSettings& mSettings) {
  m_settings = mSettings;
}

bool SettingsDialog::TransferDataToWindow() {
  m_ctrl_template->SetSelection(m_settings.m_selected_template);
  m_ctrl_comment_width->SetValue(m_settings.m_comment_length);
  m_ctrl_author->SetValue(m_settings.m_author_name);
  m_ctrl_check_date->SetValue(m_settings.m_use_date);
  m_ctrl_date->SetValue(m_settings.m_date);
  return true;
}

bool SettingsDialog::TransferDataFromWindow() {
  m_settings.m_selected_template = m_ctrl_template->GetSelection();
  m_settings.m_comment_length = m_ctrl_comment_width->GetValue();
  m_settings.m_author_name = m_ctrl_author->GetValue();
  m_settings.m_use_date = m_ctrl_check_date->IsChecked();
  m_settings.m_date = m_ctrl_date->GetValue();
  return true;
}

SettingsDialog::SettingsDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
                               const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style) {
  _create_controls();

  m_ctrl_template->Set(AnoteComment::GetTemplateNames());
}

void SettingsDialog::_create_controls() {
  SetSizeHints(wxDefaultSize, wxDefaultSize);

  wxBoxSizer* bSizer6;
  bSizer6 = new wxBoxSizer(wxVERTICAL);

  wxStaticBoxSizer* sbSizer4;
  sbSizer4 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Parameters")), wxVERTICAL);

  wxFlexGridSizer* fgSizer4;
  fgSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer4->AddGrowableCol(1);
  fgSizer4->SetFlexibleDirection(wxBOTH);
  fgSizer4->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  wxStaticText* m_statitext32;
  m_statitext32 =
      new wxStaticText(sbSizer4->GetStaticBox(), wxID_ANY, _("Template:"), wxDefaultPosition, wxDefaultSize, 0);
  m_statitext32->Wrap(-1);
  fgSizer4->Add(m_statitext32, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  wxArrayString m_ctrl_templateChoices;
  m_ctrl_template =
      new wxChoice(sbSizer4->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_ctrl_templateChoices, 0);
  m_ctrl_template->SetSelection(0);
  fgSizer4->Add(m_ctrl_template, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, 5);

  wxStaticText* m_staticText8;
  m_staticText8 =
      new wxStaticText(sbSizer4->GetStaticBox(), wxID_ANY, _("Comment width:"), wxDefaultPosition, wxDefaultSize, 0);
  m_staticText8->Wrap(-1);
  fgSizer4->Add(m_staticText8, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  m_ctrl_comment_width = new wxSpinCtrl(sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
                                        wxDefaultSize, wxSP_ARROW_KEYS, 0, 300, 100);
  fgSizer4->Add(m_ctrl_comment_width, 0, wxALL | wxEXPAND, 5);

  sbSizer4->Add(fgSizer4, 1, wxEXPAND, 5);

  bSizer6->Add(sbSizer4, 0, wxEXPAND | wxALL, 5);

  wxStaticBoxSizer* sbSizer5;
  sbSizer5 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Options")), wxVERTICAL);

  wxFlexGridSizer* fgSizer3;
  fgSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer3->AddGrowableCol(1);
  fgSizer3->SetFlexibleDirection(wxBOTH);
  fgSizer3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  wxStaticText* m_staticText6;
  m_staticText6 =
      new wxStaticText(sbSizer5->GetStaticBox(), wxID_ANY, _("Author:"), wxDefaultPosition, wxDefaultSize, 0);
  m_staticText6->Wrap(-1);
  fgSizer3->Add(m_staticText6, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  m_ctrl_author =
      new wxTextCtrl(sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(400, -1), 0);
  fgSizer3->Add(m_ctrl_author, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  m_ctrl_check_date =
      new wxCheckBox(sbSizer5->GetStaticBox(), wxID_ANY, _("Date:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
  fgSizer3->Add(m_ctrl_check_date, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  m_ctrl_date = new wxDatePickerCtrl(sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultDateTime, wxDefaultPosition,
                                     wxDefaultSize, wxDP_DEFAULT);
  fgSizer3->Add(m_ctrl_date, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, 5);

  sbSizer5->Add(fgSizer3, 1, wxEXPAND | wxALL, 5);

  bSizer6->Add(sbSizer5, 1, wxEXPAND | wxALL, 5);

  m_ctrl_btn = new wxStdDialogButtonSizer();
  m_ctrl_btnOK = new wxButton(this, wxID_OK);
  m_ctrl_btn->AddButton(m_ctrl_btnOK);
  m_ctrl_btnCancel = new wxButton(this, wxID_CANCEL);
  m_ctrl_btn->AddButton(m_ctrl_btnCancel);
  m_ctrl_btn->Realize();

  bSizer6->Add(m_ctrl_btn, 0, wxEXPAND | wxALL, 5);

  SetSizer(bSizer6);
  Layout();
  bSizer6->Fit(this);
}

