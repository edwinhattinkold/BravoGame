#include "Collectible.h"
#include "ContactWrapper.h"
#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

//Als elke CollectibleType een Asset heeft, waarom gebruiken we dan niet overal asset?
Collectible::Collectible(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY, World* gameWorld, Collectibletypes type)
:B2Content(renderTarget, gameWorld, world, Asset_Collectible){
	objectType = Object_Collectible;
	w = widthM;
	h = heightM;
	//create car body
	b2BodyDef bodyDef;
	myType = type;
	switch (type)
	{
	case Health:
		setAsset(Asset_Health);
		break;
	case Nitro:
		setAsset(Asset_Nitro);
		break;
	case Gasoline:
		setAsset(Asset_Gasoline);
		break;
	case Oil:
		setAsset(Asset_Oil);
		break;
	}

	objectiveType = getAsset(); //Make the asset known to IObjective for missions

	bodyDef.type = b2_staticBody;

	bodyDef.position.Set(posX, posY);
	m_body = world->CreateBody(&bodyDef);

	m_body->SetType(b2_staticBody);
	b2Vec2 vertices[4];
	//het figuur van de auto.
	// W en h worden meegegeven door de user
	vertices[0].Set(w / 2, 0);
	vertices[1].Set(w / 2, h);
	vertices[2].Set(-w / 2, h);
	vertices[3].Set(-w / 2, 0);
	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 4);
	
	//Draaien
	m_body->SetTransform(m_body->GetPosition(), DEGTORAD * 0);
	fixture = m_body->CreateFixture(&polygonShape, 0.0f);//shape, density
	fixture->SetSensor(true);

	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());
	updateOrigin();

	setContactWrapper(new ContactWrapper(this));
}


Collectible::~Collectible()
{
}

b2Body * Collectible::getBody()
{
	return m_body;
}

void Collectible::accept(DrawVisitor *dv)
{
	dv->visit(this);
}

void Collectible::update(float deltaTime, const Uint8 *keyState){

}