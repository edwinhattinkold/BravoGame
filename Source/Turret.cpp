#include "Turret.h"
#include "ContactWrapper.h"
Turret::Turret(b2World* world, SDL_Renderer* renderTarget, int xPos, int yPos, TDCar* c, World* gameWorld) :B2Content(renderTarget, gameWorld, world, Asset_Turret_Calm), Hittable(1000) {
	w = 5;
	this->world = gameWorld;
	objectType = Object_Turret;
	turretAngle = 0;
	range = 400;
	h = 5;
	car = c;
	angle = 0;
	state = new SearchingTurretState(this);
	weapon = new TurretWeapon(gameWorld, this, world, renderTarget);
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
	setContactWrapper(new ContactWrapper(this));
}

Turret::~Turret(){
	delete state;			state = nullptr;
	delete weapon;			weapon = nullptr;
}
b2Body* Turret::getBody()
{
	return m_body;
}

void Turret::accept(DrawVisitor *dv)
{
	dv->visit(this);
}

void Turret::accept(UpdateVisitor *uv)
{
	uv->visit(this);
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

Weapon* Turret::getWeapon(){
	return weapon;
}