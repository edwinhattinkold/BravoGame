#pragma once

#include <iostream>
#include <vector>
#include "Location.h"
#include "SDL.h"
#include "Chunk.h"
#include "IDrawable.h"
#include "DrawVisitor.h"

class MapDrawer : public IDrawable
{
private:
	std::vector<std::vector<Chunk*>*> *chunks;
	World *world;
public:
	MapDrawer(SDL_Renderer *renderTarget, World *world);
	~MapDrawer();
	virtual void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
};

