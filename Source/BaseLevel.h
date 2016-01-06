#pragma once
#include "Tile.h"
#include "Collectible.h"
#include "CollideObject.h"
#include <vector>
#include <string>
#include "Assets.h"
class BaseLevel
{
private:
	Asset textureId;
	int spacing = 0;
	int firstId = 1;
	int amount = 48;
	int width = 263;
	int height = 197;
	void addTileSet();
	string name;
public:
	std::vector<Tile*> *tiles;
	std::vector<Collectible::Collectibletypes> possibleCollectibles;
	std::vector<CollideObject::CollideType> possibleCollide;
	BaseLevel(Asset assetId,string name);
	Collectible::Collectibletypes getTypeCollectible();
	void virtual stopSound();
	void virtual startSound();
	string getName();
	~BaseLevel();	
};

