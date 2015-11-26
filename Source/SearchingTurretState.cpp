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
}