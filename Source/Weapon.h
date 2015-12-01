#pragma once
#include "Projectile.h"
#include "Random.h"

class World;

class Weapon
{
protected:
	World* world;
	Projectile* ammo;
	float fireRate;
	float pastTime;
	float spread;
	bool projectileLoaded;
	virtual void fire();
	B2Content *host;
	
public:
	Weapon( World* world, B2Content *host, b2World* physics_world, SDL_Renderer * renderTarget, float fireRate, float spread );
	~Weapon();
	void setAmmo( Projectile* projectile );
	void update( float deltaTime );
	void pullTrigger( );
};