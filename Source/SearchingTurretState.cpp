#include "SearchingTurretState.h"
#include "ShootingTurretState.h"
#include "DeadTurretState.h"
#include "Turret.h"
SearchingTurretState::SearchingTurretState(Turret* turret) :TurretState(turret){

}

SearchingTurretState::~SearchingTurretState(){}

void SearchingTurretState::checkState(){
	float distance = calculateDistance();
	if (turret->isDead()){
		turret->setState(new DeadTurretState(turret));
	}
	else if (distance < turret->getRange()){
		turret->setState(new ShootingTurretState(turret));
	}
}

void SearchingTurretState::update(float deltaTime){
	turret->setAsset(Asset_Turret_Calm);
	turret->turretAngle--;
	if (turret->turretAngle < 0){
		turret->turretAngle = 359;
	}
	turret->getWeapon()->update(deltaTime);
}