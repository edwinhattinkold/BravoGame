#include "LevelDesert.h"

LevelDesert::LevelDesert()
	: BaseLevel(Asset::Asset_Desert_Tileset)
{
	possibleCollectibles.push_back(Collectible::Gasoline);
	possibleCollectibles.push_back(Collectible::Collect);
}


LevelDesert::~LevelDesert()
{

}
