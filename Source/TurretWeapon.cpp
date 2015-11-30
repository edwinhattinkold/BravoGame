#include "TurretWeapon.h"

TurretWeapon::TurretWeapon(World* world, B2Content* host, b2World* physics_world, SDL_Renderer * renderTarget, float fireRate, float spread)
: Weapon(world, host, physics_world, renderTarget, fireRate, spread)
{
	setAmmo(new Projectile(world, physics_world, renderTarget, Asset_MachineGun_Bullet, 50, 1000));
}


TurretWeapon::~TurretWeapon()
{

}