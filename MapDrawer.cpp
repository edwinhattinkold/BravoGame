#include "MapDrawer.h"


MapDrawer::MapDrawer(SDL_Renderer *renderTarget)
{
	MapGenerator mg{ renderTarget };
	locations = mg.GenerateMap("maps/level1.tmx");
	Tile *tile = nullptr;
	SDL_Rect tarRect = { 0, 0, 32, 32 };

	for (int i = 0; i < locations->size(); i++){
		Location l = locations->at(i);
		tarRect.x = l.x * 32;
		tarRect.y = l.y * 32;
		tile = mg.getTile(l.id);
		SDL_RenderCopy(renderTarget, tile->getTexture(), tile->getRect(), &tarRect);
	}

	SDL_RenderPresent(renderTarget);
	delete locations;
}


MapDrawer::~MapDrawer()
{
}
