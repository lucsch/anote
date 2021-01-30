#include "anotecomment.h"

#include <wx/unichar.h>

wxVector<AnoteCommentTemplate> init() {
  wxVector<AnoteCommentTemplate> v;
  v.reserve(2);
  AnoteCommentTemplate t1;
  t1.m_name = "C++ Triple Dash (///)";
  t1.m_template = "///%s\n%s\n///%s";
  t1.m_begin_line_char = "///";
  t1.m_top_bottom_line_char = '/';

  AnoteCommentTemplate t2;
  t2.m_name = "Python Hashtag (#)";
  t2.m_template = "###%s\n%s\n###%s";
  t2.m_begin_line_char = "###";
  t2.m_top_bottom_line_char = '#';

  v.push_back(t1);
  v.push_back(t2);
  return v;
};

wxVector<AnoteCommentTemplate> AnoteComment::m_templates = init();

AnoteComment::AnoteComment(const wxString& brief, const wxString& filename, const wxString& desc) {
  m_brief = brief;
  m_description = desc;
  m_filename = filename;

  m_template_index = 0;
}

wxString AnoteComment::GenerateComment() {
  int number_stars = 97;
  wxASSERT(m_templates.size() > m_template_index);
  AnoteCommentTemplate actual_template = m_templates[m_template_index];

  wxString stars_text(actual_template.m_top_bottom_line_char, number_stars);
  wxString body_text;
  if (m_filename != wxEmptyString) {
    body_text << actual_template.m_begin_line_char << " @file " << m_filename << "\n";
  }
  if (m_brief != wxEmptyString) {
    body_text << actual_template.m_begin_line_char << " @brief " << m_brief << "\n";
  }
  if (m_description != wxEmptyString) {
    wxString myDescription_multiline = m_description;
    myDescription_multiline.Replace("\n", "\n " + actual_template.m_begin_line_char);
    body_text << actual_template.m_begin_line_char << " @details " << myDescription_multiline << "\n";
  }
  if (m_author != wxEmptyString){
    body_text << actual_template.m_begin_line_char << " @author " << m_author << "\n";
  }
  if (m_date != wxEmptyString){
    body_text << actual_template.m_begin_line_char << " @date " << m_date << "\n";
  }

  body_text = body_text.Trim();
  wxString myComment = wxString::Format(actual_template.m_template, stars_text, body_text, stars_text);
  return myComment;
}

wxArrayString AnoteComment::GetTemplateNames() {
  wxArrayString myNames;
  for(wxVector<AnoteCommentTemplate>::iterator it = AnoteComment::m_templates.begin() ; it != AnoteComment::m_templates.end(); ++it){
    myNames.Add(it->m_name);
  }
  return myNames;
}

void AnoteComment::SetTemplateIndex(int mTemplateIndex) {
  m_template_index = mTemplateIndex;
}

void AnoteComment::SetAuthor(const wxString& mAuthor) {
  m_author = mAuthor;
}

void AnoteComment::SetDate(const wxString& mDate) {
  m_date = mDate;
}
