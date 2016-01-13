#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <Box2D/Box2D.h>
#include <vector>
#include "Sprite.h"
#include <SDL.h>
#include "DrawContainer.h"
#include "UpdateContainer.h"
#include <string>

class World;
class ContactWrapper;
#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif
const int sdlScale = 20;

enum ObjectTypes { Object_Tire, Object_Car, Object_Projectile, Object_Tree, Object_Collide, Object_Turret, Object_Collectible };

class B2Content : public Sprite
{
	
private:
	int transform(float dgrs);
protected:
	ObjectTypes objectType;
	World* world;
	b2World* physicsWorld;
	
public:
	ContactWrapper* contactWrapper;
	bool isOnDeathRow;
	b2Body* m_body;
	float w, h;
	b2Fixture* fixture;
	B2Content( SDL_Renderer* renderTarget, World* world, b2World* physicsWorld, Asset asset );
	~B2Content();
	//custom
	b2Vec2 getB2DPosition();
	void setB2DPosition( b2Vec2 position );
	b2Vec2 getB2DDirectionalVector();
	b2Vec2 getSDLPosition();
	b2Vec2 getSDLDirectionalVector();
	float getAngleSDL();

	float getCenterXSDL();
	float getCenterYSDL();
	float getSDLWidth();
	float getSDLHeight();
	void setB2DAngle(float angle);
	virtual void accept(DrawVisitor *dv);
	void setContactWrapper(ContactWrapper* cw);
	ObjectTypes getObjectType();
	virtual void muzzleFlash();
};

