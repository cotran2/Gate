
// GatePrjDoc.cpp : implementation of the CGatePrjDoc class
//

#include "stdafx.h"
#include "GatePrj.h"

#include "GatePrjDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGatePrjDoc

IMPLEMENT_DYNCREATE(CGatePrjDoc, CDocument)

BEGIN_MESSAGE_MAP(CGatePrjDoc, CDocument)
END_MESSAGE_MAP()


// CGatePrjDoc construction/destruction

CGatePrjDoc::CGatePrjDoc()
{
	// TODO: add one-time construction code here

}

CGatePrjDoc::~CGatePrjDoc()
{
}

BOOL CGatePrjDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CGatePrjDoc serialization

void CGatePrjDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CGatePrjDoc diagnostics

#ifdef _DEBUG
void CGatePrjDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGatePrjDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGatePrjDoc commands
