#include "ShootingTurretState.h"
#include "SearchingTurretState.h"
#include "Turret.h"
ShootingTurretState::ShootingTurretState(Turret* turret) :TurretState(turret){

}

ShootingTurretState::~ShootingTurretState(){}

void ShootingTurretState::checkState(){
	float distance = calculateDistance();
	if (distance > turret->getRange()){

		turret->setState(new SearchingTurretState(turret));
	}
}

void ShootingTurretState::update(float deltaTime){
	turret->turretAngle = (360 - RADTODEG * atan2(abs(turret->getCar()->getCenterXSDL() - turret->getCenterXSDL()), abs(turret->getCar()->getCenterYSDL() - turret->getCenterYSDL()))) * DEGTORAD;
}