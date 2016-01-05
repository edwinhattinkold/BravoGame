#include "LevelJungle.h"
#include "Sound.h"

LevelJungle::LevelJungle() : BaseLevel( Asset::Asset_Jungle_Tileset,"Jungle" )
{
	possibleCollectibles.push_back( Collectible::Gasoline );
	possibleCollectibles.push_back( Collectible::Collect );
}


LevelJungle::~LevelJungle()
{}

void LevelJungle::startSound()
{
	Sound::getInstance()->playSoundLooping( Sound_Level_Jungle );
}

void LevelJungle::stopSound()
{
	Sound::getInstance()->stopSound( Sound_Level_Jungle );
}