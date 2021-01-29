#ifndef ANOTE_ANOTECOMMENT_H
#define ANOTE_ANOTECOMMENT_H
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class AnoteComment {
 public:
  AnoteComment(const wxString& brief, const wxString& filename, const wxString& desc);
  wxString GenerateComment();

 private:
  wxString m_brief;
  wxString m_filename;
  wxString m_description;

  const static wxString m_template;
};

#endif
