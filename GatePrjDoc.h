
// GatePrjDoc.h : interface of the CGatePrjDoc class
//


#pragma once

#include "SimplePoint.h"
#include "Gate.h"
#include "Monitor.h"

#include "VehicleObjectByPath.h"
#include "VehicleRunner.h"
#include "SlimRWLock.h"

class CGatePrjDoc : public CDocument
{
protected: // create from serialization only
	CGatePrjDoc();
	DECLARE_DYNCREATE(CGatePrjDoc)

// Attributes
public:
	bool m_bIsInited;
	bool m_bRedraw;

	//  GDIPlus
	ULONG_PTR m_gdiplusToken;

	//  Path
	CArray<CSimplePoint> *m_parrPts;

	//  Gates
	CArray<CGate*> *m_parrGates;

	//  Vehicles
	CArray<CVehicleObjectByPath*> *m_parrVehicles;
	CVehicleRunner *m_pVehicleRunner;
	//---Lock -----//
	SlimRWLock m_lckMovingObject;

	bool m_bOnThread;
	CEvent m_ThreadStart;
	CEvent m_ThreadEnd;
	CWinThread *m_pRunThread;
	DWORD m_nPrevTime;
	DWORD m_nCurrTime;
	CCriticalSection m_CrSection;
	int m_nRefreshTime;

	//  Monitor
	CMonitor *m_pMonitor;

private:
	bool InitPath();
	bool InitGates();
	bool InitVehicles();

// Operations
public:
	void Draw(CDC *pDC);
	void DrawPath(CDC *pDC);
	void DrawGates(CDC *pDC);
	void DrawGateAmount(CDC *pDC);
	void DrawVehicles(CDC *pDC);

public:
	bool DoExecuteRun(bool bStart);
	bool DoRunVehicleOjects(UINT nTimeInterval);
	bool UpdateVehicleStatus(CVehicleObjectByPath *pVO, double dbRadius);

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


