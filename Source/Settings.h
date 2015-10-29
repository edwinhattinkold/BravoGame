#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

enum BooleanVariables { Settings_fullscreen, Settings_SoundOn };
enum IntegerVariables { Settings_Windowed_Width, Settings_Windowed_Height };

using namespace std;

class Settings
{
private:
	vector<bool>* savedBooleans;
	vector<int>* savedIntegers;

	map<BooleanVariables, pair<string, int>>* booleanConnections;
	map<IntegerVariables, pair<string, int>>* integerConnections;

	bool isInteger( const string & s );
	string generalFile;

	/* Singleton */
	Settings();
	Settings( Settings const& );
	void operator=(Settings const&);
public:
	/* Singleton */
	static Settings* getInstance();

	bool getBoolean( BooleanVariables variable );
	int getInteger( IntegerVariables variable );
	void setBoolean( BooleanVariables variable, bool newVariable );
	void setInteger( IntegerVariables variable, int newVariable );
	vector<string>* getFile(string filepath);
	void setFile( string filepath, vector<string>* newFile );
	~Settings();
};

/**
This function cleans up the entire settings system. You should call it upon all exit conditions.
*/
extern __declspec(dllexport) void Settings_Quit();