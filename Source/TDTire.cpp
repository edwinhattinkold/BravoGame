#include "TDTire.h"

TDTire::TDTire(b2World* world, SDL_Renderer * renderTarget)
	:B2Content(world, renderTarget, "Images/Car/tire.png")
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.5f, 1.25f);
	fixture = m_body->CreateFixture(&polygonShape, 1);//shape, density
	ctfud = new CarTireFUD();
	fixture->SetUserData(ctfud);
	w = 1.5f;
	h = 3.25f;
	m_body->SetUserData(this);
	m_currentTraction = 1;
	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());
}

TDTire::~TDTire()
{
	m_body->GetWorld()->DestroyBody(m_body);
	m_groundAreas.clear();
	delete ctfud; ctfud = nullptr;
}

void TDTire::update(){
	std::cout << getAngleSDL() << std::endl;
	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());
}


void TDTire::accept(DrawVisitor *dv)
{
	dv->visit(this);
}