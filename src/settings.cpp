#include "settings.h"
#include "wx/fileconf.h"

AnoteSettings::AnoteSettings() {
  m_comment_length = 100;
  m_selected_template = 0;
  m_use_date = true;
  m_date = wxDateTime::Now();
  m_author_name = wxEmptyString;
}

bool AnoteSettings::SaveToIni() {
  wxFileConfig myConfig("Anote");
  myConfig.Write("use_date", m_use_date);
  myConfig.Write("selected_template", m_selected_template);
  myConfig.Write("comment_length", m_comment_length);
  myConfig.Write("author_name", m_author_name);
  return true;
}

bool AnoteSettings::LoadFromIni() {
  wxFileConfig myConfig("Anote");
  myConfig.Read("use_date", &m_use_date);
  myConfig.Read("selected_template", &m_selected_template);
  myConfig.Read("comment_length", &m_comment_length);
  myConfig.Read("author_name", &m_author_name);
  return true;
}
