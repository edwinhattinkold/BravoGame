#include "World.h"
#include "math.h"

Weapon::Weapon( World* world, B2Content* host, b2World* physics_world, SDL_Renderer * renderTarget, float fireRate, float spread )
{
	this->host = host;
	this->world = world;
	projectileLoaded = true;
	this->fireRate = fireRate; // <--- Measured in freedoms per second
	pastTime = 0.00f;
	this->spread = spread;
	sound = Sound::getInstance();
}

Weapon::~Weapon()
{
	delete ammo;		ammo = nullptr;
}

void Weapon::setAmmo( Projectile* projectile )
{
	this->ammo = projectile;
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
	world->cameraShake();
	Projectile* newProjectile = ammo->clone();
	b2Vec2 direction = host->getB2DDirectionalVector();
	int randomSpread = Random::getInstance().nextInt( 0 - (spread / 2), 0 + (spread / 2) );
	float spreadFloat = 0.02f * randomSpread;
	float randomDistance = 0.4f * Random::getInstance().nextInt(0, 2);
	direction.x += spreadFloat;
	direction.y += spreadFloat;
	direction.Normalize();

	newProjectile->setB2DPosition( host->m_body->GetWorldPoint( b2Vec2{ 0, 7 + randomDistance } ));
	newProjectile->setDirection( direction );
	newProjectile->applyB2DAngle( host->m_body->GetAngle() );

	world->addProjectile( newProjectile );
}