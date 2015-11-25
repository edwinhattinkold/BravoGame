#pragma once
#include "Sprite.h"
class HudObject :
	public Sprite
{
public:
	HudObject( SDL_Renderer* renderTarget, std::string filePath );
	~HudObject();

	virtual void accept( DrawVisitor *dv );
};

