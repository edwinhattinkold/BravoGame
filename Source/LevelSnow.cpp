#include "LevelSnow.h"
#include "Sound.h"

LevelSnow::LevelSnow() :BaseLevel(Asset::Asset_Snow_Tileset)
{
	possibleCollectibles.push_back(Collectible::Nitro);
	possibleCollectibles.push_back(Collectible::Collect);

}


LevelSnow::~LevelSnow()
{}

void LevelSnow::startSound()
{
	std::cout << "SNOW START" << std::endl;
	Sound::getInstance()->playSound( Sound_Credits_Theme );
}

void LevelSnow::stopSound()
{
	std::cout << "SNOW STOP" << std::endl;
	Sound::getInstance()->stopSound(Sound_Credits_Theme );
}