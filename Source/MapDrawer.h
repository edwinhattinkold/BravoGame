#pragma once

#include <iostream>
#include <vector>
#include "Location.h"
#include "SDL.h"
#include "Chunk.h"

class MapDrawer
{
private:
	std::vector<std::vector<Chunk*>*> *chunks;
public:
	MapDrawer(SDL_Renderer *renderTarget);
	~MapDrawer();
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
};

