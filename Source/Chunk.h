#pragma once

#include <iostream>
#include <vector>
#include "SDL_Image.h"
#include "XMLReader.h"
#include "Tile.h"
#include "Location.h"
#include <Box2D/Box2D.h>
class Chunk
{
private:
	std::vector<Tile*> *tiles;
	std::vector<SDL_Texture*> *textures;
	std::vector<Location> *locations;
	std::vector<b2Body> *bodies;
	b2BodyDef *collisionBodyDef;
	b2FixtureDef *collisionFixtureDef;
	b2PolygonShape *boxShape;
	SDL_Renderer *renderTarget;
public:
	void AddTileSet(std::string filePath, int spacing, int firstId, int amount, int width, int height);	
	void Draw(int x, int y, SDL_Rect *cameraRect);
	Chunk(SDL_Renderer *rt, std::string filePath);
	~Chunk();
	void AddLocation(Location l);
	void AddCollidableObject(int x, int y);

};

