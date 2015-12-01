#include "SearchingTurretState.h"
#include "ShootingTurretState.h"
#include "Turret.h"
SearchingTurretState::SearchingTurretState(Turret* turret) :TurretState(turret){

}

SearchingTurretState::~SearchingTurretState(){}

void SearchingTurretState::checkState(){
	float distance = calculateDistance();
	if (distance < turret->getRange()){
		
		turret->setState(new ShootingTurretState(turret));
	}
}

void SearchingTurretState::update(float deltaTime){
	turret->turretAngle--;
	if (turret->turretAngle < 0){
		turret->turretAngle = 359;
	}
	turret->getWeapon()->pullTrigger();
	turret->getWeapon()->update(deltaTime);
}