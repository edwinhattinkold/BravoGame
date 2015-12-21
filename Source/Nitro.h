#pragma once
#include "B2Content.h"
class Nitro : public B2Content
{
public:
	Nitro(b2World * world, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY, World* gameWorld);
	~Nitro();
	virtual void accept(DrawVisitor *dv);
	b2Body * getBody();
	void addCollectible(int, int, int, int);
	virtual void update(float delta, const Uint8 *keyState);
};

