#pragma once

#include <iostream>
#include <vector>;
#include "SDL_Image.h";
#include "XMLReader.h";
#include "Tile.h";
#include "Location.h";
class MapGenerator
{
private:
	std::vector<Tile*> tiles;
	std::vector<SDL_Texture*> textures;
	SDL_Renderer *renderTarget;
public:
	void AddTileSet(std::string filePath, int spacing, int firstId, int amount, int width, int height);
	std::vector<Location>* GenerateMap(std::string filePath);
	void AddTile(int x, int y, int id);
	Tile* getTile(int id);
	MapGenerator(SDL_Renderer *rt);
	~MapGenerator();
};

