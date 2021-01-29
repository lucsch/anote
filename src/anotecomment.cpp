#include "anotecomment.h"

#include <wx/unichar.h>

const wxString AnoteComment::m_template = "///%s\n%s\n///%s";

AnoteComment::AnoteComment(const wxString& brief, const wxString& filename, const wxString& desc) {
  m_brief = brief;
  m_description = desc;
  m_filename = filename;
}

wxString AnoteComment::GenerateComment() {
  int number_stars = 97;
  wxString stars_text(wxUniChar('/'), number_stars);
  wxString body_text;
  if (m_filename != wxEmptyString) {
    body_text << "/// @file " << m_filename << "\n";
  }
  if (m_brief != wxEmptyString) {
    body_text << "/// @brief " << m_brief << "\n";
  }
  if (m_description != wxEmptyString) {
    wxString myDescription_multiline = m_description;
    myDescription_multiline.Replace("\n", "\n ///    ");
    body_text << "/// @details " << myDescription_multiline << "\n";
  }
  body_text = body_text.Trim();
  wxString myComment = wxString::Format(m_template, stars_text, body_text, stars_text);
  wxLogWarning(myComment);
  return myComment;
}
