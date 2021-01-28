 /*******************************************************//**
@file AParser.h
@brief Parse text into tokens (header)
@details This parser was made to compute a string (a function
 description for exemple) and extract all the token 
for process.
This file is part of the ANote project
@author Lucien Schreiber (c) CREALP 2007
@date 15 November 2007
 ***********************************************************/

#ifndef APARSER_H
#define APARSER_H

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// Include wxWidgets' headers
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/arrstr.h>
#include <wx/tokenzr.h>

 /*******************************************************//**
@brief Basic text-parsing class
@details This class is intented to be a simple text-parser. A
 new child class has to be created for parsing function 
 text correctely
@author Lucien Schreiber (c) CREALP 2007
@date 15 November 2007
 ***********************************************************/
class AParser
{
	private:
		wxString m_StringToParse;
		wxString m_StringSeparator;
		wxArrayString m_StringArray;
		
		bool ParseString();
	
	public:
		AParser();
		AParser(wxString myParseString);
		void SetParseString(wxString & myParseString);
		void SetStringSeparator (wxString mySeparator);
		wxArrayString * GetParsedString ();
		~AParser();
};




#endif
