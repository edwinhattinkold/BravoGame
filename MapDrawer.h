#pragma once

#include <iostream>
#include <vector>
#include "Location.h"
#include "SDL.h"
#include "MapGenerator.h"

class MapDrawer
{
private:
	std::vector<Location> *locations;
	MapGenerator *mapGenerator;
public:
	MapDrawer(SDL_Renderer *renderTarget);
	~MapDrawer();
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
};

