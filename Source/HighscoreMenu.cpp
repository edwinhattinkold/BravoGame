#include "HighscoreMenu.h"


HighscoreMenu::HighscoreMenu( SDL_Renderer *renderTarget, Camera* camera, TTF_Font* font )
{
	//Create background
	//List highscores (name, score)
	//back button
	this->camera = camera;
	highscores = new vector<pair<string, string>>();

	background = Assets::getInstance()->getAsset( Asset_MainMenu_Background );
	backButton = new MenuItem( renderTarget, font, "Back" );
	backButton->setXPosition( camera->levelWidth - 48 );
	backButton->setYPosition( camera->levelHeight - 48 );

}


HighscoreMenu::~HighscoreMenu()
{}

void HighscoreMenu::showMenu( SDL_Renderer *renderTarget )
{
	//init the menu (that weren't fixed in the constructor
	backButton->setXPosition( camera->levelWidth - 48 );
	backButton->setYPosition( camera->levelHeight - 48 );

	//run the loop
	tick( renderTarget );
}

void HighscoreMenu::tick( SDL_Renderer *renderTarget )
{
	bool active = true;
	while( active )
	{

	}

	removeMenu();
}

void HighscoreMenu::removeMenu()
{
	//remove everything
}

void HighscoreMenu::loadHighScores()
{
	ifstream myfile( "Settings/highscores.sav" );
	if( myfile.is_open() )
	{
		string line;
		while( getline( myfile, line ) )
		{
			string delimiter = " ";

			size_t pos = 0;
			string token;
			while( ( pos = line.find( delimiter ) ) != string::npos )
			{
				token = line.substr( 0, pos );
				line.erase( 0, pos + delimiter.length() );
			}
			
			highscores->push_back( pair<string, string>( token, line ) );
		}
		//sort( highscores->begin(), highscores->end(), &HighscoreMenu::sortScores );

		//for( vector<pair<string, string>>::iterator it = highscores->begin(); it != highscores->end(); ++it )
		//{
		//	cout << it->first << " " << it->second << "\n";
		//}
	} else
	{
		cout << "Could not load highscores\n";
	}


}

bool HighscoreMenu::sortScores( pair<string, string> score1, pair<string, string> score2 )
{
	int a = stoi( score1.second );
	int b = stoi( score2.second );

	return a > b;
}