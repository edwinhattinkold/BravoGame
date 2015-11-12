#include "TDTire.h"

TDTire::TDTire(b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.5f, 1.25f);
	b2Fixture* fixture = m_body->CreateFixture(&polygonShape, 1);//shape, density
	ctfud = new CarTireFUD();
	fixture->SetUserData(ctfud);

	m_body->SetUserData(this);
	m_currentTraction = 1;
}

float TDTire::getAngle()
{
	return m_body->GetAngle();
}
float TDTire::getX()
{
	return m_body->GetPosition().x;
}

float TDTire::getY()
{
	return m_body->GetPosition().y;
}

TDTire::~TDTire()
{
	m_body->GetWorld()->DestroyBody(m_body);
	m_groundAreas.clear();
	delete ctfud; ctfud = nullptr;
}