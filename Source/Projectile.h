#pragma once
#include "B2Content.h"
class World;

class Projectile : public B2Content
{
private:
	World* world;
	b2World* physics_world;
	SDL_Renderer* renderTarget;
	Projectile( World* world, b2World* physics_world, SDL_Renderer * renderTarget, Asset asset, bool clone );

	void BeginContact( b2Contact* contact );
	void EndContact( b2Contact* contact );
public:
	Projectile( World* world, b2World* physics_world, SDL_Renderer * renderTarget, Asset asset);
	~Projectile();
	
	void applyLinearVelocity( b2Vec2 vector );
	void applyB2DAngle( float rads );
	virtual void update( float deltaTime, const Uint8 *keyState);

	Projectile* clone();
	void accept( UpdateVisitor *dv );
	void accept( DrawVisitor *dv );
};