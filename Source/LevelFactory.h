#pragma once
#include <map>

class BaseLevel;

enum Level {
	Level_Desert,
	Level_Snow,
	Level_Jungle
};

class LevelFactory
{
private:
	std::map<Level, BaseLevel*> levelMap;
	void insertIntoMap( Level, BaseLevel* );
public:
	LevelFactory();
	~LevelFactory();
	static LevelFactory* getInstance();
	BaseLevel* getLevel(Level);
};

