#include "Chunk.h"


Chunk::Chunk(MapGenerator *mapGenerator, std::string level)
{
	locations = mapGenerator->GenerateMap(level);
}


Chunk::~Chunk()
{
}
