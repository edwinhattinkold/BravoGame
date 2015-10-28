#pragma once
#include "B2Content.h"

class Tree : public B2Content
{
public:

	int w, h;
	Tree(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY);
	~Tree();

	virtual void accept(DrawVisitor *dv);
};

