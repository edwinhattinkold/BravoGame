#include "MapDrawer.h"

MapDrawer::MapDrawer( SDL_Renderer *renderTarget, SDL_Rect *cameraRect, World *world )
{
	this->cameraRect = cameraRect;
	minX = 0;
	maxX = 3;
	minY = 0;
	maxY = 3;
	int rowCount = 3;
	int colCount = 3;
	XMLReader xmlReader;
	this->world = world;
	chunks = new std::vector<std::vector<Chunk*>*>();
	int yCount = 0;
	for( int y = minY; y < maxY; ++y )
	{
		chunks->push_back( new std::vector<Chunk*>() );
		for( int x = minX; x < maxX; x++ )
			chunks->at( yCount )->push_back( new Chunk( renderTarget, "maps/" + xmlReader.getChunk( x, y ), world ) );
		yCount++;
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

void MapDrawer::accept( UpdateVisitor *uv, float deltaTime, const Uint8 *keyState )
{
	if( minX * 1024 + 300 > cameraRect->x )
		std::cout << "loadLeft" << std::endl;
	if( minY * 1024 + 300 > cameraRect->y )
		std::cout << "loadTop" << std::endl;
	if( maxX * 1024 - 300 < cameraRect->x + cameraRect->w )
		std::cout << "loadRight" << std::endl;
	if( minY * 1024 - 300 < cameraRect->x + cameraRect->h)
		std::cout << "loadBottom" << std::endl;
}
void MapDrawer::update( float delta, const Uint8 *keyState )
{

}

