#include "Turret.h"
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
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(xPos, yPos);
	m_body = world->CreateBody(&bodyDef);
   

	b2PolygonShape boxShape;
	boxShape.SetAsBox(w/2, h/2);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;

	fixture = m_body->CreateFixture(&boxShape, 1.0f);//shape, density

	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());
	

	updateOrigin();
	m_body->SetUserData(this);
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

void Turret::stayOnSpot()
{
	this->m_body->SetLinearVelocity(b2Vec2(0, 0));
}
void Turret::moveToTarget(float dt)
{ 
	float x = car->getB2DPosition().x;
	float y = car->getB2DPosition().y;
	//Snelheid van de vector instellen	

	float relativeSpeed = 0.25f / dt;

	//X & Y van de vector instellen.
	float ownX = this->getB2DPosition().x;
	float ownY = this->getB2DPosition().y;

	//Doel vector berekenen.
	float vec1 = x - ownX;
	float vec2 = y - ownY;

	//Lengte van de vector berekenen.
	float length = sqrt(vec1 * vec1 + vec2 * vec2);

	//Vector normaliseren
	float normalizedX = vec1 /= length;
	float normalizedY = vec2 /= length;

	//De vector scalen.
	float xFinal = normalizedX *= relativeSpeed;
	float yFinal = normalizedY *= relativeSpeed;


	this->m_body->SetLinearVelocity(b2Vec2(xFinal, yFinal));
	std::cout << xFinal << std::endl;
	std::cout << yFinal << std::endl << std::endl;

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