#include "IdleTurretState.h"
#include "DeadTurretState.h"
#include "ChasingTurretState.h"
#include "Turret.h"
IdleTurretState::IdleTurretState(Turret* turret) :TurretState(turret){

}
IdleTurretState::~IdleTurretState(){

}
void IdleTurretState::checkState(){
	if (turret->isDead()){
		turret->setState(new DeadTurretState(turret));
	}
	else if (calculateDistance() < (turret->getRange() * 3)){
		turret->setState(new ChasingTurretState((MovingTurret*)turret));
	}
}
void IdleTurretState::update(float deltaTime){
	turret->getBody()->SetLinearVelocity(b2Vec2(0,0));
}