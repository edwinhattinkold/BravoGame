#ifndef CAR_H
#define CAR_H
#include<SDL.h>
#include<string>

#include <Box2D/Box2D.h>

class Car
{
private:
	b2BodyDef myBodyDef;
	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	b2Body* bodie;

	bool isActive;
	SDL_Scancode keys[4];
	float moveSpeed;
public:
	Car(int x, int y, b2World *world);
	~Car();
	virtual void Update(float delta, const Uint8 *keyState);
	int getX();
	
};
#endif

