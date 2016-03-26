#pragma once

#include "VehicleObjectByPath.h"

class CVehicleRunner
{
public:
	CVehicleRunner();
	virtual ~CVehicleRunner();

public:
	bool NextLBSStep(UINT nTimeInterval, CVehicleObjectByPath *pVO);
	void SetTransportType(int nTransportType);
};
