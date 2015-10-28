#include "MapDrawer.h"
#include "world.h"
MapDrawer::MapDrawer( SDL_Renderer *renderTarget, SDL_Rect *cameraRect, World *world )
{
	this->cameraRect = cameraRect;
	this->renderTarget = renderTarget;
	//this->chunkFactory = new ChunkFactory(renderTarget, world);
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
			chunks->at( yCount )->push_back( new Chunk( renderTarget, "maps/" + getChunk( x, y ), world ) );
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
			chunks->at(y)->at(x)->draw((minX + x) * 1024, (minY+ y) * 1024, &cameraRect);
		}
	}
}

void MapDrawer::accept( UpdateVisitor *uv, float deltaTime, const Uint8 *keyState )
{
	if ( minX * 1024 > cameraRect->x)
		loadChunkLeft();
	if (minY * 1024 > cameraRect->y)
		loadChunkTop();
	if (maxX * 1024 < cameraRect->x + cameraRect->w)
		loadChunkRight();
	if (maxY * 1024 < cameraRect->y + cameraRect->h)
		loadChunkBottom();
}
void MapDrawer::update( float delta, const Uint8 *keyState )
{

}

std::string MapDrawer::getChunk(int x, int y)
{
	XMLReader xmlReader;
	std::string filePath = xmlReader.getChunk(x,y);
	if( filePath.empty())
	{
		filePath = "cleanlevel.tmx";
	}
	return filePath;
}

void MapDrawer::loadChunkLeft()
{
	std::vector<Chunk*> preLoad;
	preLoad.push_back(new Chunk(renderTarget, "maps/" + getChunk(minX - 1, minY), world));
	preLoad.push_back(new Chunk(renderTarget, "maps/" + getChunk(minX - 1, minY+1), world));
	preLoad.push_back(new Chunk(renderTarget, "maps/" + getChunk(minX - 1, minY +2), world));
	for (size_t y = 0; y < chunks->size(); y++)
	{
		int xCount = chunks->at(y)->size() - 1;
		//delete most right element
		delete chunks->at(y)->at(xCount);
		//move all to right
		for (int x = xCount; x > 0; x--)
		{
			chunks->at(y)->at(x) = chunks->at(y)->at(x - 1);
		}
		//create new chunk at left
		chunks->at(y)->at(0) = preLoad.at(y);
	}
	minX--;
	maxX--;
}

void MapDrawer::loadChunkRight()
{
	XMLReader xmlReader;
	std::vector<Chunk*> preLoad;
	preLoad.push_back(new Chunk(renderTarget, "maps/" + getChunk(maxX , minY), world));
	preLoad.push_back(new Chunk(renderTarget, "maps/" + getChunk(maxX , minY + 1), world));
	preLoad.push_back(new Chunk(renderTarget, "maps/" + getChunk(maxX , minY + 2), world));
	for (size_t y = 0; y < chunks->size(); y++)
	{
		//delete most left element
		delete chunks->at(y)->at(0);
		//move all to left
		size_t x;
		for (x = 0; x < chunks->at(y)->size()-1; x++)
		{
			chunks->at(y)->at(x) = chunks->at(y)->at(x + 1);
		}
		//create new chunk at right
		chunks->at(y)->at(x) = preLoad.at(y);
	}
	minX++;
	maxX++;
}

void MapDrawer::loadChunkBottom(){
	XMLReader xmlReader;
	std::vector<Chunk*> *preLoad = new std::vector<Chunk*>();
	preLoad->push_back(new Chunk(renderTarget, "maps/" + getChunk(minX, maxY), world));
	preLoad->push_back(new Chunk(renderTarget, "maps/" + getChunk(minX + 1, maxY), world));
	preLoad->push_back(new Chunk(renderTarget, "maps/" + getChunk(minX + 2, maxY), world));
	//delete first row
	for (size_t x = 0; x < chunks->at(0)->size() ; x++){
		delete chunks->at(0)->at(x);
	}
	delete chunks->at(0);
	size_t y;
	for (y = 0; y < chunks->size() -1; y++)
	{
		//move chunk up
		chunks->at(y) = chunks->at(y + 1);
	}
	//add chunk row to bottom
	chunks->at(y) = preLoad;
	minY++;
	maxY++;
}

void MapDrawer::loadChunkTop()
{
	XMLReader xmlReader;
	std::vector<Chunk*> *preLoad = new std::vector<Chunk*>();
	preLoad->push_back(new Chunk(renderTarget, "maps/" + getChunk(minX, minY -1), world));
	preLoad->push_back(new Chunk(renderTarget, "maps/" + getChunk(minX + 1, minY - 1), world));
	preLoad->push_back(new Chunk(renderTarget, "maps/" + getChunk(minX + 2, minY - 1), world));
	//delete first row
	size_t size = chunks->size() - 1;
	for (size_t x = 0; x < chunks->at(size)->size(); x++){
		delete chunks->at(size)->at(x);
	}
	delete chunks->at(size);
	int y;
	for (y = size; y > 0; y--)
	{
		//move chunk up
		chunks->at(y) = chunks->at(y - 1);
	}
	//add chunk row to bottom
	chunks->at(y) = preLoad;
	minY--;
	maxY--;
}