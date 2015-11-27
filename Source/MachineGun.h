#pragma once
#include "Weapon.h"
class MachineGun : public Weapon
{
public:
	MachineGun( World* world, B2Content *host, b2World* physics_world, SDL_Renderer * renderTarget, float fireRate = 2.0f, float spread = 10.0f );
	~MachineGun();
};

