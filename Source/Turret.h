#pragma once
#include "B2Content.h"
#include "TDCar.h"
#include <math.h>
class Turret:public B2Content{
private:
	int currentTargetX;
	int currentTargetY;
	TDCar* car;
public:
	Turret(b2World* world, SDL_Renderer* renderTarget, int xPos, int yPos, TDCar* c);
	~Turret();
	void accept(DrawVisitor* dv);
	void accept(UpdateVisitor* uv);
	b2Body* getBody();
};