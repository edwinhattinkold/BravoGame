#pragma once
#include "B2Content.h"
#include "TDCar.h"
#include <math.h>
#include "SearchingTurretState.h"
#include "TurretState.h"
#include "Hittable.h"
#include "TurretWeapon.h"

class Turret:public B2Content, public Hittable{
private:
	int currentTargetX;
	int currentTargetY;
	int range;
	Weapon* weapon;
	TDCar* car;
	TurretState* state;
public:
	float turretAngle;
	World* world;
	Turret(b2World* world, SDL_Renderer* renderTarget, int xPos, int yPos, TDCar* c, World* gameWorld);
	~Turret();
	void accept(DrawVisitor* dv);
	void accept(UpdateVisitor *uv);
	b2Body* getBody();
	TDCar* getCar();
	int getRange();
	void setState(TurretState* state);
	TurretState* getState();
	Weapon* getWeapon();
	void moveToTarget(float);
	void stayOnSpot();
};