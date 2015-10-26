#include "MapDrawer.h"

MapDrawer::MapDrawer(SDL_Renderer *renderTarget, World *world)
{
	int rowCount = 3;
	int colCount = 3;
	XMLReader xmlReader;
	this->world = world;
	chunks = new std::vector<std::vector<Chunk*>*>();
	for (int y = 0; y < rowCount; ++y)
	{
		chunks->push_back(new std::vector<Chunk*>());
		for (int x = 0; x < colCount; x++)
			chunks->at(y)->push_back(new Chunk(renderTarget, "maps/" + xmlReader.getChunk(x, y),world));
	}
}


MapDrawer::~MapDrawer()
{
	for( size_t y = 0; y < chunks->size(); y++ )
	{
		for( size_t x = 0; x < chunks->at( y )->size(); x++ )
		{
			delete chunks->at( y )->at( x );
			chunks->at( y )->at( x ) = nullptr;
		}
		delete chunks->at( y );
		chunks->at( y ) = nullptr;
	}
	delete chunks;
	chunks = nullptr;

}

void MapDrawer::draw( SDL_Renderer *renderTarget, SDL_Rect cameraRect )
{
	int rowCount = 3;
	int colCount = 3;
	for( int y = 0; y < rowCount; y++ )
	{
		for( int x = 0; x < colCount; x++ )
		{
			chunks->at( y )->at( x )->draw( y * 1024, x * 1024, &cameraRect );
		}
	}
}

