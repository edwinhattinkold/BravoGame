#pragma once
class Turret;
class MovingTurret;
class TurretState{
private:
	
protected:
	Turret* turret;
	float calculateDistance();
public:
	TurretState(Turret* turret);
	~TurretState();
	virtual void checkState();
	virtual void update(float deltaTime);
};