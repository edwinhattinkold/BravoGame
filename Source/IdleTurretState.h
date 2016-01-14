#pragma once
#include "TurretState.h"

class IdleTurretState:public TurretState{
public:
	IdleTurretState(Turret* turret);
	~IdleTurretState();
	void checkState();
	void update(float deltaTime);
};