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
	turret->turretAngle = atan2(turret->getCar()->getCenterXSDL() - turret->getCenterXSDL(), turret->getCar()->getCenterYSDL() - turret->getCenterYSDL());
}