#include "ChunkFactory.h"

ChunkFactory::ChunkFactory(SDL_Renderer *renderTarget, World *world)
{
	this->renderTarget = renderTarget;
	this->world = world;
	chunks = new std::map<std::string, Chunk*>();

}

ChunkFactory::~ChunkFactory()
{
	typedef std::map<std::string, Chunk*>::iterator it_type;
	for (it_type iterator = chunks->begin(); iterator != chunks->end(); iterator++) {
		delete iterator->second;
		iterator->second = nullptr;
	}
	delete chunks;
}
Chunk* ChunkFactory::getChunk(std::string name)
{
	std::map<std::string, Chunk*>::iterator it = chunks->find(name);
	if (it != chunks->end())
		return it->second;
	std::pair<std::string, Chunk*> pair;
	pair.first = name;
	pair.second = new Chunk(renderTarget, "maps/" + name, world);
	chunks->insert(pair);
	return pair.second;
}