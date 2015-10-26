#pragma once

#include <iostream>
#include <vector>
#include "SDL_Image.h"
#include "XMLReader.h"
#include "Tile.h"
#include "Location.h"
#include <Box2D/Box2D.h>
class World;

class Chunk
{
private:
	std::vector<Tile*> *tiles;
	std::vector<SDL_Texture*> *textures;
	std::vector<Location> *locations;
	std::vector<b2Body*> *bodies;
	World *world;
	b2BodyDef *collisionBodyDef;
	b2FixtureDef *collisionFixtureDef;
	b2PolygonShape *boxShape;
	SDL_Renderer *renderTarget;
public:
	void addTileSet(std::string filePath, int spacing, int firstId, int amount, int width, int height);	
	void draw(int x, int y, SDL_Rect *cameraRect);
	Chunk(SDL_Renderer *rt, std::string filePath, World *world);
	~Chunk();
	void addLocation(Location l);
	void addCollidableObject(int x, int y);

};

