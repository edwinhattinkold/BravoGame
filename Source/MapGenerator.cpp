#include "MapGenerator.h"

SDL_Texture* LoadImage(SDL_Renderer *renderTarget, std::string filePath){
	filePath = filePath.substr(3);
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error1" << filePath << std::endl;
	else {
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error2" << std::endl;
		SDL_FreeSurface(surface);
		return texture;
	}
}

MapGenerator::MapGenerator(SDL_Renderer *rt)
{
	renderTarget = rt;
	tiles.push_back(nullptr);
}

MapGenerator::~MapGenerator()
{
	for (int i = 1; i < tiles.size(); i++){
		delete tiles.at(i);
	}
}

std::vector<Location>* MapGenerator::GenerateMap(std::string filePath)
{
	XMLReader reader;
	return reader.parseXMLFile(this, filePath);
}

void MapGenerator::AddTileSet(std::string filePath, int spacing, int firstId, int amount, int width, int height)
{
	
	SDL_Texture  *texture = LoadImage(renderTarget, filePath);
	//save pointer for removing
	textures.push_back(texture);
	int x = 0;
	int y = 0;
	for (int c = 0; c < amount; c++){
		SDL_Rect cropRect;
		cropRect.h = 32;
		cropRect.w = 32;
		cropRect.x = x;
		cropRect.y = y;
		x += spacing + 32;
		
		tiles.push_back(new Tile(texture, cropRect));
		if (x + 32 > width){
			x = 0;
			y += spacing + 32;
		}
	}
}

Tile* MapGenerator::getTile(int id){
	return tiles.at(id);
}
