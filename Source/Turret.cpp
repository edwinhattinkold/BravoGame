#include "Turret.h"
Turret::Turret(b2World* world, SDL_Renderer* renderTarget,int xPos, int yPos, TDCar* c) :B2Content(world, renderTarget, "Images/Car/car2.png") {
	w = 6;
	turretAngle = 0;
	range = 350;
	h = 6;
	car = c;
	angle = 0;
	state = new SearchingTurretState(this);
	//create car body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(xPos, yPos);
	m_body = world->CreateBody(&bodyDef);

	//m_body->SetAngularDamping(3);

	b2Vec2 vertices[8];
	//het figuur van de auto.
	// W en h worden meegegeven door de user
	vertices[0].Set(w / 2, 0);
	vertices[1].Set(w / 2, h);
	vertices[2].Set(-w / 2, h);
	vertices[3].Set(-w / 2, 0);
	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 4);

	//Draaien
	m_body->SetTransform(m_body->GetPosition(), DEGTORAD * 45);
	
	fixture = m_body->CreateFixture(&polygonShape, 0.8f);//shape, density


	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());


	updateOrigin();
}

Turret::~Turret(){
	delete state;			state = nullptr;
}
b2Body* Turret::getBody()
{
	return m_body;
}

void Turret::accept(DrawVisitor *dv)
{
	state->checkState();
	state->update(10);
	
	
	m_body->SetTransform(m_body->GetPosition(),  turretAngle);

	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());
	dv->visit(this);
}

void Turret::accept(UpdateVisitor *uv)
{
	//uv->visit(this);
}

TDCar* Turret::getCar(){
	return car;
}

int Turret::getRange(){
	return range;
}

void Turret::setState(TurretState* state){
	delete this->state;
	this->state = state;
}