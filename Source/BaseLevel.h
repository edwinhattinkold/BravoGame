#pragma once
#include "Tile.h"
#include "Collectible.h"
#include <vector>
#include <string>
#include "Assets.h"
class BaseLevel
{
private:
	Asset textureId;
	int spacing = 1;
	int firstId = 1;
	int amount = 48;
	int width = 263;
	int height = 197;
	void addTileSet();
public:
	std::vector<Tile*> *tiles;
	std::vector<Collectible::Collectibletypes> possibleCollectibles;
	BaseLevel(Asset assetId);
	Collectible::Collectibletypes getTypeCollectible();
	~BaseLevel();	
};

