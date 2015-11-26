#pragma once
#include "B2Content.h"
class World;

class Projectile : public B2Content, public b2ContactListener
{
private:
	World* world;
	b2World* physics_world;
	SDL_Renderer* renderTarget;
	Projectile( World* world, b2World* physics_world, SDL_Renderer * renderTarget, bool clone );
public:
	Projectile( World* world, b2World* physics_world, SDL_Renderer * renderTarget );
	~Projectile();
	
	void applyLinearVelocity( b2Vec2 vector );
	void applyB2DAngle( float rads );
	virtual void update( float deltaTime, const Uint8 *keyState);

	virtual void BeginContact( b2Contact* contact );
	virtual void EndContact( b2Contact* contact );

	Projectile* clone();
	virtual void accept( UpdateVisitor *dv );
	virtual void accept( DrawVisitor *dv );
	
};