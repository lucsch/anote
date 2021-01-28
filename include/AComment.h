 /*******************************************************//**
@file AComment.h
@brief Class for building comments (header)
@details This file contains all headers required for dealing 
with the comments.
@author Lucien Schreiber (c) CREALP 2007
@date 15 November 2007
 ***********************************************************/

#ifndef ACOMMENT_H
#define ACOMMENT_H


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// Include wxWidgets' headers
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


enum ACOMMENTPOSITION 
{
	COMMENT_DECO_TOP = 1,
	COMMENT_FILE,
	COMMENT_BRIEF,
	COMMENT_DESCRIPTION,
	COMMENT_AUTHOR,
	COMMENT_DATE,
	COMMENT_DECO_BOTTOM,
	COMMENT_PARAM,
	COMMENT_RETURN
};


 class ACommentItem 
 {
	private:	
	  wxString m_Tag;
	  wxString m_Text;
	  
	protected :  
	  wxString SplitText(wxString szText,int iTextWidth);
	  bool SearchForSpaceToCut (wxString & myStringToCut, int & iCutedWidth, int iStop, int iLen);
    
	public:
	  ACommentItem();
	  ~ACommentItem();
	
      wxString GetValue() {return m_Text;}  
	  wxString GetTag()	{ return m_Tag;}
	  
	  void SetValue(wxString myText); 
	  void SetTag(wxString myTag);
	  
	  virtual void WriteTag(wxString myTagText)  = 0;// = 0 signifie "virtuelle pure"
	  virtual void WriteText(wxString myTextText)  = 0;
	  wxString WriteItem();
   
};


class ACommentItemAuthor : public ACommentItem
{
	private:
		void WriteTag(wxString myTagText);

	
	public:
		ACommentItemAuthor();
		~ACommentItemAuthor();
		
		void WriteText(wxString myAuthor);

};

class ACommentItemBrief : public ACommentItem
{
	private:
		int m_TextWidth;
	
	public:
		ACommentItemBrief();
		~ACommentItemBrief();
		
		void SetTextWidth(int myTextWidth);
		void WriteText(wxString myBrief);
		void WriteTag(wxString myTagText);
};


class ACommentItemDescription : public ACommentItem
{
	private:
		int m_TextWidth;
	
	public:
		ACommentItemDescription();
		~ACommentItemDescription();
		
		void SetTextWidth(int myTextWidth);
		void WriteText(wxString myDescription);
		void WriteTag(wxString myTagText);
};

class ACommentItemDate : public ACommentItem
{
	private:
		void WriteTag(wxString myTagText);

	
	public:
		ACommentItemDate();
		~ACommentItemDate();
		
		void WriteText(wxString myDate);
		void WriteDate(wxDateTime &myDate);

};

class ACommentItemFile : public ACommentItem
{
	private:
		void WriteTag(wxString myTagText);

	
	public:
		ACommentItemFile();
		~ACommentItemFile();
		
		void WriteText(wxString myFile);

};

class ACommentItemDecoration : public ACommentItem
{
	private:
		int m_WithOfDecoration;
		
		void WriteTag(wxString myTagText);
		void WriteText(wxString myDecoration);
	
	public:
		ACommentItemDecoration();
		~ACommentItemDecoration();
		
		void SetWidthOfDecoration(int myWidth=50, bool bBegin=TRUE);
		
};

class ACommentItemFunction : public ACommentItem
{
	private:
		void WriteTag(wxString myTagFunction);
		int m_TextWidth;
	
	public:
		ACommentItemFunction();
		~ACommentItemFunction();
		
		void WriteFunctionTag(wxString myVal, ACOMMENTPOSITION itemType=COMMENT_PARAM);
		void WriteText(wxString myFunctionComment);
		void SetTextWidth (int myWidth);
};


class ACommentClassItem
{
	public:
		ACommentItem * m_CommentItem;
};

WX_DECLARE_LIST(ACommentClassItem, ACommentClassItemList);



class AComment
{
	protected:
		ACommentClassItemList m_List;
		int m_CommentWidth;
		
		wxString m_CommentFileTxt;
		wxString m_CommentBriefTxt;
		wxString m_CommentDescriptionTxt;
		wxString m_CommentAuthorTxt;
		wxDateTime m_Date;
		
		
		 void MakeCommentDecoration (bool bIsStartDeco=TRUE);
		 void MakeCommentFile ();
		 void MakeCommentBrief();
		 void MakeCommentDescription();
		 void MakeCommentAuthor();
		 void MakeCommentDate();
		 
		 virtual int MakeComment();
	public:
		AComment();
		~AComment();
		
		void AddItem(ACommentItem * myItem);
		ACommentItem* GetItem(int iIndex=0);
		bool GetItemByTag(wxString szTag, ACommentItem * myReturnedItem);
		int GetItemCount ();
		void SetCommentWidth (int iCommentWidth);
		wxString Write ();
		void SetCommentText (ACOMMENTPOSITION itemPosition, wxString myText);
		void SetCommentDate (wxDateTime &myDate);
		int ClearList();
};


class ACommentFunction : public AComment
{
	private:
		wxArrayString myVarArray;
		wxArrayString myCommentArray;
		wxArrayInt myTypeArray;
	
		void MakeCommentFunction();
		void ClearArray();
	
		virtual int MakeComment();
	public:
		ACommentFunction();
		~ACommentFunction();
		void SetCommentFunctionList(wxString myVar, wxString myComment, ACOMMENTPOSITION itemType=COMMENT_PARAM);
};




#endif
