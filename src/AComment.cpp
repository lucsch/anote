 /*******************************************************//**
@file AComment.cpp
@brief Class for building comments (Definition)
@details This file contains all methods and functions required
 for dealing with the comments.
@author Lucien Schreiber (c) CREALP 2007
@date 15 November 2007
 ***********************************************************/
#include "../include/AComment.h"

ACommentItem::ACommentItem()
{
	m_Tag = _T("");
	m_Text = _T("");
}

ACommentItem::~ACommentItem()
{

}

wxString ACommentItem::WriteItem()
{
	wxString MyText = _T("");
	MyText.Append(GetTag());
	MyText.Append(_T(" "));
	MyText.Append(m_Text);
	
	if (MyText.Len() > 1)
	{
		MyText.Append(_T("\n"));
		
		// remove first white characters
		//MyText.Trim(FALSE);
	}
	return MyText;
}

void ACommentItem::SetValue(wxString myValue)
{
	m_Text = myValue;
}

void ACommentItem::SetTag(wxString myTag)
{
	m_Tag = myTag;
}

wxString ACommentItem::SplitText(wxString szText, int iTextWidth)
{
	int iStartPosition = 0;
	int iTextLen = szText.Len();
	wxString myTempString = _T("");
	wxString myModifiedString = _T("");
	int iFirstLineWidth = iTextWidth - GetTag().Len() -1; // remove 1 for white space
	bool isFisrtLine = TRUE;
	int iCuted = 0;
	
	
	// check for text width greather than 0
	// otherwise do nothing
	if(iTextWidth != 0)
	{
		
		while (iStartPosition < iTextLen)
		{
			// first line, remove width of tag
			if (isFisrtLine)
			{
				
				isFisrtLine=FALSE;
				
				myTempString = szText.Mid(iStartPosition, iFirstLineWidth);
				if (SearchForSpaceToCut(myTempString, iCuted, 
										iStartPosition+iFirstLineWidth, iTextLen))
				{
					iStartPosition += iCuted;
				}
				else
				{
					iStartPosition += iFirstLineWidth;
				}
			}
			// normal line, remove nothing
			else
			{
				myTempString = szText.Mid(iStartPosition, iTextWidth);
				
				if (SearchForSpaceToCut(myTempString, iCuted,
										iStartPosition+iTextWidth, iTextLen))
				{
					iStartPosition += iCuted;
				}
				else
				{
					iStartPosition += iTextWidth;
				}
				
			}
			myModifiedString.Append(myTempString);
			// don't add a carriage return if last line.
			if (iStartPosition < iTextLen)
			{
				myModifiedString.Append(_T("\n"));
			}
			
		}
	}
	return myModifiedString.Trim();	
}


bool ACommentItem::SearchForSpaceToCut (wxString & myStringToCut, int & iCutedWidth, int iStop, int iLen)
{
	
	if (iStop < iLen)
	{
		for (int i=myStringToCut.Len(); i > 0; i--)
		{
			if (myStringToCut.GetChar(i) == ' ')
			{
				iCutedWidth = i;
				myStringToCut = myStringToCut.Mid(0, i);
				return TRUE;
			}
		}
	}
	return FALSE;

}

/**************** CLASSE AUTHOR ****************/
ACommentItemAuthor::ACommentItemAuthor()
{
	WriteTag(_T(""));
}

ACommentItemAuthor::~ACommentItemAuthor()
{

}

void ACommentItemAuthor::WriteTag(wxString myTagText)
{
	SetTag(_T("@author"));
}

void ACommentItemAuthor::WriteText(wxString myAuthor)
{
	SetValue(myAuthor);
}


/*************** CLASSE BRIEF ****************/
ACommentItemBrief::ACommentItemBrief()
{
	m_TextWidth = 0;
	WriteTag(_T(""));
}

ACommentItemBrief::~ACommentItemBrief()
{

}

void ACommentItemBrief::SetTextWidth(int myTextWidth)
{
	m_TextWidth = myTextWidth;
}

void ACommentItemBrief::WriteTag(wxString myTagText)
{
	SetTag(_T("@brief"));
}

void ACommentItemBrief::WriteText(wxString myBrief)
{
	SetValue(SplitText(myBrief, m_TextWidth));
}




/******************* CLASS description *****************/
ACommentItemDescription::ACommentItemDescription()
{
	m_TextWidth = 0;
	WriteTag(_T(""));
}

ACommentItemDescription::~ACommentItemDescription()
{

}

void ACommentItemDescription::SetTextWidth(int myTextWidth)
{
	m_TextWidth = myTextWidth;
}

void ACommentItemDescription::WriteTag(wxString myTagText)
{
	
	SetTag(_T("@details"));
}

void ACommentItemDescription::WriteText(wxString myDescription)
{
	
	SetValue(SplitText(myDescription, m_TextWidth));
}


/********************** CLASSE DATE *************************/
ACommentItemDate::ACommentItemDate()
{
	WriteTag(_T(""));
}

ACommentItemDate::~ACommentItemDate()
{

}

void ACommentItemDate::WriteTag(wxString myTagText)
{
	SetTag(_T("@date"));
}

void ACommentItemDate::WriteText(wxString myDate)
{
	SetValue(myDate);
}

void ACommentItemDate::WriteDate(wxDateTime &myDate)
{	
	//wxString myDateText = myDate.GetWeekDayName(myDate.GetWeekDay());
	//myDateText.Append()
	
	//wxString myDateText = myDate.FormatDate();
	wxString myDateText = myDate.Format(_T("%d %B %Y"));
	
	WriteText(myDateText);
}

/********************** CLASSE FILE **************************/
ACommentItemFile::ACommentItemFile()
{
	WriteTag(_T(""));
}

ACommentItemFile::~ACommentItemFile()
{

}

void ACommentItemFile::WriteTag(wxString myTagText)
{
	SetTag(_T("@file"));
}

void ACommentItemFile::WriteText(wxString myFile)
{
	SetValue(myFile);
}

/********************** CLASSE DECORATION ***********************/
ACommentItemDecoration::ACommentItemDecoration()
{
	m_WithOfDecoration = 0;
}

ACommentItemDecoration::~ACommentItemDecoration()
{
	
}

void ACommentItemDecoration::WriteTag(wxString myTagText)
{
	SetTag(_T(""));
}

void ACommentItemDecoration::WriteText(wxString myDecoration)
{
	SetValue(myDecoration);
}

void ACommentItemDecoration::SetWidthOfDecoration(int myWidth, bool bBegin)
{
	wxString myTempDecoration = _T("");

	// if bBegin == true we made the first decoration
	if (bBegin)
	{
		myTempDecoration = _T("/");
	}
	else 
		myTempDecoration = _T("****");
		
	// add all the required characters
	myTempDecoration.Append('*',myWidth-5);
	
	
	if (bBegin)
	{
		myTempDecoration.Append(_T("//**"));
	}
	else
	{
		myTempDecoration.Append(_T("/"));
	}
	
	// call write decoration to store the decoration.
	WriteText(myTempDecoration);
}




/*********************** CLASS FUNCTION  ****************/
ACommentItemFunction::ACommentItemFunction()
{
	m_TextWidth = 50;
}

ACommentItemFunction::~ACommentItemFunction()
{

}

void ACommentItemFunction::SetTextWidth(int myWidth)
{
	m_TextWidth = myWidth;
}

void ACommentItemFunction::WriteTag(wxString myTagFunction)
{
	SetTag(myTagFunction);
}


void ACommentItemFunction::WriteFunctionTag(wxString myVal, ACOMMENTPOSITION itemType)
{
	wxString myTempTag = _T("@");
	
	switch (itemType)
	{
		case COMMENT_RETURN:
			myTempTag.Append(_T("return "));
			break;
		default:
			myTempTag.Append(_T("param "));
			myTempTag.Append(myVal);
			break;
	}
	
	WriteTag(myTempTag);
}

void ACommentItemFunction::WriteText(wxString myFunctionComment)
{
	SetValue(SplitText(myFunctionComment, m_TextWidth));
}

/*********************** LISTE OF COMMENTS ****************/
#include <wx/listimpl.cpp> 
WX_DEFINE_LIST(ACommentClassItemList);

AComment::AComment()
{
	m_List.DeleteContents(TRUE);
	 
	 m_CommentFileTxt = _T("");
	 m_CommentBriefTxt = _T("");
	 m_CommentDescriptionTxt =_T("");
	 m_CommentAuthorTxt = _T("");
	 // default width change it using SetCommentWidth()
	 m_CommentWidth = 80;

}

AComment::~AComment()
{
	m_List.DeleteContents(TRUE);
}

void AComment::AddItem(ACommentItem * myItem)
{
	ACommentClassItem * TheNewItem = new ACommentClassItem;
	TheNewItem->m_CommentItem = myItem;
	

		m_List.Append(TheNewItem);
	
	
}

ACommentItem * AComment::GetItem(int iIndex)
{
	ACommentClassItemList::Node * myNode = m_List.Item(iIndex);
	
	if (myNode != NULL) 
	{
		ACommentClassItem * ReturnedItem = myNode->GetData();
		return (ReturnedItem->m_CommentItem);
	}
	return NULL;
	
}

int AComment::GetItemCount()
{
	return m_List.GetCount();
}



wxString AComment::Write()
{
	// create the comment
	MakeComment();
	
	wxString myCommentString = _T("");
	
	ACommentClassItemList::Node * myNode = m_List.GetFirst();
	if (myNode != NULL)
	{
		while (myNode)
		{
			ACommentClassItem * myItem = myNode->GetData();
			
			myCommentString.Append(myItem->m_CommentItem->WriteItem());
			
			myNode = myNode->GetNext();
		}
	}
	return myCommentString;
}



bool AComment::GetItemByTag(wxString szTag, ACommentItem  *myReturnedItem)
{
	wxString myListTag = _T("");
	
	// search the list
	ACommentClassItemList::Node * myNode = m_List.GetFirst();
	
	if (myNode != NULL)
	{
		while (myNode)
		{
			ACommentClassItem * myItem = myNode->GetData();
			
			myListTag = myItem->m_CommentItem->GetTag();
			if (myListTag == szTag)
			{
				myReturnedItem = myItem->m_CommentItem;
				return TRUE;
			}
			
			myNode = myNode->GetNext();
		}
	}
	return FALSE;
}

void AComment::SetCommentText(ACOMMENTPOSITION itemPosition, wxString myText)
{
	switch (itemPosition)
	{
		case COMMENT_FILE:
			m_CommentFileTxt = myText;
			break;
		case COMMENT_BRIEF:
			m_CommentBriefTxt = myText;
			break;
		case COMMENT_DESCRIPTION:
			m_CommentDescriptionTxt = myText;
			break;
		case COMMENT_AUTHOR:
			m_CommentAuthorTxt = myText;
			break;
	}
}

 void AComment::SetCommentWidth(int iCommentWidth)
{
	m_CommentWidth = iCommentWidth;
}

int AComment::MakeComment()
{
	MakeCommentDecoration(TRUE);
	MakeCommentFile();
	MakeCommentBrief();
	MakeCommentDescription();
	MakeCommentAuthor();
	MakeCommentDate();
	MakeCommentDecoration(FALSE);
	return GetItemCount();
}

int AComment::ClearList()
{
	int iListCount = m_List.GetCount();
	m_List.DeleteContents(TRUE);
	m_List.Clear();
	return iListCount;
}

void AComment::SetCommentDate(wxDateTime &myDate)
{
	m_Date = myDate;
}


void AComment::MakeCommentDecoration (bool bIsStartDeco)
{
	ACommentItemDecoration * cFrontDeco = new ACommentItemDecoration();
	cFrontDeco->SetWidthOfDecoration(m_CommentWidth, bIsStartDeco);
	AddItem(cFrontDeco);
}


void AComment::MakeCommentFile ()
{
	if(!m_CommentFileTxt.IsEmpty())
	{
		ACommentItemFile * cFileComment = new ACommentItemFile();
		cFileComment->WriteText(m_CommentFileTxt);
		AddItem(cFileComment);
	}
}

void AComment::MakeCommentBrief()
{
	if(!m_CommentBriefTxt.IsEmpty())
	{
		ACommentItemBrief * cBriefComment = new ACommentItemBrief();
		cBriefComment->SetTextWidth(m_CommentWidth);
		cBriefComment->WriteText(m_CommentBriefTxt);
		AddItem(cBriefComment);
	}
}

void AComment::MakeCommentDescription()
{
	if(!m_CommentDescriptionTxt.IsEmpty())
	{
		ACommentItemDescription * cDesciption = new ACommentItemDescription();
		cDesciption->SetTextWidth(m_CommentWidth);
		cDesciption->WriteText(m_CommentDescriptionTxt);
		AddItem(cDesciption);
	}

}

void AComment::MakeCommentAuthor()
{
	if(!m_CommentAuthorTxt.IsEmpty())
	{
		ACommentItemAuthor * cAuthor = new ACommentItemAuthor();
		cAuthor->WriteText(m_CommentAuthorTxt);
		AddItem(cAuthor);
	}

}


void AComment::MakeCommentDate()
{
	if (m_Date.IsValid())
	{
		ACommentItemDate * cDate = new ACommentItemDate();
		cDate->WriteDate(m_Date);
		AddItem(cDate);
	}
}


ACommentFunction::ACommentFunction() : AComment()
{
	m_List.DeleteContents(TRUE);
	ClearArray();
}

ACommentFunction::~ACommentFunction()
{
	ClearArray();
}

int ACommentFunction::MakeComment()
{
	MakeCommentDecoration(TRUE);
	MakeCommentFile();
	MakeCommentBrief();
	MakeCommentDescription();
	MakeCommentFunction();
	MakeCommentAuthor();
	MakeCommentDate();
	MakeCommentDecoration(FALSE);
	return GetItemCount();
}

void ACommentFunction::MakeCommentFunction()
{
	ACommentItemFunction * cFunction;
	
	if (myCommentArray.GetCount() > 0)
	{
		
		for (int i=0; i< myCommentArray.GetCount(); i++)
		{
			cFunction = new ACommentItemFunction();
			cFunction->SetTextWidth(m_CommentWidth);
			cFunction->WriteFunctionTag(myVarArray.Item(i),(ACOMMENTPOSITION) myTypeArray.Item(i));
			cFunction->WriteText(myCommentArray.Item(i));
			AddItem(cFunction); 
		}
		
		// clear the array
		ClearArray();
	}
}

void ACommentFunction::ClearArray()
{
	myVarArray.Clear();
	myCommentArray.Clear();
	myTypeArray.Clear();
}

void ACommentFunction::SetCommentFunctionList(wxString myVar, wxString myComment, ACOMMENTPOSITION itemType)
{
	myVarArray.Add(myVar);
	myCommentArray.Add(myComment);
	myTypeArray.Add(itemType);
}
