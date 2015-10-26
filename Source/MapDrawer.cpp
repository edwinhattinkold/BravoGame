#include "MapDrawer.h"


MapDrawer::MapDrawer(SDL_Renderer *renderTarget)
{
	int rowCount = 3;
	int colCount = 3;
	this->chunks = new std::vector<std::vector<Chunk*>*>();
	for (int i = 0; i < rowCount; ++i)
	{
		chunks->push_back(new std::vector<Chunk*>());
		for (int x = 0; x < colCount; x++)
			chunks->at(i)->push_back(new Chunk(renderTarget, "maps/level1.tmx"));
	}
	//chunk = new Chunk(renderTarget, "maps/level1.tmx");
}


MapDrawer::~MapDrawer()
{
	//delete chunk;
}

void MapDrawer::Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
			chunks->at(y)->at(x)->Draw(y * 1024, x * 1024, &cameraRect);
	}
	/*Tile *tile = nullptr;
	SDL_Rect tarRect = { 0, 0, 32, 32 };
	for (int i = 0; i < chunk->locations->size(); i++){
		Location l = chunk->locations->at(i);
		tarRect.x = l.x * 32 - cameraRect.x;
		tarRect.y = l.y * 32 - cameraRect.y;
		tile = chunk->getTile(l.id);
		SDL_RenderCopy(renderTarget, tile->getTexture(), tile->getRect(), &tarRect);
	}*/
}
