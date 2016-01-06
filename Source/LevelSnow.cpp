#include "LevelSnow.h"
#include "Sound.h"

LevelSnow::LevelSnow() :BaseLevel(Asset::Asset_Snow_Tileset,"Tundra")
{
	
	possibleCollide.push_back(CollideObject::Ice_Tree);
	possibleCollide.push_back(CollideObject::Ice_Tent);
	

}


LevelSnow::~LevelSnow()
{
}

void LevelSnow::startSound()
{
	Sound::getInstance()->playSoundLooping( Sound_Level_Snow );
}

void LevelSnow::stopSound()
{
	Sound::getInstance()->stopSound( Sound_Level_Snow );
}
