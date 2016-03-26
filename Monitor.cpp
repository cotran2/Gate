#include "StdAfx.h"
#include "Monitor.h"

CMonitor::CMonitor()
{
	m_pVehicle2Gate = new CMap<int, int&, int, int&>;
	m_pGate2Vehicles = new CMap<int, int&, CMap<int, int&, VehicleStatus, VehicleStatus&>*, CMap<int, int&, VehicleStatus, VehicleStatus&>*>;
}

CMonitor::~CMonitor()
{
	if (m_pVehicle2Gate != NULL)
	{
		delete m_pVehicle2Gate;
		m_pVehicle2Gate = NULL;
	}

	if (m_pGate2Vehicles != NULL)
	{
		POSITION pos;
		CMap<int, int&, VehicleStatus, VehicleStatus&> *pmapStatus;
		int nKey;

		pos = m_pGate2Vehicles->GetStartPosition();
		while (pos)
		{
			m_pGate2Vehicles->GetNextAssoc(pos, nKey, pmapStatus);
			if (pmapStatus != NULL)
			{
				delete pmapStatus;
				pmapStatus = NULL;
			}
		}
		delete m_pGate2Vehicles;
		m_pGate2Vehicles = NULL;
	}
}
