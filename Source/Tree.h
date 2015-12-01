#pragma once
#include "B2Content.h"
#include "Hittable.h"

class World;

class Tree : public B2Content, public Hittable 
{
public:
	Tree( World* world, b2World* physicsWorld, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY );
	~Tree();

	void accept(DrawVisitor *dv);
	void accept( UpdateVisitor *uv );
	b2Body * getBody();
	void checkDeath();
};

