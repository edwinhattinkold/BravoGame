#include "RageTurretState.h"
#include "DeadTurretState.h"
RageTurretState::RageTurretState(MovingTurret* turret) :ChasingTurretState(turret){

}

RageTurretState::~RageTurretState(){

}

void RageTurretState::update(float deltaTime){
	ChasingTurretState::update(deltaTime);
	float degPerSec = 200;
	turret->setAsset(Asset_Turret_Angry);
	double newAngle = fmod(450 + RADTODEG * atan2((turret->getCar()->getCenterYSDL() - turret->getCenterYSDL()), (turret->getCar()->getCenterXSDL() - turret->getCenterXSDL())), 360);
	if (deltaTime * degPerSec < abs(newAngle - turret->turretAngle)){
		if (fmod(turret->turretAngle - newAngle + 360, 360) > 180){
			turret->turretAngle += deltaTime * degPerSec;
			if (turret->turretAngle > 360){
				turret->turretAngle = 0;
			}
		}
		else {
			turret->turretAngle -= deltaTime * degPerSec;
			if (turret->turretAngle < 0){
				turret->turretAngle = 360;
			}
		}
	}
	else{
		turret->turretAngle = newAngle;
		turret->getWeapon()->pullTrigger();
	}

	turret->getWeapon()->update(deltaTime);
}

void RageTurretState::checkState(){
	float distance = calculateDistance();
	if (turret->isDead()){
		turret->setState(new DeadTurretState(turret));
	}
	else if (distance > turret->getRange()){
		turret->setState(new ChasingTurretState((MovingTurret*)turret));
	}
}