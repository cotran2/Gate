#include "StdAfx.h"
#include "VehicleRunner.h"

#include "SimplePoint.h"
#include "SimpleSegment.h"

CVehicleRunner::CVehicleRunner()
{
}

CVehicleRunner::~CVehicleRunner()
{
}

bool CVehicleRunner::NextLBSStep(UINT nTimeInterval, CVehicleObjectByPath *pVO)
{
	if (nTimeInterval <= 0)
		return false;
	if (pVO == NULL)
		return false;

	CSimpleSegment S;

	int i, nPts;
	double dbTotalDist, dbCountDist, dbTmpDist, dbRatio;
	CSimplePoint sV, eV, cV;
	bool bContinue;
	CSimplePoint *pPts;
	CSimplePoint rP;

	pVO->m_PPt.x = pVO->m_CPt.x;
	pVO->m_PPt.y = pVO->m_CPt.y;
	cV.x = pVO->m_CPt.x;
	cV.y = pVO->m_CPt.y;
	dbCountDist = 0;
	bContinue = false;
	nPts = pVO->m_pPath->GetSize();
	pPts = pVO->m_pPath->GetData();
	dbTotalDist = ((pVO->m_dbVelocity*1000)/3600) * (nTimeInterval / 1000.0);
	if (pVO->m_bInvert == false) // on direction
	{
		i = pVO->m_nPartId + 1;
		sV.x = pVO->m_CPt.x;
		sV.y = pVO->m_CPt.y;
		eV.x = pPts[i].x;
		eV.y = pPts[i].y;
		dbTmpDist = Distance(sV, eV);
		dbCountDist	+=	dbTmpDist;
		if (dbTotalDist < dbCountDist)
		{
			dbRatio = dbTotalDist / dbCountDist;
			cV.x = sV.x+(eV.x-sV.x) * dbRatio;
			cV.y = sV.y+(eV.y-sV.y) * dbRatio;
			bContinue = true;
		}
		else
		{
			while (i < nPts - 1)
			{
				sV.x = pPts[i].x;
				sV.y = pPts[i].y;
				eV.x = pPts[i+1].x;
				eV.y = pPts[i+1].y;
				dbTmpDist = Distance(sV, eV);
				if (dbTotalDist < dbCountDist + dbTmpDist)
				{
					dbTotalDist = dbTotalDist - dbCountDist;
					dbCountDist = dbTmpDist;
					dbRatio	= dbTotalDist/dbCountDist;
					cV.x = sV.x+(eV.x-sV.x)*dbRatio;
					cV.y = sV.y+(eV.y-sV.y)*dbRatio;
					bContinue = true;
					pVO->m_nPartId = i;
					break;
				}
				dbCountDist += dbTmpDist;
				pVO->m_nPartId++;
				i++;
			}
		}
		pVO->m_CPt.x = cV.x;
		pVO->m_CPt.y = cV.y;
		S.p1 = pPts[pVO->m_nPartId];
		S.p2 = pPts[pVO->m_nPartId+1];
		pVO->dbHeading = S.Heading()*180/PI;
	}
	else // invert direction
	{
		i = pVO->m_nPartId;
		sV.x = pVO->m_CPt.x;
		sV.y = pVO->m_CPt.y;
		eV.x = pPts[i].x;
		eV.y = pPts[i].y;
		dbTmpDist = Distance(sV, eV);
		dbCountDist += dbTmpDist;
		if (dbTotalDist < dbCountDist)
		{
			dbRatio = dbTotalDist/dbCountDist;
			cV.x = sV.x+(eV.x-sV.x)*dbRatio;
			cV.y = sV.y+(eV.y-sV.y)*dbRatio;
			bContinue = true;
		}
		else
		{
			while (i > 0)
			{
				sV.x = pPts[i].x;
				sV.y = pPts[i].y;
				eV.x = pPts[i-1].x;
				eV.y = pPts[i-1].y;
				dbTmpDist = Distance(sV, eV);
				if (dbTotalDist < dbCountDist + dbTmpDist)
				{
					dbTotalDist = dbTotalDist - dbCountDist;
					dbCountDist = dbTmpDist;
					dbRatio = dbTotalDist/dbCountDist;
					cV.x = sV.x+(eV.x-sV.x)*dbRatio;
					cV.y = sV.y+(eV.y-sV.y)*dbRatio;
					bContinue	=	true;
					//					pMO->nPartId--;
					pVO->m_nPartId = i - 1;
					break;
				}
				dbCountDist += dbTmpDist;
				pVO->m_nPartId--;
				i--;
			}
		}
		pVO->m_CPt.x = cV.x;
		pVO->m_CPt.y = cV.y;
		S.p1 = pPts[pVO->m_nPartId+1];
		S.p2 = pPts[pVO->m_nPartId];
		pVO->dbHeading = S.Heading()*180/PI;
	}

	if (bContinue == false)
	{
		if (pVO->m_bReverse == true)
			pVO->m_bInvert = !pVO->m_bInvert;
		else
		{
			if (pVO->m_bRepeat == true)
			{
				if (pVO->m_bInvert == false)
				{
					pVO->m_nPartId = 0;
					rP = pVO->m_pPath->GetAt(0);
				}
				else
				{
					pVO->m_nPartId = pVO->m_pPath->GetSize() - 1;
					rP = pVO->m_pPath->GetAt(pVO->m_pPath->GetUpperBound());
				}
				pVO->m_PPt.x = rP.x;
				pVO->m_PPt.y = rP.y;
				pVO->m_CPt.x = rP.x;
				pVO->m_CPt.y = rP.y;
			}
		}
	}

	return bContinue;
}
