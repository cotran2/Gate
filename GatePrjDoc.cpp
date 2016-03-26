
// GatePrjDoc.cpp : implementation of the CGatePrjDoc class
//

#include "stdafx.h"
#include "GatePrj.h"

#include "GatePrjDoc.h"

#include "Random.h"
#include <float.h>

// CGatePrjDoc

IMPLEMENT_DYNCREATE(CGatePrjDoc, CDocument)

BEGIN_MESSAGE_MAP(CGatePrjDoc, CDocument)
END_MESSAGE_MAP()


// CGatePrjDoc construction/destruction

UINT VehicleObjectsThread(LPVOID lpParam)
{
	CGatePrjDoc* pGPDoc = (CGatePrjDoc*)lpParam;
	if (pGPDoc == NULL)
		return 0;

	int nTimeInterval;

	BOOL keepRunning = TRUE;
	::WaitForSingleObject(pGPDoc->m_ThreadStart.m_hObject, INFINITE);
	while (keepRunning)
	{
		pGPDoc->m_nCurrTime = ::GetTickCount();
		nTimeInterval = pGPDoc->m_nCurrTime - pGPDoc->m_nPrevTime;
		pGPDoc->DoRunVehicleOjects(nTimeInterval);
		pGPDoc->m_nPrevTime = pGPDoc->m_nCurrTime;
		int result = ::WaitForSingleObject(pGPDoc->m_ThreadEnd.m_hObject, 0);
		if (result == WAIT_OBJECT_0)
			keepRunning = FALSE;
	}

	return 0;
}

CGatePrjDoc::CGatePrjDoc()
{
	m_parrPts = NULL;
	m_parrGates = NULL;
	m_bIsInited = false;
	m_bRedraw = false;
	m_parrVehicles = NULL;
	m_pVehicleRunner = NULL;;
	m_bOnThread = false;
	m_pRunThread = NULL;
	m_pMonitor = NULL;
	m_nRefreshTime = 500;

	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &input, NULL);
}

CGatePrjDoc::~CGatePrjDoc()
{
	if (m_parrPts != NULL)
	{
		delete m_parrPts;
		m_parrPts = NULL;
	}

	if (m_parrGates != NULL)
	{
		int i, nGates;
		CGate *pGate;

		nGates = m_parrGates->GetSize();
		for (i = 0; i < nGates; i++)
		{
			pGate = m_parrGates->GetAt(i);
			if (pGate != NULL)
			{
				delete pGate;
				pGate = NULL;
			}
		}
		delete m_parrGates;
		m_parrGates = NULL;
	}

	m_bOnThread = false;
	if (m_pRunThread != NULL)
	{
	}

	if (m_parrVehicles != NULL)
	{
		int i, nVehicles;
		CVehicleObjectByPath *pVO;

		nVehicles = m_parrVehicles->GetSize();
		for (i = 0; i < nVehicles; i++)
		{
			pVO = m_parrVehicles->GetAt(i);
			if (pVO != NULL)
			{
				delete pVO;
				pVO = NULL;
			}
		}
		delete m_parrVehicles;
		m_parrVehicles = NULL;
	}

	if (m_pVehicleRunner != NULL)
	{
		delete m_pVehicleRunner;
		m_pVehicleRunner = NULL;
	}

	if (m_pMonitor != NULL)
	{
		delete m_pMonitor;
		m_pMonitor = NULL;
	}

	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}

BOOL CGatePrjDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	InitPath();
	InitGates();
	InitVehicles();

	m_pMonitor = new CMonitor;
	m_bIsInited = true;
	m_bRedraw = true;
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
bool CGatePrjDoc::InitPath()
{
	CSimplePoint rP;

	m_parrPts = new CArray<CSimplePoint>;
	rP.x = 100;
	rP.y = 100;
	m_parrPts->Add(rP);

	rP.x = 1000;
	rP.y = 100;
	m_parrPts->Add(rP);

	rP.x = 1000;
	rP.y = 500;
	m_parrPts->Add(rP);

	rP.x = 100;
	rP.y = 500;
	m_parrPts->Add(rP);

	rP.x = 100;
	rP.y = 100;
	m_parrPts->Add(rP);

	return true;
}

bool CGatePrjDoc::InitGates()
{
	if (m_parrGates != NULL)
	{
		int i, nGates;
		CGate *pGate;

		nGates = m_parrGates->GetSize();
		for (i = 0; i < nGates; i++)
		{
			pGate = m_parrGates->GetAt(i);
			if (pGate != NULL)
			{
				delete pGate;
				pGate = NULL;
			}
		}
		delete m_parrGates;
		m_parrGates = NULL;
	}

	int i, nGates;
	CGate *pGate;
	CSimpleSegment s;
	CSimplePoint *pPts;
	double dbLength, dbDist;

	m_parrGates = new CArray<CGate*>;

	nGates = m_parrPts->GetSize() - 1;
	pPts = m_parrPts->GetData();
	for (i = 0; i < nGates; i++)
	{
		s.p1 = pPts[i];
		s.p2 = pPts[i+1];
		dbLength = Distance(s.p1, s.p2);
		dbDist = dbLength / 2;
		pGate = new CGate(dbDist, 40, s);
		pGate->m_nId = m_parrGates->GetSize();
		m_parrGates->Add(pGate);
	}

	return true;
}

bool CGatePrjDoc::InitVehicles()
{
	if (m_parrVehicles != NULL)
	{
		int i, nVehicles;
		CVehicleObjectByPath *pVO;

		nVehicles = m_parrVehicles->GetSize();
		for (i = 0; i < nVehicles; i++)
		{
			pVO = m_parrVehicles->GetAt(i);
			if (pVO != NULL)
			{
				delete pVO;
				pVO = NULL;
			}
		}
		delete m_parrVehicles;
		m_parrVehicles = NULL;
	}

	int i, nIndex, nParts, nVehicles;
	CVehicleObjectByPath *pVO;
	double dbDist, dbLength;
	CSimpleSegment seg;
	CSimplePoint *pPts, rP;
	static Random r;
	int nVelocity;

	nVehicles = 2;
	nVelocity = 120;
	pPts = m_parrPts->GetData();
	m_parrVehicles = new CArray<CVehicleObjectByPath*>;
	nParts = m_parrPts->GetSize() - 1;
	for (i = 0; i < nVehicles; i++)
	{
		nIndex = i % nParts;
		seg.p1 = pPts[nIndex];
		seg.p2 = pPts[nIndex+1];
		dbLength = Distance(seg.p1, seg.p2);
		dbDist = r.random0_1() * dbLength;

		rP = seg.GetPointAt(dbDist);
		pVO = new CVehicleObjectByPath(true);
		pVO->m_bInvert = false;
		pVO->m_bRepeat = true;
		pVO->m_nId = m_parrVehicles->GetSize();
		pVO->m_nPartId = nIndex;
		pVO->m_PPt = rP;
		pVO->m_CPt = rP;
		pVO->m_dbVelocity = nVelocity;
		pVO->m_pPath = m_parrPts;

		nIndex = m_parrVehicles->Add(pVO);
	}

	return true;
}

void CGatePrjDoc::Draw(CDC *pDC)
{
	DrawPath(pDC);
	DrawGates(pDC);
	DrawVehicles(pDC);
	DrawGateAmount(pDC);
}

void CGatePrjDoc::DrawPath(CDC *pDC)
{
	int i, nPts;
	CSimplePoint *pPts;
	Gdiplus::Graphics *pGraphics;
	Gdiplus::Point *pGdiPts;

	pGraphics = new Gdiplus::Graphics(pDC->GetSafeHdc());
	if (m_parrPts != NULL)
	{
		nPts = m_parrPts->GetSize();
		pPts = m_parrPts->GetData();

		pGdiPts = new Gdiplus::Point[nPts];
		for (i = 0; i < nPts; i++)
		{
			pGdiPts[i].X = (INT)pPts[i].x;
			pGdiPts[i].Y = (INT)pPts[i].y;
		}
		Gdiplus::GraphicsPath path;
		Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 192), 5);

		path.AddLines(pGdiPts, nPts);
		pGraphics->DrawPath(&pen, &path);
		delete []pGdiPts;
		pGdiPts = NULL;
	}

	delete pGraphics;
	pGraphics = NULL;
}

void CGatePrjDoc::DrawGates(CDC *pDC)
{
	if (m_parrGates == NULL)
		return;

	int i, nGates;
	CGate *pGate;
	Gdiplus::Graphics *pGraphics;
	Gdiplus::Point p1, p2;
	Gdiplus::Pen pen(Gdiplus::Color(255, 192, 0, 0), 4);

	pGraphics = new Gdiplus::Graphics(pDC->GetSafeHdc());
	nGates = m_parrGates->GetSize();
	for (i = 0; i < nGates; i++)
	{
		pGate = m_parrGates->GetAt(i);
	
		p1.X = (INT)pGate->m_segOrthor.p1.x;
		p1.Y = (INT)pGate->m_segOrthor.p1.y;
		p2.X = (INT)pGate->m_segOrthor.p2.x;
		p2.Y = (INT)pGate->m_segOrthor.p2.y;
		pGraphics->DrawLine(&pen, p1, p2);
	}

	delete pGraphics;
	pGraphics = NULL;
}

void CGatePrjDoc::DrawGateAmount(CDC *pDC)
{
	if (m_parrGates == NULL)
		return;

	int i, nGates, nTextMode, nTextAlign;
	CGate *pGate;
	CPen *pOldPen;
	CString strText;

	m_lckMovingObject.LockReader();

	pOldPen = pDC->GetCurrentPen();
	nTextMode = pDC->SetBkMode(TRANSPARENT);
	nTextAlign = pDC->SetTextAlign(TA_CENTER | TA_BASELINE);

	nGates = m_parrGates->GetSize();
	for (i = 0; i < nGates; i++)
	{
		pGate = m_parrGates->GetAt(i);

		strText.Format(_T("%d___%d"), pGate->m_nId, pGate->m_nCount);
		pDC->TextOut(pGate->m_segOrthor.p2.x + 10, pGate->m_segOrthor.p2.y + 10, strText);
	}

	pDC->SelectObject(pOldPen);
	pDC->SetBkMode(nTextMode);
	pDC->SetTextAlign(nTextAlign);

	m_lckMovingObject.UnlockReader();
}

bool CGatePrjDoc::DoExecuteRun(bool bStart)
{
	if (bStart == false)
	{
		m_ThreadEnd.SetEvent();
		m_bOnThread = false;
	}
	else
	{
		m_pRunThread = AfxBeginThread(VehicleObjectsThread, this);
		m_pRunThread->m_bAutoDelete = false;
		m_nPrevTime = ::GetTickCount();
		m_ThreadStart.SetEvent();
		m_bOnThread = true;
	}
	return true;
}

bool CGatePrjDoc::DoRunVehicleOjects(UINT nTimeInterval)
{
	m_lckMovingObject.LockWriter();

	if (m_parrVehicles != NULL && nTimeInterval > 0)
	{
		int i, nObjs;
		CVehicleObjectByPath **paVOs;
		double dbRadius;

		dbRadius = FLT_EPSILON;
		nObjs = m_parrVehicles->GetSize();
		paVOs = m_parrVehicles->GetData();
		for (i = 0; i < nObjs; i++)
		{
			m_pVehicleRunner->NextLBSStep(nTimeInterval, paVOs[i]);
			UpdateVehicleStatus(paVOs[i], dbRadius);
		}
	}

	m_lckMovingObject.UnlockWriter();
	return true;
}

void CGatePrjDoc::DrawVehicles(CDC *pDC)
{
	m_lckMovingObject.LockReader();

	int i, nVehicles, nRadius, nTextMode, nTextAlign;
	CPen penV, penS, penR, *pOldPen;
	CString strText;
	CPoint vP;

	nRadius = 3;

	pOldPen = pDC->GetCurrentPen();
	nTextMode = pDC->SetBkMode(TRANSPARENT);
	nTextAlign = pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
	if (m_parrVehicles != NULL)
	{
		CVehicleObjectByPath **paVOs;

		penV.CreatePen(PS_SOLID, 3, RGB(0, 192, 0));
		penS.CreatePen(PS_SOLID, 3, RGB(0, 0, 192));
		penR.CreatePen(PS_SOLID, 3, RGB(192, 0, 0));
		pDC->SelectObject(&penV);
		paVOs = m_parrVehicles->GetData();
		
		nVehicles = m_parrVehicles->GetSize();
		for (i = 0; i < nVehicles; i++)
		{
			vP.x = (int)paVOs[i]->m_CPt.x;
			vP.y = (int)paVOs[i]->m_CPt.y;
			pDC->SelectObject(&penV);
			pDC->Ellipse(vP.x - nRadius, vP.y - nRadius, vP.x + nRadius, vP.y + nRadius);
//					DrawVehicleObjectHeading(pTransform, pDC, pVO);
			strText.Format(_T("%d___%d"), i, paVOs[i]->m_nCount);
			pDC->TextOut(vP.x - 10, vP.y - 10, strText);
		}
		pDC->SelectObject(pOldPen);
	}

	pDC->SelectObject(pOldPen);
	pDC->SetBkMode(nTextMode);
	pDC->SetTextAlign(nTextAlign);

	m_lckMovingObject.UnlockReader();
}

bool CGatePrjDoc::UpdateVehicleStatus(CVehicleObjectByPath *pVO, double dbRadius)
{
	if (m_pMonitor == NULL)
		return false;

	double dbDist, dbMinDist, dbSaveOrgDist;
	int i, nGates, nGateId, nSaveIndex;
	CGate *pGate;
	CSimplePoint rP;
	CMap<int, int&, VehicleStatus, VehicleStatus&> *pmapStatus;
	VehicleStatus status;
	bool bLeft;
	CSimpleSegment seg;

	nSaveIndex = -1;
	dbMinDist = DBL_MAX;
	nGates = m_parrGates->GetSize();
	for (i = 0; i < nGates; i++)
	{
		pGate = m_parrGates->GetAt(i);
		rP.x = pVO->m_CPt.x;
		rP.y = pVO->m_CPt.y;
		seg = pGate->m_seg;
		if (seg.GetCircleClip(rP, dbRadius) == true)
		{
			dbDist = Distance(pVO->m_CPt, rP);
			if (dbDist < dbMinDist)
			{
				dbMinDist = dbDist;
				dbSaveOrgDist = Distance(pGate->m_seg.p1, rP);
				nSaveIndex = i;
			}
		}
	}

	if (nSaveIndex == -1)
		return false;

	if (m_pMonitor->m_pVehicle2Gate->Lookup(pVO->m_nId, nGateId) == false)
	{
		//  Insert
		(*m_pMonitor->m_pVehicle2Gate)[pVO->m_nId] = nGateId;
		if (m_pMonitor->m_pGate2Vehicles->Lookup(nGateId, pmapStatus) == false)
		{
			pmapStatus = new CMap<int, int&, VehicleStatus, VehicleStatus&>;
			(*m_pMonitor->m_pGate2Vehicles)[nGateId] = pmapStatus;
		}

		if (pmapStatus->Lookup(pVO->m_nId, status) == false)
		{
			status.nVehicleId = pVO->m_nId;
			status.bLeft = (dbSaveOrgDist < pGate->m_dbGateRatioOrgDist) ? true : false;
			(*pmapStatus)[pVO->m_nId] = status;
		}
	}
	else
	{
		pGate = m_parrGates->GetAt(nSaveIndex);
		if (pGate->m_nId == nGateId)  //  On 
		{
			if (dbSaveOrgDist < pGate->m_dbGateRatioOrgDist)
				bLeft = true;
			else
				bLeft = false;
			if (m_pMonitor->m_pGate2Vehicles->Lookup(nGateId, pmapStatus) == true)
			{
				if (pmapStatus->Lookup(pVO->m_nId, status) == true)
				{
					if (status.bLeft != bLeft)
					{
						pGate->m_nCount++;
						pVO->m_nCount++;
						status.bLeft = bLeft;
						pmapStatus->SetAt(pVO->m_nId, status);
					}
				}
			}
		}
		else
		{
			m_pMonitor->m_pVehicle2Gate->SetAt(pVO->m_nId, pGate->m_nId);

			//  Delete Old
			if (m_pMonitor->m_pGate2Vehicles->Lookup(nGateId, pmapStatus) == true)
				pmapStatus->RemoveKey(pVO->m_nId);

			//  Update New
			if (m_pMonitor->m_pGate2Vehicles->Lookup(pGate->m_nId, pmapStatus) == false)
			{
				pmapStatus = new CMap<int, int&, VehicleStatus, VehicleStatus&>;
				(*m_pMonitor->m_pGate2Vehicles)[pGate->m_nId] = pmapStatus;
			}

			if (pmapStatus->Lookup(pVO->m_nId, status) == false)
			{
				status.nVehicleId = pVO->m_nId;
				status.bLeft = (dbSaveOrgDist < pGate->m_dbGateRatioOrgDist) ? true : false;
				(*pmapStatus)[pVO->m_nId] = status;
			}
		}
	}

	return true;
}
