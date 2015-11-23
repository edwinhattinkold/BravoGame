#pragma once
#include "Projectile.h"
#include "Random.h"

class World;

class Weapon
{
private:
	World* world;
	Projectile* ammo;
	float fireRate;
	float pastTime;
	float spread;
	bool projectileLoaded;
	void fire();
	B2Content *host;
public:
	Weapon( World* world, B2Content *host, b2World* physics_world, SDL_Renderer * renderTarget );
	~Weapon();
	void update( float deltaTime );
	void pullTrigger( );
};