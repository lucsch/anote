 /*******************************************************//**
@file AParser.cpp
@brief Parse text into tokens (definition)
@details This parser was made to compute a string (a function
 description for exemple) and extract all the token 
for process.
This file is part of the ANote project
@author Lucien Schreiber (c) CREALP 2007
@date 15 November 2007
 ***********************************************************/

#include "../include/AParser.h"

AParser::AParser()
{
	m_StringToParse = _T("");
	m_StringSeparator = _T(" ");
}

AParser::AParser(wxString  myParseString)
{
	SetParseString(myParseString);
	m_StringSeparator = _T(" (),;*&");
}

AParser::~AParser()
{

}

void AParser::SetParseString(wxString & myParseString)
{
	m_StringToParse = myParseString;
}

void AParser::SetStringSeparator(wxString mySeparator)
{
	m_StringSeparator = mySeparator;
}

wxArrayString * AParser::GetParsedString()
{
	if(ParseString())
		return &m_StringArray;
	else 
		return NULL;
}

bool AParser::ParseString()
{
	wxString myExtractedString = _T("");
	
	wxStringTokenizer tkz(m_StringToParse,m_StringSeparator);
	while (tkz.HasMoreTokens())
	{
		myExtractedString = tkz.GetNextToken();
		if (myExtractedString.Len() > 0)
		{
			m_StringArray.Add(myExtractedString);
		}
		
	}
	if (m_StringArray.GetCount() > 0)
	{
		return TRUE;
	}
	return FALSE;
}
