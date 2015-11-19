#pragma once
#include "B2Content.h"
class Turret:public B2Content{
public:
	Turret(b2World* world, SDL_Renderer* renderTarget, int xPos, int yPos);
	~Turret();
	void accept(DrawVisitor* dv);
	b2Body* getBody();
};