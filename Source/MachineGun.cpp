#include "MachineGun.h"


MachineGun::MachineGun( World* newWorld, B2Content* host, b2World* physics_world, SDL_Renderer * renderTarget, float fireRate, float spread)
	: Weapon( newWorld, host, physics_world, renderTarget, fireRate, spread )
{
	Projectile* projectile = new Projectile( newWorld, physics_world, renderTarget, Asset_MachineGun_Bullet, 50, 100 );
	setAmmo( projectile );
}


MachineGun::~MachineGun()
{

}