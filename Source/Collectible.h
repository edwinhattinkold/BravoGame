#pragma once
#include "B2Content.h"

class Collectible : public B2Content
{
public:
	Collectible( b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY);
	~Collectible();

	virtual void accept(DrawVisitor *dv);
	b2Body * getBody();
	void addCollectible(int,int,int,int);
};



