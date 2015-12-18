#pragma once

#include <iostream>
#include <vector>
#include "SDL_Image.h"
#include "XMLReader.h"
#include "Tile.h"
#include "Location.h"
#include <Box2D/Box2D.h>
#include "BaseLevel.h"
class World;
class MiniChunk
{
public:
	std::string tmx;
	std::string level;
};

class Chunk
{
private:
	BaseLevel *level;
	std::vector<Location> *locations;
	std::vector<Collectible*> collectibleItems;
	World *world;
	b2BodyDef *collisionBodyDef;
	b2FixtureDef *collisionFixtureDef;
	b2PolygonShape *boxShape;
	SDL_Renderer *renderTarget;
	int x, y;
public:
	void addTileSet();	
	void draw( SDL_Rect *cameraRect);
	Chunk(SDL_Renderer *rt,MiniChunk miniChunk, World *world, int x , int y);
	~Chunk();
	void addLocation(Location l);
	void addCollidableObject(int x, int y);
	void addCollectable();
};