
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
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_SIMULATE_RUN, &CGatePrjView::OnSimulateRunStop)
	ON_UPDATE_COMMAND_UI(ID_SIMULATE_RUN, &CGatePrjView::OnUpdateSimulateRunStop)
END_MESSAGE_MAP()

// CGatePrjView construction/destruction

CGatePrjView::CGatePrjView()
{
	m_nRunTimer = -1;
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

void CGatePrjView::OnDraw(CDC *pDC)
{
	CGatePrjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if(pDoc->m_bIsInited)
	{
		CRect rectUpdate;

		GetClientRect(&rectUpdate);
		pDC->FillSolidRect(rectUpdate, RGB(255, 255, 255));
		pDoc->Draw(pDC);
	}
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

void CGatePrjView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CGatePrjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect  rcCl;
	CSize sz;
	bool bRet;

	bRet = false;
	GetClientRect(&rcCl);
	sz.cx = rcCl.Width();
	sz.cy = rcCl.Height();

	m_rcClientRect = rcCl;
}

void CGatePrjView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(1000,1000);
	pDC->SetViewportExt(1000,1000);

	CView::OnPrepareDC(pDC, pInfo);
}

void CGatePrjView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if((cx==0)||(cy==0))
		return;

	CGatePrjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSize sz;

	if(!pDoc->m_bIsInited)
		return;

	GetClientRect(&m_rcClientRect);

	sz.cx = m_rcClientRect.Width();
	sz.cy = m_rcClientRect.Height();

	InvalidateRect(NULL, FALSE);	
}

void CGatePrjView::OnDestroy()
{
	CView::OnDestroy();

	if (m_nRunTimer != -1)
		KillTimer(m_nRunTimer);
}

void CGatePrjView::OnTimer(UINT_PTR nIDEvent)
{
	CGatePrjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch (nIDEvent)
	{
	case VEHICLE_OBJECT_TIMER:
		{
			if (pDoc->m_bOnThread == true)
				Invalidate(FALSE);
		}
		break;
	}

	CView::OnTimer(nIDEvent);
}

void CGatePrjView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGatePrjView::OnSimulateRunStop()
{
	CGatePrjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->m_bOnThread == false)  //  Start
	{
		if (m_nRunTimer != -1)
		{
			KillTimer(m_nRunTimer);
			m_nRunTimer = -1;
		}
		m_nRunTimer = SetTimer(VEHICLE_OBJECT_TIMER, pDoc->m_nRefreshTime, NULL);
		pDoc->DoExecuteRun(true);
	}
	else  //  Stop
	{
		if (m_nRunTimer != -1)
		{
			KillTimer(m_nRunTimer);
			m_nRunTimer = -1;
		}
		pDoc->DoExecuteRun(false);
	}
}

void CGatePrjView::OnUpdateSimulateRunStop(CCmdUI *pCmdUI)
{
	CGatePrjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(pDoc->m_bIsInited);
	pCmdUI->SetCheck(pDoc->m_bOnThread);
}
