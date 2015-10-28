#pragma once
#include <map>
#include "Chunk.h"
class ChunkFactory{
private:
	std::map<std::string, Chunk*> *chunks;
	SDL_Renderer *renderTarget;
	World *world;
public:
	ChunkFactory(SDL_Renderer *renderTarget, World *world);
	~ChunkFactory();
	Chunk* getChunk(std::string name);
};