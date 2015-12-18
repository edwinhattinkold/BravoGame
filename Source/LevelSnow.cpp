#include "LevelSnow.h"


LevelSnow::LevelSnow() :BaseLevel(Asset::Asset_Snow_Tileset)
{
	possibleCollectibles.push_back(Collectible::Nitro);
	possibleCollectibles.push_back(Collectible::Collect);

}


LevelSnow::~LevelSnow()
{}
