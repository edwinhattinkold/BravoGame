#pragma once

#include <iostream>
#include <vector>
#include "Location.h"
#include "SDL.h"
#include "Chunk.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "DrawVisitor.h"
#include "ChunkFactory.h"

class MapDrawer : public IDrawable, public IUpdateable
{
private:
	std::vector<std::vector<Chunk*>*> *chunks;
	SDL_Renderer *renderTarget;
	int minX, maxX, minY, maxY;
	SDL_Rect *cameraRect;
	World *world;
	ChunkFactory *chunkFactory;
	void loadChunkTop();
	void loadChunkRight();
	void loadChunkBottom();
	void loadChunkLeft();
	MiniChunk getChunk( int x, int y );
public:
	MapDrawer(SDL_Renderer *renderTarget,SDL_Rect *cameraRect, World *world);
	~MapDrawer();
	virtual void draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	virtual void accept( UpdateVisitor *uv );
	virtual void update( float delta, const Uint8 *keyState );
};

