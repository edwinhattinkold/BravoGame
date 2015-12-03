#pragma once
#include "Weapon.h"
class MachineGun : public Weapon
{
public:
	MachineGun( World* newWorld, B2Content *host, b2World* physics_world, SDL_Renderer * renderTarget, float fireRate = 50.0f, float spread = 10.0f );
	~MachineGun();
};

