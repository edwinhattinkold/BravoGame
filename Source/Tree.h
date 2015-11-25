#pragma once
#include "B2Content.h"

class Tree : public B2Content, public b2ContactListener
{
public:
	Tree(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY);
	~Tree();

	virtual void accept(DrawVisitor *dv);
	b2Body * getBody();
	virtual void BeginContact( b2Contact* contact );
	virtual void EndContact( b2Contact* contact );
};

