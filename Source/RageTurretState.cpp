#include "RageTurretState.h"
#include "DeadTurretState.h"
RageTurretState::RageTurretState(MovingTurret* turret) :ChasingTurretState(turret){

}

RageTurretState::~RageTurretState(){

}

void RageTurretState::update(float deltaTime){
	ChasingTurretState::update(deltaTime);
	turret->setAsset(Asset_Turret_Angry);
	double radAngle = 90 + RADTODEG * atan2((turret->getCar()->getCenterYSDL() - turret->getCenterYSDL()), (turret->getCar()->getCenterXSDL() - turret->getCenterXSDL()));
	turret->turretAngle = radAngle;
	turret->getWeapon()->pullTrigger();
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