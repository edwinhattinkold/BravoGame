#include "Settings.h"

static Settings* instance;

Settings::Settings()
{
	savedBooleans			= new vector<bool>();
	savedIntegers			= new vector<int>();

	booleanConnections		= new map<BooleanVariables, pair<string, int>>();
	integerConnections		= new map<IntegerVariables, pair<string, int>>();

	generalFile = "Settings/general.ini";

	string line;
	int lineNumber = 0;
	int booleanCounter = 0;
	int integerCounter = 0;

	ifstream myfile( generalFile );
	if( myfile.is_open() )
	{
		while( getline( myfile, line ) )
		{
			string delimiter = " ";

			size_t pos = 0;
			string token;
			while( (pos = line.find( delimiter )) != string::npos )
			{
				token = line.substr( 0, pos );
				line.erase( 0, pos + delimiter.length() );
			}
			if( isInteger( line ) )
			{
				savedIntegers->push_back( stoi( line ) );
				IntegerVariables intVar = static_cast<IntegerVariables>(integerCounter);
				integerConnections->insert(std::pair<IntegerVariables, pair<string, int>>(intVar,  pair<string, int>( token, lineNumber ) ) );
				integerCounter++;
			}
				
			if( line == "true" || line == "false" )
			{
				savedBooleans->push_back( line == "true" );
				BooleanVariables boolVar = static_cast<BooleanVariables>(booleanCounter);
				booleanConnections->insert( std::pair<BooleanVariables, pair<string, int>>( boolVar, pair<string, int>( token, lineNumber ) ) );
				booleanCounter++;
			}
			lineNumber++;
		}
		myfile.close();
	}
	else 
		cout << "Unable to open settings file!";
}

Settings::~Settings()
{
	delete savedBooleans;		savedBooleans = nullptr;
	delete savedIntegers;		savedIntegers = nullptr;
	delete booleanConnections;	booleanConnections = nullptr;
	delete integerConnections;	integerConnections = nullptr;
}

Settings* Settings::getInstance()
{
	if( !instance )
		instance = new Settings();
	return instance;
}

bool Settings::isInteger( const string & s )
{
	if( s.empty() || ((!isdigit( s[0] )) && (s[0] != '-') && (s[0] != '+')) ) return false;
	char * p;
	strtol( s.c_str(), &p, 10 );
	return (*p == 0);
}

bool Settings::getBoolean( BooleanVariables variable )
{
	if( size_t(variable) < savedBooleans->size() )
		return savedBooleans->at( variable );
	else
		return nullptr;
}

int Settings::getInteger( IntegerVariables variable )
{
	if( size_t( variable ) < savedIntegers->size() )
		return savedIntegers->at( variable );
	else
		return -1000;
}

void Settings::setBoolean( BooleanVariables variable, bool newVariable )
{
	string newVariableStr = newVariable ? "true" : "false";
	vector<string>* fileDuplicate = getFile( generalFile );
	std::pair<string, int> info = booleanConnections->at( variable );
	if( size_t( variable ) < booleanConnections->size() )
		fileDuplicate->at( info.second ) = info.first + " " + newVariableStr;
	else
		cout << "Error while trying to set a boolean variable, changes have not been made!" << std::endl;

	setFile( generalFile, fileDuplicate );
	delete fileDuplicate;	fileDuplicate = nullptr;
}
	

void Settings::setInteger( IntegerVariables variable, int newVariable )
{
	ostringstream oss; oss << newVariable;
	vector<string>* fileDuplicate = getFile( generalFile );
	std::pair<string, int> info = integerConnections->at( variable );
	if( size_t( variable ) < integerConnections->size() )
		fileDuplicate->at( info.second ) = info.first + " " + oss.str();
	else
		cout << "Error while trying to set a integer variable, changes have not been made!" << std::endl;

	setFile( generalFile, fileDuplicate );
	delete fileDuplicate;	fileDuplicate = nullptr;
}

vector<string>* Settings::getFile( string filepath )
{
	vector<string>* fileMap = new vector<string>();
	string line;
	ifstream myfile( filepath );
	if( myfile.is_open() )
	{
		while( getline( myfile, line ) )
			fileMap->push_back( line );
		myfile.close();
	}
	else
		cout << "Unable to open settings file!";
	return fileMap;
}

void Settings::setFile( string filepath, vector<string>* newFile )
{
	ofstream myFile;  
	myFile.open( filepath );  //open file

	for( size_t x = 0; x < newFile->size(); x++ )
		myFile << newFile->at( x ) << endl;
	myFile.close();
}

extern __declspec(dllexport) void Settings_Quit()
{
	delete instance; instance = nullptr;
}