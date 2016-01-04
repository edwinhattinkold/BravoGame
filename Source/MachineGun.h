#pragma once
#include "Weapon.h"
class MachineGun : public Weapon
{
private:
	void fire();
public:
	MachineGun( World* newWorld, B2Content *host, b2World* physics_world, SDL_Renderer * renderTarget, Camera* camera, float fireRate = 50.0f, float spread = 10.0f );
	~MachineGun();
};

