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
float test = 0;
void ShootingTurretState::update(float deltaTime){
	double radAngle = 90 + RADTODEG * atan2((turret->getCar()->getCenterYSDL() - turret->getCenterYSDL()), (turret->getCar()->getCenterXSDL() - turret->getCenterXSDL()));
	std::cout << radAngle << std::endl;
	turret->turretAngle = radAngle;
	test += deltaTime;
	if (test > 0.3){
		turret->getWeapon()->pullTrigger();
		test = 0;
	}
	turret->getWeapon()->update(deltaTime);
}