#include "TDTire.h"
TDTire::TDTire( World* world, b2World* physicsWorld, SDL_Renderer * renderTarget)
	:B2Content( renderTarget, world, physicsWorld, Asset_Tire)
{
	objectType = Object_Tire;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	m_body = physicsWorld->CreateBody( &bodyDef );

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.25f,0.675f);
	fixture = m_body->CreateFixture(&polygonShape, 1);//shape, density
	ctfud = new CarTireFUD();
	fixture->SetUserData(ctfud);
	w = 0.75f;
	h = 1.625f;
	contactable = new Contactable(this);
	m_body->SetUserData(contactable);
	m_currentTraction = 1;
	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());
}

TDTire::~TDTire()
{
	m_groundAreas.clear();
	delete ctfud; ctfud = nullptr;
}

void TDTire::update()
{
	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());
}


void TDTire::accept(DrawVisitor *dv)
{
	dv->visit(this);
}