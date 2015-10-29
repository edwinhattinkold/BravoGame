#include "Car.h"
#include <Box2D/Box2D.h>

Car::Car(int x, int y, b2World *world) 
{
	//body definition
	myBodyDef.type = b2_dynamicBody;

	//shape definition
	
	polygonShape.SetAsBox(1, 1); //a 2x2 rectangle

	//fixture definition
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	myBodyDef.position.Set(x, y);
	bodie = world->CreateBody(&myBodyDef);
	bodie->CreateFixture(&myFixtureDef);
}


Car::~Car()
{
}

void Car::Update(float delta, const Uint8 *keyState){
	isActive = true;
	if (keyState[keys[0]])
	{

		bodie->ApplyLinearImpulse(b2Vec2(0, 50), bodie->GetWorldCenter(),true);
	}
	else
		isActive = false;

	
}

int Car::getX(){
	return myBodyDef.position.x;
}