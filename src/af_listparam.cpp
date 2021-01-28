 /*******************************************************//**
@file af_listparam.cpp
@brief Derived list class used for the parameters
 (Definition)
@details This class deals with the parameters list. It
 allows adding, editing and moving items in the
 list.
This class derives from ListGenReport
@author Lucien Schreiber (c) CREALP 2007
@date 16 November 2007
 ***********************************************************/


#include "../include/af_listparam.h"


const int AFListParam::ID_PARAMLIST = wxID_ANY;

AFListParam::AFListParam(wxWindow * parent, wxWindowID  id) 
	: ListGenReport(parent,id)
{
	// Create columns
	wxArrayString myColNames;
	wxArrayInt myColsWidths;
	
	myColNames.Add(_("Value"));
	myColNames.Add(_("Comment"));
	myColNames.Add(_("Type"));
	
	myColsWidths.Add(100);
	myColsWidths.Add(300);	
	myColsWidths.Add(80);
	
	CreateColumns(&myColNames, &myColsWidths);
	
	m_ChoiceToChange = NULL;
	
}

AFListParam::~AFListParam()
{

}


BEGIN_EVENT_TABLE(AFListParam,ListGenReport)
	EVT_LIST_ITEM_SELECTED(ID_PARAMLIST, AFListParam::OnMySelectionChange) 
END_EVENT_TABLE()

int AFListParam::GetParamType (wxString myTextParam)
{
	if (myTextParam == _T("return"))
	{
		return COMMENT_RETURN;
	}
	else
		return COMMENT_PARAM;
}

wxString AFListParam::GetParamType (int imyType)
{
	switch (imyType)
	{
		case COMMENT_RETURN:
			return _T("return");
			break;
		default:
			return _T("param");
			break;
	}
}


void AFListParam::AddItemToParamList(wxString myValue, wxString myComment, ACOMMENTPOSITION type)
{
	int iPos = GetItemCount();
	
	AddItemToList(myValue);
	SetItemText(iPos, 1, myComment);
	
	switch (type)
	{
		case COMMENT_PARAM:
			SetItemText(iPos, 2, _("param"));
			break;
		case COMMENT_RETURN:
			SetItemText(iPos, 2, _("return"));
			break;
	}
}

void AFListParam::SetChoiceList (wxChoice * myChoiceList)
{
	m_ChoiceToChange = myChoiceList;
}

void AFListParam::OnDoubleClickItem(wxListEvent & event)
{
		wxString myAcutalValue = GetItemColText(event.GetIndex(), 1);
		wxTextEntryDialog myTextDlg(this, _("Modify comment :"),_("Comment"));
		myTextDlg.SetValue(myAcutalValue);
		myTextDlg.ShowModal();
		SetItemText(event.GetIndex(),1,myTextDlg.GetValue());
}


void AFListParam::OnMySelectionChange (wxListEvent & event)
{
	if (m_ChoiceToChange != NULL)
	{
		wxString myItemValue = GetItemColText(event.GetIndex(),2);
		int imyItemValueInt = GetParamType(myItemValue) - COMMENT_PARAM;
		m_ChoiceToChange->SetSelection(imyItemValueInt);
	}
		
}
