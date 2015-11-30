#pragma once
#include "Weapon.h"
class TurretWeapon : public Weapon
{
public:
	TurretWeapon(World* world, B2Content *host, b2World* physics_world, SDL_Renderer * renderTarget, float fireRate = 30.0f, float spread = 5.0f);
	~TurretWeapon();
};

