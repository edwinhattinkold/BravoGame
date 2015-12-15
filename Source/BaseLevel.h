#pragma once
#include "Tile.h"
#include <vector>
#include <string>
#include "Assets.h"
class BaseLevel
{
private:
	Asset textureId;
	int spacing;
	int firstId;
	int amount;
	int width;
	int height;
public:
	std::vector<Tile*> *tiles;
	BaseLevel(Asset assetId);
	~BaseLevel();
	void addTileSet( int spacing, int firstId, int amount, int width, int height );	
};

