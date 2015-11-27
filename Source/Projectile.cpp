#include "Projectile.h"
#include "World.h"
#include <typeinfo>

Projectile::Projectile(World* world, b2World* physics_world, SDL_Renderer * renderTarget, Asset asset)
	: B2Content( renderTarget, asset )
{
	objectType = Object_Projectile;
	this->world = world;
	this->physics_world = physics_world;
	this->renderTarget = renderTarget;
	this->m_body = nullptr;
}

Projectile::Projectile( World* world, b2World* physics_world, SDL_Renderer * renderTarget, Asset asset, bool clone )
	:B2Content( renderTarget, asset )
{
	objectType = Object_Projectile;
	this->world = world;
	this->physics_world = physics_world;
	this->renderTarget = renderTarget;

	b2BodyDef bodyDef;
	bodyDef.position.Set( 2, 2 );
	bodyDef.bullet = true;
	bodyDef.type = b2_dynamicBody;

	m_body = physics_world->CreateBody( &bodyDef );
	m_body->SetAngularDamping( 3 );

	b2PolygonShape box;
	box.SetAsBox( 0.175f, 0.35f );
	
	fixture = m_body->CreateFixture( &box, 1.0f ); //shape, density

	w = 0.35f;
	h = 0.7f;

	m_body->SetUserData( this );

	updateSDLPosition( getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL() );
	updateOrigin();
}

Projectile::~Projectile()
{

}

void Projectile::applyLinearVelocity( b2Vec2 vector )
{
	m_body->ApplyLinearImpulse( vector, m_body->GetWorldCenter(), true );
}

void Projectile::applyB2DAngle( float rads )
{
	m_body->SetTransform( m_body->GetPosition(), rads );
}

void Projectile::update(float deltaTime, const Uint8 *keyState)
{
	
	updateSDLPosition( getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL() );
}

Projectile* Projectile::clone()
{
	Projectile* toReturn = new Projectile(world, physics_world, renderTarget, asset, true);
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