#pragma once
#include "B2Content.h"
#include "Hittable.h"

class World;

class CollideObject : public B2Content, public Hittable
{
public:
	enum CollideType {
		Desert_Tree = 0,
		Desert_Piramid,
		Ice_Tree,
		Ice_Tent,
		Collide_Default
	};
	CollideType myType;
	CollideObject(World* world, b2World* physicsWorld, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY, CollideType type);
	~CollideObject();

	void accept(DrawVisitor *dv);
	void accept(UpdateVisitor *uv);
	b2Body * getBody();
	void checkDeath();
};

