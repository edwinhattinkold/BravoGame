#include "Turret.h"
Turret::Turret(b2World* world, SDL_Renderer* renderTarget,int xPos, int yPos, TDCar* c) :B2Content(world, renderTarget, "Images/Car/car2.png") {
	w = 6;
	turretAngle = 0;
	range = 400;
	h = 6;
	car = c;
	angle = 0;
	state = new SearchingTurretState(this);
	//create car body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(xPos, yPos);
	m_body = world->CreateBody(&bodyDef);
   

	b2PolygonShape boxShape;
	boxShape.SetAsBox(w/2, h/2);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;

	fixture = m_body->CreateFixture(&boxShape, 1.0f);//shape, density

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
	dv->visit(this);
}

void Turret::accept(UpdateVisitor *uv, float deltaTime, const Uint8 *keyState)
{
	uv->visit(this, deltaTime, keyState);
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

TurretState* Turret::getState(){
	return state;
}