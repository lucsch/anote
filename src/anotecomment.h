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


class AnoteCommentParameters{
 public:
  bool m_generic_comment;
  wxString m_gen_brief;
  wxString m_gen_filename;
  wxString m_gen_description;

  wxString m_function_brief;
  wxString m_function_description;

  struct function_parmeters{
    wxString parameters;
    wxString description;
    int type;
  };
  wxVector<function_parmeters> m_function_parameters;
  AnoteCommentParameters();
  static wxArrayString GetFunctionTypes();
  void AddFunctionParameter(const wxString & param, const wxString & desc, int type=0);
};


class AnoteComment {
 public:
  AnoteComment();
  wxString GenerateComment(AnoteCommentParameters param);
  static wxArrayString GetTemplateNames();
  void SetTemplateIndex(int mTemplateIndex);
  void SetAuthor(const wxString& mAuthor);
  void SetDate(const wxString& mDate);
  void SetCommentLength(int length);

 private:
  int m_template_index;

  static wxVector<AnoteCommentTemplate> m_templates;
  wxString m_author;
  wxString m_date;
  int m_comment_length;
  wxString _generate_simple_comment(AnoteCommentParameters param);
  wxString _generate_function_comment(AnoteCommentParameters param);
};



#endif
