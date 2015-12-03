#pragma once
#include "TurretState.h"

class SearchingTurretState:public TurretState{
public:
	SearchingTurretState(Turret* turret);
	~SearchingTurretState();
	void checkState();
	void update(float deltaTime);
};