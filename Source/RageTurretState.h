#include "ChasingTurretState.h"
#include "MovingTurret.h"
class RageTurretState : public ChasingTurretState{
public:
	RageTurretState(MovingTurret* turret);
	~RageTurretState();
	void update(float deltaTime);
	void checkState();
};