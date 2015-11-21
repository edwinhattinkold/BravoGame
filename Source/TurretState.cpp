#include "TurretState.h"
#include "Turret.h"
TurretState::TurretState(Turret* turret){
	this->turret = turret;
}
TurretState::~TurretState(){

}

float TurretState::calculateDistance(){
	float carX = turret->getCar()->getCenterXSDL();
	float carY = turret->getCar()->getCenterYSDL();
	float x = turret->getCenterXSDL();
	float y = turret->getCenterYSDL();
	float deltaX = abs(carX - x);
	float deltaY = abs(carY - y);
	return sqrt(deltaX * deltaX + deltaY * deltaY);
}

void TurretState::checkState(){}
void TurretState::update(float deltaTime){}