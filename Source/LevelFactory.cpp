#include "LevelFactory.h"
static LevelFactory* instance;

LevelFactory::LevelFactory()
{

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

BaseLevel* LevelFactory::getLevel( Level level )
{
	return levelMap.at(level);
}

void LevelFactory::insertIntoMap( Level id, BaseLevel* level )
{
	levelMap.insert( std::pair<Level, BaseLevel*>( id, level ) );
}
