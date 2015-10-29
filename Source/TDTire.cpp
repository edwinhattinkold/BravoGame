#include "TDTire.h"
#include "CarTireFud.h"

TDTire::TDTire(b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.5f, 1.25f);
	b2Fixture* fixture = m_body->CreateFixture(&polygonShape, 1);//shape, density
	fixture->SetUserData(new CarTireFUD());

	m_body->SetUserData(this);

	m_currentTraction = 1;
}


TDTire::~TDTire()
{
	m_body->GetWorld()->DestroyBody(m_body);
}
