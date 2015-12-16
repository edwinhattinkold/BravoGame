#include "LevelFactory.h"
#include "LevelSnow.h"
#include "LevelDesert.h"
static LevelFactory* instance;

LevelFactory::LevelFactory()
{
	insertIntoMap( "desert", new LevelDesert() );
	insertIntoMap( "snow", new LevelSnow() );
}

LevelFactory* LevelFactory::getInstance()
{
	if( !instance )
	{
		instance = new LevelFactory();
	}
	return instance;
}

LevelFactory::~LevelFactory()
{}

BaseLevel* LevelFactory::getLevel( std::string level )
{
	return levelMap.at(level);
}

void LevelFactory::insertIntoMap( std::string name, BaseLevel* level )
{
	levelMap.insert( std::pair<std::string, BaseLevel*>( name, level ) );
}
