#include "TDTire.h"

TDTire::TDTire(b2World* world, SDL_Renderer * renderTarget)
	:B2Content( renderTarget, Asset_Tire)
{
	objectType = Object_Tire;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.25f,0.675f);
	fixture = m_body->CreateFixture(&polygonShape, 1);//shape, density
	ctfud = new CarTireFUD();
	fixture->SetUserData(ctfud);
	w = 0.75f;
	h = 1.625f;
	m_body->SetUserData(this);
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

void TDTire::EndContact( b2Contact* contact )
{

}

void TDTire::BeginContact( b2Contact* contact )
{

}