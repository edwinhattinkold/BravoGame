#pragma once
#include "B2Content.h"
class World;

class Projectile : public B2Content
{
private:
	World* world;
	b2World* physics_world;
	SDL_Renderer* renderTarget;
	Projectile( World* world, b2World* physicsWorld, SDL_Renderer * renderTarget, Asset asset, int damage, float speed, bool clone );

	void BeginContact( b2Contact* contact );
	void EndContact( b2Contact* contact );
protected:
	int damage;
	float speed;
public:
	Projectile( World* world, b2World* physicsWorld, SDL_Renderer * renderTarget, Asset asset, int damage, float speed );
	~Projectile();
	
	void setDirection( b2Vec2 vector );
	void applyB2DAngle( float rads );
	virtual void update( float deltaTime, const Uint8 *keyState);

	Projectile* clone();
	void accept( UpdateVisitor *dv );
	void accept( DrawVisitor *dv );
	int getDamage();
};