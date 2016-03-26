
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
	CGatePrjDoc* GetDocument() const;

// Operations
public:

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
};

#ifndef _DEBUG  // debug version in GatePrjView.cpp
inline CGatePrjDoc* CGatePrjView::GetDocument() const
   { return reinterpret_cast<CGatePrjDoc*>(m_pDocument); }
#endif

