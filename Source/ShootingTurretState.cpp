#include "ShootingTurretState.h"
#include "SearchingTurretState.h"
#include "DeadTurretState.h"
#include "Turret.h"
ShootingTurretState::ShootingTurretState(Turret* turret) :TurretState(turret){

}

ShootingTurretState::~ShootingTurretState(){}

void ShootingTurretState::checkState(){
	float distance = calculateDistance();
	if (turret->isDead()){
		turret->setState(new DeadTurretState(turret));
	}
	else if (distance > turret->getRange()){
		turret->setState(new SearchingTurretState(turret));
	}
}
void ShootingTurretState::update(float deltaTime){
	float degPerSec = 200;
	turret->setAsset(Asset_Turret_Angry);
	double newAngle = fmod(450 + RADTODEG * atan2((turret->getCar()->getCenterYSDL() - turret->getCenterYSDL()), (turret->getCar()->getCenterXSDL() - turret->getCenterXSDL())), 360);
	if (deltaTime * degPerSec < abs(newAngle - turret->turretAngle)){
		if (fmod(turret->turretAngle - newAngle+360, 360) > 180){
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