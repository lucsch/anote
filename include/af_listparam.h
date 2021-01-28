 /*******************************************************//**
@file af_listparam.h
@brief Derived list class used for the parameters (header)
@details This class deals with the parameters list. It
 allows adding, editing and moving items in the
 list.
This class derives from ListGenReport
@author Lucien Schreiber (c) CREALP 2007
@date 16 November 2007
 ***********************************************************/

#ifndef AF_LISTPARAM_H
#define AF_LISTPARAM_H

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// Include wxWidgets' headers
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/listgenreport.h"
#include "../include/AComment.h"



 /*******************************************************//**
@brief In charge of the ANote parameter list
@details This class is derived from the ListGenReport class
 and is dedicated to the management of the
 parameter list.
@author Lucien Schreiber (c) CREALP 2007
@date 19 November 2007
 ***********************************************************/
class AFListParam : public ListGenReport
	{
	private:
		virtual void OnDoubleClickItem(wxListEvent & event);
		void OnMySelectionChange (wxListEvent & event);
		
		wxChoice * m_ChoiceToChange;
		
	public:
		static const int ID_PARAMLIST;
		/*********************************************//**
		 @brief Parameter list contructor
		 @details This function mainly construct the
		 parameter list, This function calls
		 CreateColumns for adding the Value,
		 Comment and type columns
		 @param parent The parent window
		 @param id The windows id
		 @author Lucien Schreiber (c) CREALP
		 @date 19 November 2007
		 *************************************************/
		AFListParam(wxWindow * parent, wxWindowID id);
		/*********************************************//**
		 @brief Parameter list destructor
		 @details This function does nothing for the moment
		 @author Lucien Schreiber (c) CREALP
		 @date 19 November 2007
		 *************************************************/
		~AFListParam(); 
		/*********************************************//**
		 @brief return the type of the parameter string
		 @details Convert a wxString into a parameter type
		 (int). Actually only the folowing values
		 are managed : COMMENT_RETURN,
		 @return return an integer of ACOMMENTPOSITION
		 type (COMMENT_RETURN or COMMENT_PARAM)
		 @param myTextParam the string to convert into
		 ACOMMENTPOSITION
		 @author Lucien Schreiber (c) CREALP
		 @date 19 November 2007
		 *************************************************/
		int GetParamType (wxString myTextParam);
		
		wxString GetParamType (int imyType);
		/*********************************************//**
		 @brief Add an entry to the parameter list
		 @details This function adds an entry to the
		 parameter list
		 @param myValue Value of the first column
		 @param myComment Value of the second column
		 @param type the parameter type : actually only
		 COMMENT_RETURN and COMMENT_PARAM are
		 managed
		 @author Lucien Schreiber (c) CREALP
		 @date 19 November 2007
		 *************************************************/
		void AddItemToParamList(wxString myValue, wxString myComment, ACOMMENTPOSITION type);
		void SetChoiceList (wxChoice * myChoiceList);
		DECLARE_EVENT_TABLE();
	};


#endif
