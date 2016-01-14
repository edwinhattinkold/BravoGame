#include "Projectile.h"
#include "World.h"
#include <typeinfo>
#include "ContactWrapper.h"
Projectile::Projectile( World* world, b2World* physicsWorld, SDL_Renderer * renderTarget, Asset asset, int damage, float speed )
	: B2Content( renderTarget, world, physicsWorld, asset )
{
	muzzleFlash = Assets::getInstance()->getAsset( Asset_Muzzleflash );
	objectType = Object_Projectile;
	this->renderTarget = renderTarget;
	this->m_body = nullptr;
	this->damage = damage;
	this->speed = speed;
}

Projectile::Projectile( World* world, b2World* physicsWorld, SDL_Renderer * renderTarget, Asset asset, int damage, float speed, SDL_Texture* muzzleFlashTexture )
	:B2Content( renderTarget, world, physicsWorld, asset )
{
	muzzleFlash = muzzleFlashTexture;
	shouldDrawMuzzleFlash = true;
	objectType = Object_Projectile;
	this->renderTarget = renderTarget;
	this->damage = damage;
	this->speed = speed;
	this->deleteAfter = 3.00f;

	b2BodyDef bodyDef;
	bodyDef.position.Set( 2, 2 );
	bodyDef.bullet = true;
	bodyDef.type = b2_dynamicBody;

	m_body = physicsWorld->CreateBody( &bodyDef );
	m_body->SetAngularDamping( 3 );

	b2PolygonShape box;
	box.SetAsBox( 0.175f, 0.35f );
	
	fixture = m_body->CreateFixture( &box, 1.0f ); //shape, density

	w = 0.35f;
	h = 0.7f;

	setContactWrapper(new ContactWrapper(this));

	updateSDLPosition( getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL() );
	updateOrigin();
}

Projectile::~Projectile()
{

}

void Projectile::setDirection( b2Vec2 vector )
{
	vector.x *= speed;
	vector.y *= speed;
	m_body->ApplyLinearImpulse( vector, m_body->GetWorldCenter(), true );
}

void Projectile::applyB2DAngle( float rads )
{
	m_body->SetTransform( m_body->GetPosition(), rads );
}

void Projectile::update(float deltaTime, const Uint8 *keyState)
{
	updateSDLPosition( getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL() );
	deleteAfter -= deltaTime;
	if( deleteAfter <= 0.00f )
		world->destroyProjectile( this );
}

Projectile* Projectile::clone()
{
	Projectile* toReturn = new Projectile( world, physicsWorld, renderTarget, asset, damage, speed, muzzleFlash );
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

int Projectile::getDamage()
{
	return damage;
}

void Projectile::drawProjectile( SDL_Renderer* renderTarget, SDL_Rect cameraRect )
{
	SDL_Rect drawingRect = { positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h };
	if( shouldDrawMuzzleFlash )
	{
		SDL_QueryTexture( muzzleFlash, NULL, NULL, &drawingRect.w, &drawingRect.h );
		drawingRect.x -= drawingRect.w / 2 - positionRect.w / 2;
		drawingRect.y -= drawingRect.h / 2 - positionRect.h / 2;
		SDL_RenderCopyEx( renderTarget, muzzleFlash, NULL, &drawingRect, angle, NULL, SDL_FLIP_NONE );
		shouldDrawMuzzleFlash = false;
	}
	else
	{
		animations->at( currentAnimation )->drawCar( renderTarget, drawingRect, angle );
	}
}