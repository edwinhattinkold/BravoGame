#pragma once
#include <map>
#include <string>

class BaseLevel;

class LevelFactory
{
private:
	std::map<std::string, BaseLevel*> levelMap;
	void insertIntoMap( std::string, BaseLevel* );
public:
	LevelFactory();
	~LevelFactory();
	static LevelFactory* getInstance();
	BaseLevel* getLevel(std::string name);
};

extern __declspec(dllexport) void LevelFactory_Quit();
