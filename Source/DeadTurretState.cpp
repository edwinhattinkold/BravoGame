#include "DeadTurretState.h"
#include "Turret.h"

DeadTurretState::DeadTurretState(Turret* turret) :TurretState(turret){

}

DeadTurretState::~DeadTurretState(){}

void DeadTurretState::checkState(){
	
}
void DeadTurretState::update(float deltaTime){
	turret->setAsset(Asset_Turret_Dead);
}