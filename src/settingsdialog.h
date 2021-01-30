#ifndef ANOTE_SETTINGSDIALOG_H
#define ANOTE_SETTINGSDIALOG_H
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "settings.h"
#include "wx/datectrl.h"
#include "wx/spinctrl.h"

class SettingsDialog : public wxDialog {
 private:
  void _create_controls();
  AnoteSettings m_settings;

 public:
  const AnoteSettings& GetSettings() const;
  void SetSettings(const AnoteSettings& mSettings);

 protected:
  wxChoice* m_ctrl_template;
  wxSpinCtrl* m_ctrl_comment_width;
  wxTextCtrl* m_ctrl_author;
  wxCheckBox* m_ctrl_check_date;
  wxDatePickerCtrl* m_ctrl_date;
  wxStdDialogButtonSizer* m_ctrl_btn;
  wxButton* m_ctrl_btnOK;
  wxButton* m_ctrl_btnCancel;

 public:
  SettingsDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Settings"),
                 const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
                 long style = wxDEFAULT_DIALOG_STYLE);

  virtual bool TransferDataToWindow();
  virtual bool TransferDataFromWindow();

};

#endif