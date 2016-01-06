#pragma once
#include "B2Content.h"
#include "IObjective.h"

class Collectible : public B2Content, public IObjective
{
public:
	
	enum Collectibletypes {
		Gasoline = 0, 
		Collect,
		Nitro,
		Oil	
	};
	Collectibletypes myType;
	Collectible(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY, World* gameWorld, Collectibletypes type);
	~Collectible();

	virtual void accept(DrawVisitor *dv);
	b2Body * getBody();
	void addCollectible(int,int,int,int);
	virtual void update(float delta, const Uint8 *keyState);
};



