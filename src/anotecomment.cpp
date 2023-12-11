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
    t2.m_begin_line_char = "#";
    t2.m_top_bottom_line_char = '#';

    v.push_back(t1);
    v.push_back(t2);
    return v;
};


wxVector<AnoteCommentTemplate> AnoteComment::m_templates = init();

AnoteComment::AnoteComment() {
    m_template_index = 0;
    m_comment_length = 100;
}

wxString AnoteComment::GenerateComment(AnoteCommentParameters param) {
    wxASSERT(m_templates.size() > m_template_index);
    wxString comment_txt;
    switch (param.m_selected_panel) {
        case 0: // Simple panel
            comment_txt = _generate_simple_comment(param);
            break;
        case 1: // Function panel
            comment_txt = _generate_function_comment(param);
            break;
        case 2: // MCU panel
            comment_txt = _generate_mcu_comment(param);
            break;
    }
    return comment_txt;
}

wxString AnoteComment::_generate_mcu_comment(AnoteCommentParameters param) {
    AnoteCommentTemplate actual_template = m_templates[m_template_index];
    int number_stars = m_comment_length - actual_template.m_begin_line_char.Length();
    wxString stars_text(actual_template.m_top_bottom_line_char, number_stars);
    wxString body_text;

    if (param.m_mcu_pins % 2 != 0) {
        wxLogError("Number of pins should be even!");
        return wxEmptyString;
    }
    if (param.m_mcu_type == 0) { // LEFT / RIGHT type
        body_text << "         ______  \n";
        for (int i = 0; i < param.m_mcu_pins / 2; i++) {
            if (i == (param.m_mcu_pins / 2)-1){
                body_text << "    ----|______|----    " << "\n";
                continue;
            }
            body_text << "    ----|      |----    " << "\n";
        }
    } else {  // SQUARE TYPE
        body_text = _("Not implemented");
    }
    wxString myComment = wxString::Format(actual_template.m_template, stars_text, body_text, stars_text);
    return myComment;
}

wxString AnoteComment::_generate_simple_comment(AnoteCommentParameters param) {
    AnoteCommentTemplate actual_template = m_templates[m_template_index];
    int number_stars = m_comment_length - actual_template.m_begin_line_char.Length();
    wxString stars_text(actual_template.m_top_bottom_line_char, number_stars);
    wxString body_text;
    if (param.m_gen_filename != wxEmptyString) {
        body_text << actual_template.m_begin_line_char << " @file " << param.m_gen_filename << "\n";
    }
    if (param.m_gen_brief != wxEmptyString) {
        body_text << actual_template.m_begin_line_char << " @brief " << param.m_gen_brief << "\n";
    }
    if (param.m_gen_description != wxEmptyString) {
        wxString myDescription_multiline = param.m_gen_description;
        myDescription_multiline.Replace("\n", "\n " + actual_template.m_begin_line_char);
        body_text << actual_template.m_begin_line_char << " @details " << myDescription_multiline << "\n";
    }
    if (m_author != wxEmptyString) {
        body_text << actual_template.m_begin_line_char << " @author " << m_author << "\n";
    }
    if (m_date != wxEmptyString) {
        body_text << actual_template.m_begin_line_char << " @date " << m_date << "\n";
    }

    body_text = body_text.Trim();
    wxString myComment = wxString::Format(actual_template.m_template, stars_text, body_text, stars_text);
    return myComment;
}

wxString AnoteComment::_generate_function_comment(AnoteCommentParameters param) {
    AnoteCommentTemplate actual_template = m_templates[m_template_index];
    int number_stars = m_comment_length - actual_template.m_begin_line_char.Length();
    wxString stars_text(actual_template.m_top_bottom_line_char, number_stars);
    wxString body_text;
    if (param.m_function_brief != wxEmptyString) {
        body_text << actual_template.m_begin_line_char << " @brief " << param.m_function_brief << "\n";
    }
    if (param.m_function_description != wxEmptyString) {
        wxString myDescription_multiline = param.m_function_description;
        myDescription_multiline.Replace("\n", "\n " + actual_template.m_begin_line_char);
        body_text << actual_template.m_begin_line_char << " @details " << myDescription_multiline << "\n";
    }
    // iterate all parameters
    for (wxVector<AnoteCommentParameters::function_parmeters>::iterator it = param.m_function_parameters.begin();
         it != param.m_function_parameters.end(); ++it) {
        body_text << actual_template.m_begin_line_char << "    "
                  << AnoteCommentParameters::GetFunctionTypes()[it->type];
        body_text << " " << it->parameters << "  " << it->description << "\n";
    }

    if (m_author != wxEmptyString) {
        body_text << actual_template.m_begin_line_char << " @author " << m_author << "\n";
    }
    if (m_date != wxEmptyString) {
        body_text << actual_template.m_begin_line_char << " @date " << m_date << "\n";
    }

    body_text = body_text.Trim();
    wxString myComment = wxString::Format(actual_template.m_template, stars_text, body_text, stars_text);
    return myComment;
}

wxArrayString AnoteComment::GetTemplateNames() {
    wxArrayString myNames;
    for (wxVector<AnoteCommentTemplate>::iterator it = AnoteComment::m_templates.begin();
         it != AnoteComment::m_templates.end(); ++it) {
        myNames.Add(it->m_name);
    }
    return myNames;
}

void AnoteComment::SetTemplateIndex(int mTemplateIndex) {
    m_template_index = mTemplateIndex;
}

void AnoteComment::SetAuthor(const wxString &mAuthor) {
    m_author = mAuthor;
}

void AnoteComment::SetDate(const wxString &mDate) {
    m_date = mDate;
}

void AnoteComment::SetCommentLength(int length) {
    m_comment_length = length;
}

AnoteCommentParameters::AnoteCommentParameters() {
    m_selected_panel = 0;
}

wxArrayString AnoteCommentParameters::GetFunctionTypes() {
    wxArrayString my_types;
    my_types.push_back("@param[in]");
    my_types.push_back("@param[out]");
    my_types.push_back("@param[in,out]");
    my_types.push_back("@return");
    return my_types;
}

void AnoteCommentParameters::AddFunctionParameter(const wxString &param, const wxString &desc, int type) {
    function_parmeters myparam;
    myparam.parameters = param;
    myparam.description = desc;
    myparam.type = type;
    m_function_parameters.push_back(myparam);
}
