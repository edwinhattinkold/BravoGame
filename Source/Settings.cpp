#include "Settings.h"

static Settings* instance;

Settings::Settings()
{
	savedBooleans = new std::vector<bool>();
	savedIntegers = new std::vector<int>();

	generalFile = "Settings/general.ini";

	std::string line;
	std::ifstream myfile( generalFile );
	if( myfile.is_open() )
	{
		while( getline( myfile, line ) )
		{
			std::string delimiter = " ";

			size_t pos = 0;
			std::string token;
			while( (pos = line.find( delimiter )) != std::string::npos )
			{
				token = line.substr( 0, pos );
				line.erase( 0, pos + delimiter.length() );
			}
			if( isInteger( line ) )
				savedIntegers->push_back( std::stoi( line ) );
			if( line == "true" || line == "false" )
				savedBooleans->push_back(line == "true");
		}
		myfile.close();
	}
	else 
		std::cout << "Unable to open settings file!";
}

Settings::~Settings()
{
	delete savedBooleans;		savedBooleans = nullptr;
	delete savedIntegers;		savedIntegers = nullptr;
}

Settings* Settings::getInstance()
{
	if( !instance )
		instance = new Settings();
	return instance;
}

bool Settings::isInteger( const std::string & s )
{
	if( s.empty() || ((!isdigit( s[0] )) && (s[0] != '-') && (s[0] != '+')) ) return false;
	char * p;
	strtol( s.c_str(), &p, 10 );
	return (*p == 0);
}

bool Settings::getBoolean( BooleanVariables variable )
{
	return savedBooleans->at( variable );
}

int Settings::getInteger( IntegerVariables variable )
{
	return savedIntegers->at( variable );
}

void Settings::setBoolean( BooleanVariables variable, bool newVariable )
{
	std::ofstream myFile( generalFile, std::ofstream::binary );
	myFile << "TrueVanafWrite";
}

void Settings::setInteger( IntegerVariables variable, int newVariable )
{

}

extern __declspec(dllexport) void Settings_Quit()
{
	delete instance; instance = nullptr;
}