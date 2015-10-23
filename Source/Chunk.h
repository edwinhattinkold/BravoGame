#pragma once

#include <iostream>
#include <vector>;
#include "SDL_Image.h";
#include "XMLReader.h";
#include "Tile.h";
#include "Location.h";
class Chunk
{
private:
	std::vector<Tile*> tiles;
	std::vector<SDL_Texture*> textures;
	
	SDL_Renderer *renderTarget;
public:
	void AddTileSet(std::string filePath, int spacing, int firstId, int amount, int width, int height);	
	Tile* getTile(int id);
	Chunk(SDL_Renderer *rt, std::string filePath);
	~Chunk();
	std::vector<Location> *locations;
};

