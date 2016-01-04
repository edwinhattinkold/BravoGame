#include "MachineGun.h"

MachineGun::MachineGun( World* newWorld, B2Content* host, b2World* physics_world, SDL_Renderer * renderTarget, Camera* camera, float fireRate, float spread)
	: Weapon( newWorld, host, physics_world, renderTarget, camera, 10.0f, spread )
{
	Projectile* projectile = new Projectile( newWorld, physics_world, renderTarget, Asset_MachineGun_Bullet, 50, 100 );
	setAmmo( projectile );
}


MachineGun::~MachineGun()
{

}

void MachineGun::fire()
{
	sound->playSound( Sound_Shooting_Machine_Gun );
	Weapon::fire();
}