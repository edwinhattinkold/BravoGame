#include "MapDrawer.h"


MapDrawer::MapDrawer(SDL_Renderer *renderTarget)
{
	mapGenerator = new MapGenerator(renderTarget);
	locations = mapGenerator->GenerateMap("maps/level1.tmx");
}


MapDrawer::~MapDrawer()
{
	delete locations;
}

void MapDrawer::Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect)
{
	Tile *tile = nullptr;
	SDL_Rect tarRect = { 0, 0, 32, 32 };
	for (int i = 0; i < locations->size(); i++){
		Location l = locations->at(i);
		tarRect.x = l.x * 32 - cameraRect.x;
		tarRect.y = l.y * 32 - cameraRect.y;
		tile = mapGenerator->getTile(l.id);
		SDL_RenderCopy(renderTarget, tile->getTexture(), tile->getRect(), &tarRect);
	}
}
