#include "Weapon.h"
#include "World.h"

Weapon::Weapon( World* world, B2Content* host, b2World* physics_world, SDL_Renderer * renderTarget )
{
	this->host = host;
	this->world = world;
	ammo = new Projectile( world, physics_world, renderTarget );
	projectileLoaded = true;
	fireRate = 1.00f; // <--- Measured in projectiles per second
	pastTime = 0.00f;
	spread = 40.0f;
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
	b2Vec2 direction = host->getB2DDirectionalVector();
	int randomSpread = Random::getInstance().nextInt( 0 - (spread / 2), 0 + (spread / 2) );
	float spreadFloat = 0.05f * randomSpread;
	direction.x += spreadFloat;

	direction.x *= 2.0;
	direction.y *= 2.0;

	newProjectile->setB2DPosition( host->m_body->GetWorldPoint( b2Vec2{ 0, 12.5 } ));
	newProjectile->applyLinearVelocity( direction );
	newProjectile->applyB2DAngle( host->m_body->GetAngle() );

	world->addProjectile( newProjectile );
}