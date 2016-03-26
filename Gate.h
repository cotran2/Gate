#pragma once

#include "SimpleSegment.h"

class CGate
{
public:
	CGate();
	CGate(double dbDist, double dbGateHeight, CSimpleSegment &s);
	virtual ~CGate();

private:
public:
	int m_nId;
	int m_nCount;
	double m_dbGateRatioOrgDist, m_dbGateRatio, m_dbSegLength;
	CSimpleSegment m_seg, m_segOrthor;

public:
	void SetGateInfo(double dbDist, double dbGateHeight, CSimpleSegment &s);
};
