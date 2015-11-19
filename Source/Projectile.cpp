#include "Projectile.h"


Projectile::Projectile( b2World* world, SDL_Renderer * renderTarget )
	: B2Content( renderTarget, "Images/Objects/Shooting/bullet.png" )
{
	this->world = world;
	this->renderTarget = renderTarget;
	this->m_body = nullptr;
}

Projectile::Projectile( b2World* world, SDL_Renderer * renderTarget, bool clone )
	:B2Content( renderTarget, "Images/Objects/Shooting/bullet.png" )
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	m_body = world->CreateBody( &bodyDef );
	m_body->SetBullet( true );


	b2CircleShape circleShape;

	circleShape.m_p.Set( 0, 0 ); //position, relative to body position
	circleShape.m_radius = 2;

	fixture = m_body->CreateFixture( &circleShape, 0.1f ); //shape, density
	fixture->SetSensor( false );

	w = 0.5f;
	h = 1.0f;

	m_body->SetUserData( this );
	updateSDLPosition( getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL() );
}

Projectile::~Projectile()
{

}

Projectile* Projectile::clone()
{
	Projectile* toReturn = new Projectile(world, renderTarget, true);
	return toReturn;
}

void Projectile::accept( DrawVisitor *dv )
{
	dv->visit( this );
}

void Projectile::accept( UpdateVisitor *uv )
{
	uv->visit( this );
}