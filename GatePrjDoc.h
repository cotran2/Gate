
// GatePrjDoc.h : interface of the CGatePrjDoc class
//


#pragma once


class CGatePrjDoc : public CDocument
{
protected: // create from serialization only
	CGatePrjDoc();
	DECLARE_DYNCREATE(CGatePrjDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CGatePrjDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


