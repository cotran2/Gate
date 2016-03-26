#pragma once

#include "SimplePoint.h"

class CVehicleObjectByPath
{
public:
	CVehicleObjectByPath(bool bRefPath);
	virtual ~CVehicleObjectByPath();

public:
	int m_nId;
	int m_nPartId;
	CSimplePoint m_PPt;
	CSimplePoint m_CPt;
	double m_dbVelocity;  //  Km/h
	bool m_bInvert;
	double dbHeading;
	CString strText;  //  Temp to display signpost
	CArray<CSimplePoint> *m_pPath;
	bool m_bRepeat;
	bool m_bReverse;

	int m_nCount;
private:
	bool m_bRefPath;
};
