#include "StdAfx.h"
#include "Gate.h"

CGate::CGate()
{
	m_nId = -1;
	m_dbGateRatio = -1;
	m_dbSegLength = 0.0;
	m_dbGateRatioOrgDist = 0.0;
	m_nCount = 0;
}

CGate::CGate(double dbDist, double dbGateHeight, CSimpleSegment &s)
{
	CSimpleSegment segL, segR;

	m_nId = -1;
	m_nCount = 0;
	m_seg = s;
	m_dbSegLength = Distance(m_seg.p1, m_seg.p2);
	m_dbGateRatio = dbDist / m_dbSegLength;
	m_dbGateRatioOrgDist = dbDist;

	m_seg.ParallelSegments(dbGateHeight, segL, segR);
	m_segOrthor.p1 = segL.GetPointAt(dbDist);
	m_segOrthor.p2 = segR.GetPointAt(dbDist);
}

CGate::~CGate()
{
}

void CGate::SetGateInfo(double dbDist, double dbGateHeight, CSimpleSegment &s)
{
	CSimpleSegment segL, segR;

	m_seg = s;
	m_dbSegLength = Distance(m_seg.p1, m_seg.p2);
	m_dbGateRatio = dbDist / m_dbSegLength;
	m_dbGateRatioOrgDist = dbDist;

	m_seg.ParallelSegments(dbGateHeight, segL, segR);
	m_segOrthor.p1 = segL.GetPointAt(dbDist);
	m_segOrthor.p2 = segR.GetPointAt(dbDist);
}

