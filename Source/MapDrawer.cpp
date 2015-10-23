#include "MapDrawer.h"


MapDrawer::MapDrawer(SDL_Renderer *renderTarget)
{
	chunk = new Chunk(renderTarget, "maps/level1.tmx");
}


MapDrawer::~MapDrawer()
{
	delete chunk;
}

void MapDrawer::Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect)
{
	Tile *tile = nullptr;
	SDL_Rect tarRect = { 0, 0, 32, 32 };
	for (int i = 0; i < chunk->locations->size(); i++){
		Location l = chunk->locations->at(i);
		tarRect.x = l.x * 32 - cameraRect.x;
		tarRect.y = l.y * 32 - cameraRect.y;
		tile = chunk->getTile(l.id);
		SDL_RenderCopy(renderTarget, tile->getTexture(), tile->getRect(), &tarRect);
	}
}
