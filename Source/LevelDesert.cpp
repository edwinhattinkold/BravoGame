#include "LevelDesert.h"

LevelDesert::LevelDesert()
	: BaseLevel(Asset::Asset_Desert_Tileset)
{
	



	possibleCollide.push_back(CollideObject::Desert_Piramid);
	possibleCollide.push_back(CollideObject::Desert_Tree);
}


LevelDesert::~LevelDesert()
{

}
