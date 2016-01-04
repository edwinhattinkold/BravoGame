#include "LevelFactory.h"
#include "LevelSnow.h"
#include "LevelDesert.h"
#include "LevelJungle.h"
static LevelFactory* instance;

LevelFactory::LevelFactory()
{
	insertIntoMap( "desert", new LevelDesert() );
	insertIntoMap( "snow", new LevelSnow() );
	insertIntoMap( "jungle", new LevelJungle() );
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
{
	typedef std::map<std::string, BaseLevel*>::iterator it_type;
	for( it_type iterator = levelMap.begin(); iterator != levelMap.end(); iterator++ )
	{
		delete iterator->second;
	}
}

BaseLevel* LevelFactory::getLevel( std::string level )
{
	return levelMap.at(level);
}

void LevelFactory::insertIntoMap( std::string name, BaseLevel* level )
{
	levelMap.insert( std::pair<std::string, BaseLevel*>( name, level ) );
}

extern __declspec(dllexport) void LevelFactory_Quit()
{
	delete instance; instance = nullptr;
}
