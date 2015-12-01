#pragma once
#include "Sprite.h"
class UpdateVisitor;
class World;

class Explosion : public Sprite
{
private:
	SDL_Renderer* renderTarget;
	World* world;
public:
	Explosion(SDL_Renderer* renderTarget, World* world, SDL_Rect positionRect);
	~Explosion();

	void accept( UpdateVisitor* uv );
	void update( float deltaTime );
};

