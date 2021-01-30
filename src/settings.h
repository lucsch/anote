#ifndef ANOTE_SETTINGS_H
#define ANOTE_SETTINGS_H

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class AnoteSettings {
 public:
  wxString m_author_name;
  int m_comment_length;
  bool m_use_date;
  wxDateTime m_date;
  int m_selected_template;

  AnoteSettings();
  bool SaveToIni();
  bool LoadFromIni();
};

#endif
