#pragma once

#include <iostream>
#include <vector>
#include "Location.h"
#include "SDL.h"
#include "MapGenerator.h"
#include "IDrawable.h"
#include "DrawVisitor.h"

class MapDrawer : public IDrawable
{
private:
	std::vector<Location> *locations;
	MapGenerator *mapGenerator;
public:
	MapDrawer(SDL_Renderer *renderTarget);
	~MapDrawer();
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	void Accept(DrawVisitor &dv);
};

