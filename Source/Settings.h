#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

enum BooleanVariables { Settings_SoundOn };
enum IntegerVariables { Settings_Resolution_Width, Settings_Resolution_Height };

class Settings
{
private:
	std::vector<bool>* savedBooleans;
	std::vector<int>* savedIntegers;

	bool isInteger( const std::string & s );
	std::string generalFile;

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
	~Settings();
};

/**
This function cleans up the entire settings system. You should call it upon all exit conditions.
*/
extern __declspec(dllexport) void Settings_Quit();