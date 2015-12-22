#include "LevelDesert.h"
#include "Sound.h"

LevelDesert::LevelDesert()
	: BaseLevel(Asset::Asset_Desert_Tileset)
{
	possibleCollectibles.push_back(Collectible::Gasoline);
	possibleCollectibles.push_back(Collectible::Collect);
}


LevelDesert::~LevelDesert()
{
}

void LevelDesert::startSound()
{
	Sound::getInstance()->playSoundLooping( Sound_Level_Desert );
}

void LevelDesert::stopSound()
{
	Sound::getInstance()->stopSound( Sound_Level_Desert );
}