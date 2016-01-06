#pragma once
#include "TurretState.h"
class ChasingTurretState :public TurretState{
public:
	ChasingTurretState(MovingTurret* turret);
	~ChasingTurretState();
	void checkState();
	void update(float deltaTime);
};