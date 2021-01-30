#ifndef ANOTE_ANOTECOMMENT_H
#define ANOTE_ANOTECOMMENT_H
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

struct AnoteCommentTemplate{
  wxString m_name;
  wxString m_template;
  wxString m_begin_line_char;
  wxUniChar m_top_bottom_line_char;
};

class AnoteComment {
 public:
  AnoteComment(const wxString& brief, const wxString& filename, const wxString& desc);
  wxString GenerateComment();
  static wxArrayString GetTemplateNames();
  void SetTemplateIndex(int mTemplateIndex);

 private:
  wxString m_brief;
  wxString m_filename;
  wxString m_description;

  int m_template_index;
  static wxVector<AnoteCommentTemplate> m_templates;
};



#endif
