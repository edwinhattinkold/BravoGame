#pragma once

#include <vector>;
#include "Tile.h";
#include "Location.h";
#include "SDL_image.h"
#include <string>;
#include "MapGenerator.h";

class Chunk
{
private:
	std::vector<Tile*> tiles;
	std::vector<SDL_Texture*> textures;
	std::vector<Location> *locations;
public:
	Chunk(MapGenerator *mapGenerator, std::string level);
	~Chunk();
};

