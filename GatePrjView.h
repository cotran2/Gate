
// GatePrjView.h : interface of the CGatePrjView class
//


#pragma once


class CGatePrjView : public CView
{
protected: // create from serialization only
	CGatePrjView();
	DECLARE_DYNCREATE(CGatePrjView)

// Attributes
public:
	CRect m_rcClientRect;

	//  Timer
	int m_nRunTimer;

// Operations
public:
	CGatePrjDoc* GetDocument() const;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CGatePrjView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSimulateRunStop();
	afx_msg void OnUpdateSimulateRunStop(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in GatePrjView.cpp
inline CGatePrjDoc* CGatePrjView::GetDocument() const
   { return reinterpret_cast<CGatePrjDoc*>(m_pDocument); }
#endif

