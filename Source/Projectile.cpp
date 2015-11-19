#include "Projectile.h"


Projectile::Projectile( b2World* world, SDL_Renderer * renderTarget )
	: B2Content( world, renderTarget, "Images/Objects/Shooting/bullet.png" )
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	m_body = world->CreateBody( &bodyDef );
	m_body->IsBullet = true;


	b2CircleShape circleShape;
	
	circleShape.m_p.Set( 0, 0 ); //position, relative to body position
	circleShape.m_radius = 1;

	fixture = m_body->CreateFixture( &circleShape, 0.1f ); //shape, density
	fixture->IsSensor = false;

	w = 0.5f;
	h = 1.0f;

	m_body->SetUserData( this );
	updateSDLPosition( getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL() );
}

Projectile::~Projectile()
{

}