#pragma once
#include "B2Content.h"

class Projectile : public B2Content
{
private:
	b2World* world;
	SDL_Renderer* renderTarget;
	Projectile( b2World* world, SDL_Renderer * renderTarget, bool clone);
public:
	Projectile( b2World* world, SDL_Renderer * renderTarget );
	~Projectile();
	
	Projectile* clone();
	virtual void accept( UpdateVisitor *dv );
	virtual void accept( DrawVisitor *dv );
};