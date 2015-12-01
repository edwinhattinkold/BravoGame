#pragma once
#include "TurretState.h"

class DeadTurretState :public TurretState{
public:
	DeadTurretState(Turret* turret);
	~DeadTurretState();
	void checkState();
	void update(float deltaTime);
};