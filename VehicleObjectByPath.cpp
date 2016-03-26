#include "StdAfx.h"
#include "VehicleObjectByPath.h"

CVehicleObjectByPath::CVehicleObjectByPath(bool bRefPath)
{
	m_nId = -1;
	m_nPartId = 0;
	m_dbVelocity = -1;
	m_bInvert = false;
	dbHeading = 0.0;
	m_pPath = NULL;
	m_bRepeat = false;
	m_bReverse = false;
	m_bRefPath = bRefPath;
	m_nCount = 0;
}

CVehicleObjectByPath::~CVehicleObjectByPath()
{
	if (m_bRefPath == false)
	{
		if (m_pPath != NULL)
		{
			delete m_pPath;
			m_pPath = NULL;
		}
	}
}
