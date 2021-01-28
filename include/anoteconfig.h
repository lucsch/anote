 /*****************************************************************//**
@file anoteconfig.h
@brief deal with configuration file (ini)
@details This class is based on wxFileConfig for storing program's
 configuration. Ini files are made for all plateform
@author Lucien Schreiber (c) CREALP 2007
@date 26 November 2007
 *********************************************************************/
#ifndef ANOTECONFIG_H
#define ANOTECONFIG_H

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// Include wxWidgets' headers
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/fileconf.h>

enum CONFIG_KEY_TYPE
{
	CONFIG_DATE=0,
	CONFIG_DATE_CHECKED,
	CONFIG_AUTHOR,
	CONFIG_COMMENT_WIDTH,
	CONFIG_SHOW_RESULT
	
};

typedef wxString CONFIG_KEY_TYPE_STRING;

 /*****************************************************************//**
@brief deal with configuration file (ini)
@details This class is based on wxFileConfig for storing program's
 configuration. Ini files are made for all plateform. This is a
 specialisation of wxFileConfig for Anote to allow simpler acces to
 config file. To use AnoteConfig, just use SetConfigItem() and
 GetConfigItem() with one of the CONFIG_KEY_TYPE().
@author Lucien Schreiber (c) CREALP 2007
@date 26 November 2007
 *********************************************************************/
class AnoteConfig
{
	private:
			wxFileConfig * m_pConfig;
			CONFIG_KEY_TYPE_STRING m_Config_String[5];
			
	public:
		AnoteConfig();
		~AnoteConfig();
		
		void SetConfigItemDate(wxDateTime myDate);
		void SetConfigItemAuthor (wxString myAuthor);
		void SetConfigItemCommentWidth (int iCommentWidth);
		void SetConfigItemCheckDate (bool isDateChecked);
		void SetConfigItemShowResult (bool showResult);
		
		bool GetConfigItemDate(wxDateTime & myDate);
		bool GetConfigItemAuthor (wxString & myAuthor);
		int GetConfigItemCommentWidth ();	
		bool GetConfigItemCheckDate ();
		bool GetConfigItemShowResult();
};


#endif
