#pragma once
#include "World.h"
#include "Weapon.h"
class Turret;
class TurretWeapon : public Weapon
{
private:
	Turret* turret;
public:
	TurretWeapon(World* world, Turret *host, b2World* physics_world, SDL_Renderer * renderTarget, float fireRate = 30.0f, float spread = 5.0f);
	~TurretWeapon();
	void fire();
};

