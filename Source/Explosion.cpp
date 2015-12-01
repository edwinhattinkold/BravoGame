#include "Explosion.h"
#include "UpdateVisitor.h"
#include "World.h"

Explosion::Explosion( SDL_Renderer* renderTarget, World* world, SDL_Rect positionRect )
	:Sprite(renderTarget, Asset_Explosion, positionRect.x, positionRect.y, 5, 5, 0.05f )
{
	this->renderTarget = renderTarget;
	this->positionRect = positionRect;
	this->world = world;
}


Explosion::~Explosion()
{

}

void Explosion::accept( UpdateVisitor* uv )
{
	uv->visit( this );
}

void Explosion::update( float deltaTime )
{
	if( !animationDone() )
		updateAnimation( deltaTime );
	else
		world->removeExplosion( this );
}