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
public:
	MapDrawer(SDL_Renderer *renderTarget);
	~MapDrawer();
	virtual void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
};

