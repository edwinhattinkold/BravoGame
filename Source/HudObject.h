#pragma once
#include "Sprite.h"
class HudObject :
	public Sprite
{
public:
	HudObject( SDL_Renderer* renderTarget, Asset asset );
	~HudObject();

	virtual void accept( DrawVisitor *dv );
};

