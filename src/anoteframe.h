#ifndef TEST_WXWIDGETS_MAINFRAME_H
#define TEST_WXWIDGETS_MAINFRAME_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "settings.h"
#include "wx/listctrl.h"
#include "wx/notebook.h"

class AnoteFrame : public wxFrame {
 public:
  AnoteFrame(const wxString &title);

  void OnQuit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnGenerate(wxCommandEvent & event);
  void OnSettings(wxCommandEvent & event);

 private:
  void _create_menubar();
  void _create_statusbar();
  void _connect_events();
  void _create_controls();

  AnoteSettings m_settings;

 protected:
  wxNotebook* m_ctrl_notebook;
  wxPanel* m_ctrl_panel_general;
  wxTextCtrl* m_ctrl_general_brief;
  wxTextCtrl* m_ctrl_general_filename;
  wxTextCtrl* m_ctrl_general_description;
  wxPanel* m_ctrl_panel_function;
  wxTextCtrl* m_ctrl_function_def;
  wxButton* m_ctrl_paste_btn;
  wxTextCtrl* m_ctrl_function_brief;
  wxTextCtrl* m_ctrl_function_desc;
  wxListCtrl* m_ctrl_function_list;

  wxMenuItem* m_menu_generate;
  wxMenuItem* m_menu_settings;
  wxMenuItem* m_menu_exit;
  wxMenuItem* m_menu_about;
};

#endif
