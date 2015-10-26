#pragma once

#include <iostream>
#include <vector>
#include "Location.h"
#include "SDL.h"
#include "Chunk.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "DrawVisitor.h"

class MapDrawer : public IDrawable, public IUpdateable
{
private:
	std::vector<std::vector<Chunk*>*> *chunks;
	int minX, maxX, minY, maxY;
	SDL_Rect *cameraRect;
	World *world;
public:
	MapDrawer(SDL_Renderer *renderTarget,SDL_Rect *cameraRect, World *world);
	~MapDrawer();
	virtual void draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	virtual void accept( UpdateVisitor *uv, float deltaTime, const Uint8 *keyState );
	virtual void update( float delta, const Uint8 *keyState );
};

