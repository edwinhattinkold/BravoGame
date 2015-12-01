#pragma once
#include "TurretState.h"

class ShootingTurretState :public TurretState{
public:
	ShootingTurretState(Turret* turret);
	~ShootingTurretState();
	void checkState();
	void update(float deltaTime);
};