#include "DeadTurretState.h"
#include "Turret.h"

DeadTurretState::DeadTurretState(Turret* turret) :TurretState(turret){
	exploded = false;
}

DeadTurretState::~DeadTurretState(){}

void DeadTurretState::checkState(){
	
}
void DeadTurretState::update(float deltaTime){
	if (!exploded){
		turret->world->createExplosion(turret->positionRect);
		turret->world->getCar()->addScore( 1000 );
		exploded = true;
	}
	turret->setAsset(Asset_Turret_Dead);
}