#pragma once

#include <iostream>
#include <vector>
#include "Location.h"
#include "SDL.h"
#include "Chunk.h"

class MapDrawer
{
private:
	Chunk *chunk;
public:
	MapDrawer(SDL_Renderer *renderTarget);
	~MapDrawer();
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
};

