 /*****************************************************************//**
@file anoteconfig.cpp
@brief deal with configuration file (ini)
@details This class is based on wxFileConfig for storing program's
 configuration. Ini files are made for all plateform
@author Lucien Schreiber (c) CREALP 2007
@date 26 November 2007
 *********************************************************************/
#include "../include/anoteconfig.h"

AnoteConfig::AnoteConfig()
{
	m_pConfig = new wxFileConfig();
	
	// init CONFIG_KEY_TYPE_STRING values
	m_Config_String[CONFIG_DATE]= _("Date");
	m_Config_String[CONFIG_AUTHOR] = _("Author");
	m_Config_String[CONFIG_COMMENT_WIDTH] = _("Comment Width");
	m_Config_String[CONFIG_DATE_CHECKED] = _("Date Checked");
	m_Config_String[CONFIG_SHOW_RESULT] = _("Show Result");
}


AnoteConfig::~AnoteConfig()
{
	delete m_pConfig;
}

void AnoteConfig::SetConfigItemDate(wxDateTime myDate)
{
	
	m_pConfig->Write(m_Config_String[CONFIG_DATE], myDate.FormatDate());
}

void AnoteConfig::SetConfigItemAuthor (wxString myAuthor)
{
	m_pConfig->Write(m_Config_String[CONFIG_AUTHOR], myAuthor);
}

void AnoteConfig::SetConfigItemCommentWidth(int iCommentWidth)
{
	m_pConfig->Write(m_Config_String[CONFIG_COMMENT_WIDTH], iCommentWidth);
}

void AnoteConfig::SetConfigItemCheckDate (bool isDateChecked)
{
	m_pConfig->Write(m_Config_String[CONFIG_DATE_CHECKED], isDateChecked);
}


void AnoteConfig::SetConfigItemShowResult (bool showResult)
{
	m_pConfig->Write(m_Config_String[CONFIG_SHOW_RESULT], showResult);
}

bool AnoteConfig::GetConfigItemDate(wxDateTime & myDate)
{	
	wxString myTempDateString = _T("");
	wxDateTime myTempDateTime;

	if (m_pConfig->Read(m_Config_String[CONFIG_DATE], &myTempDateString))
	{
		myTempDateTime.ParseDate(myTempDateString);
		if (myTempDateTime.IsValid())
		{
			myDate = myTempDateTime;
			return TRUE;
		}
	}
	return FALSE;
}

bool AnoteConfig::GetConfigItemAuthor (wxString & myAuthor)
{
	wxString myTempAuthor = _("");
	
	if (m_pConfig->Read(m_Config_String[CONFIG_AUTHOR], &myTempAuthor))
	{
		if (myTempAuthor.IsEmpty() == FALSE)
		{
			myAuthor = myTempAuthor;
			return TRUE;
		}
	}
	return FALSE;
}

int AnoteConfig::GetConfigItemCommentWidth ()
{
	int myTempCommentWidth = -1;
	
	if (m_pConfig->Read(m_Config_String[CONFIG_COMMENT_WIDTH], &myTempCommentWidth))
	{
		return myTempCommentWidth;
	}
	return -1;
}


bool AnoteConfig::GetConfigItemCheckDate()
{
	bool myCheckDateValue = TRUE;
	
	if (m_pConfig->Read(m_Config_String[CONFIG_DATE_CHECKED], &myCheckDateValue))
	{
		return myCheckDateValue;
	}
	
	return TRUE;
}

bool AnoteConfig::GetConfigItemShowResult()
{
	bool myShowResult = TRUE;
	
	if (m_pConfig->Read(m_Config_String[CONFIG_SHOW_RESULT], &myShowResult))
	{
		return myShowResult;
	}
	
	return TRUE;

}
