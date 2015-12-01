#pragma once
#include "TurretState.h"

class DeadTurretState :public TurretState{
private:
	bool exploded;
public:
	DeadTurretState(Turret* turret);
	~DeadTurretState();
	void checkState();
	void update(float deltaTime);
};