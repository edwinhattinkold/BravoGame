#include "Weapon.h"
#include "World.h"

Weapon::Weapon( World* world, B2Content* host, b2World* physics_world, SDL_Renderer * renderTarget )
{
	this->host = host;
	this->world = world;
	ammo = new Projectile( physics_world, renderTarget );
	projectileLoaded = true;
	fireRate = 1.00f; // <--- Measured in projectiles per second
	pastTime = 0.00f;
}


Weapon::~Weapon()
{
	delete ammo;		ammo = nullptr;
}

void Weapon::update( float deltaTime )
{
	pastTime += deltaTime;

	if( pastTime >= 1.00f / fireRate )
		projectileLoaded = true;
}

void Weapon::pullTrigger( )
{
	if( projectileLoaded )
	{
		fire();
		pastTime = 0.00f;
		projectileLoaded = false;
	}
}

void Weapon::fire()
{
	world->addProjectile( ammo->clone() );
}