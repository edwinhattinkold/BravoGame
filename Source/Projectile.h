#pragma once
#include "B2Content.h"
class Projectile : B2Content
{
public:
	Projectile( b2World* world, SDL_Renderer * renderTarget );
	~Projectile();
};