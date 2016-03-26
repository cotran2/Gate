
// GatePrjView.cpp : implementation of the CGatePrjView class
//

#include "stdafx.h"
#include "GatePrj.h"

#include "GatePrjDoc.h"
#include "GatePrjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGatePrjView

IMPLEMENT_DYNCREATE(CGatePrjView, CView)

BEGIN_MESSAGE_MAP(CGatePrjView, CView)
END_MESSAGE_MAP()

// CGatePrjView construction/destruction

CGatePrjView::CGatePrjView()
{
	// TODO: add construction code here

}

CGatePrjView::~CGatePrjView()
{
}

BOOL CGatePrjView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGatePrjView drawing

void CGatePrjView::OnDraw(CDC* /*pDC*/)
{
	CGatePrjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CGatePrjView diagnostics

#ifdef _DEBUG
void CGatePrjView::AssertValid() const
{
	CView::AssertValid();
}

void CGatePrjView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGatePrjDoc* CGatePrjView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGatePrjDoc)));
	return (CGatePrjDoc*)m_pDocument;
}
#endif //_DEBUG


// CGatePrjView message handlers
