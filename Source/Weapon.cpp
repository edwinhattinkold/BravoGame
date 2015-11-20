#include "Weapon.h"
#include "World.h"

Weapon::Weapon( World* world, B2Content* host, b2World* physics_world, SDL_Renderer * renderTarget )
{
	this->host = host;
	this->world = world;
	ammo = new Projectile( world, physics_world, renderTarget );
	projectileLoaded = true;
	fireRate = 11.00f; // <--- Measured in projectiles per second
	pastTime = 0.00f;
	spread = 50.0f;
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
	Projectile* newProjectile = ammo->clone();
	int xVector = Random::getInstance().nextInt( 0 - (spread / 2), 0 + (spread / 2) );
	newProjectile->applyLinearVelocity( b2Vec2( xVector, 120.0f) );
	world->addProjectile( newProjectile );
}