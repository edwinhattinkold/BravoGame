#include "LevelSnow.h"


LevelSnow::LevelSnow() :BaseLevel(Asset::Asset_Snow_Tileset)
{
	
	possibleCollide.push_back(CollideObject::Ice_Tree);
	possibleCollide.push_back(CollideObject::Ice_Tent);
	

}


LevelSnow::~LevelSnow()
{}
