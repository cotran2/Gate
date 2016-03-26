#pragma once

#include "Gate.h"
#include "VehicleObjectByPath.h"

struct VehicleStatus
{
	int nVehicleId;
	bool bLeft;
};

class CMonitor
{
public:
	CMonitor();
	virtual ~CMonitor();

public:
	CMap<int, int&, int, int&> *m_pVehicle2Gate;
	CMap<int, int&, CMap<int, int&, VehicleStatus, VehicleStatus&>*, CMap<int, int&, VehicleStatus, VehicleStatus&>*> *m_pGate2Vehicles;
};
