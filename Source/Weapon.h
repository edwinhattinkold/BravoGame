#pragma once
#include "Projectile.h"
#include "Random.h"
#include "Sound.h"
#include "Camera.h"
class World;

class Weapon
{
protected:
	World* world;
	Projectile* ammo;
	Camera* camera;
	float fireRate;
	float pastTime;
	float spread;
	bool projectileLoaded;
	virtual void fire();
	B2Content *host;
	Sound* sound;
public:
	Weapon( World* world, B2Content *host, b2World* physics_world, SDL_Renderer * renderTarget, Camera* camera, float fireRate, float spread );
	~Weapon();
	void setAmmo( Projectile* projectile );
	void update( float deltaTime );
	void pullTrigger( );
};