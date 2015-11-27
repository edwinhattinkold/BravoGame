#pragma once
#include "B2Content.h"
#include "Hittable.h"

class Tree : public B2Content, public Hittable 
{
public:
	Tree(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY);
	~Tree();

	void accept(DrawVisitor *dv);
	b2Body * getBody();
};

