#include "LevelSnow.h"
#include "Sound.h"

LevelSnow::LevelSnow() :BaseLevel(Asset::Asset_Snow_Tileset,"Snow")
{
	possibleCollectibles.push_back(Collectible::Nitro);
	possibleCollectibles.push_back(Collectible::Collect);

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