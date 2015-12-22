#include "HighscoreMenu.h"


HighscoreMenu::HighscoreMenu( World* world, SDL_Renderer *renderTarget, Camera* camera)
{
	saveFile = "Settings/highscores.sav";
	this->world = world;
	this->renderTarget = renderTarget;
	this->camera = camera;
	font = TTF_OpenFont( "Fonts/bloodlust.ttf", 60 );
	bigFont = TTF_OpenFont( "Fonts/Frontman.ttf", 80 );
	this->sound = Sound::getInstance();
	menuItems = new vector<MenuItem*>();
	highscores = new vector<pair<string, string>>();
	backButton = new MenuItem(renderTarget, font, "Back" );
	title = new MenuItem( renderTarget, bigFont, "High Scores" );
	isSelected = false;
	margin = 40;
	selected = 0;

	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	this->backgroundImage = Assets::getInstance()->getAsset( Asset_MainMenu_Background );
	center();
}


HighscoreMenu::~HighscoreMenu()
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		delete menuItems->at( c );	menuItems->at( c ) = nullptr;
	}
	delete menuItems;				menuItems = nullptr;
	delete backButton;				backButton = nullptr;
	delete highscores;				highscores = nullptr;
	delete title;					title = nullptr;
	TTF_CloseFont( font );			font = nullptr;
	TTF_CloseFont( bigFont );		bigFont = nullptr;
}


void HighscoreMenu::tick( int mouseX, int mouseY )
{
	/* Draw background image */
	SDL_RenderCopy( renderTarget, backgroundImage, NULL, &backgroundImageRect );

	
	if( !isSelected && backButton->checkHover( mouseX, mouseY ) )
	{
		sound->playSound( Sound_MainMenu_Tick );
		isSelected = true;
	} else if( !backButton->checkHover( mouseX, mouseY ) )
	{
		isSelected = false;
	}

	/* Draw menu items */
	for( size_t c = 0; c < menuItems->size(); c++ )
		menuItems->at( c )->draw( renderTarget );

	backButton->setXPosition( 40 );
	backButton->setYPosition( camera->getCamera()->h - 100 );
	backButton->draw( renderTarget );

	//title->setXPosition( ( camera->getCamera()->h / 2 ) - ( title->getWidth() / 5 ) );
	title->setYPosition( 100 );
	title->draw( renderTarget );

	/* Draw cursor */
	CustomCursor::getInstance()->draw( mouseX, mouseY );
}


void HighscoreMenu::loadHighScores(bool newScore)
{
	ifstream myfile( saveFile );
	if( myfile.is_open() )
	{
		string line;

		//clean up last highscore
		for( size_t c = 0; c < menuItems->size(); c++ )
		{
			delete menuItems->at( c );	menuItems->at( c ) = nullptr;
		}
		menuItems->clear();
		highscores->clear();

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
		
		if( newScore )
		{
			int score = world->getCar()->getScore();
			if( highscores->size() < 5 )
			{
				highscores->push_back( pair<string, string>( getNow(), to_string( score ) ) );
			} else
			{
				for( vector<pair<string, string>>::iterator it = highscores->begin(); it != highscores->end(); ++it )
				{
					if( stoi( it->second ) < score )
					{
						highscores->push_back( pair<string, string>( getNow(), to_string( score ) ) );
						break;
					}
				}
			}
		}

		sort( highscores->begin(), highscores->end(), &HighscoreMenu::sortScores );
		while( highscores->size() > 5 )
		{
			highscores->pop_back();
		}
		saveScores();
		createMenuItems();
	} else
	{
		cout << "Could not load highscores\n";
	}


}

void HighscoreMenu::saveScores()
{
	ofstream myfile;

	myfile.open( saveFile );
	if( myfile.is_open() )
	{
		string s = "";
		for( vector<pair<string, string>>::iterator it = highscores->begin(); it != highscores->end(); ++it )
		{
			s += it->first + " " + it->second + "\n";
		}
		myfile << s;
		myfile.close();
	}
}

void HighscoreMenu::createMenuItems()
{
	for( vector<pair<string, string>>::iterator it = highscores->begin(); it != highscores->end(); ++it )
	{
		string s = it->first + " " + it->second;
		char *text = (char*) s.c_str();
		menuItems->push_back( new MenuItem( renderTarget, font, text ) );
	}
}

bool HighscoreMenu::sortScores( pair<string, string> score1, pair<string, string> score2 )
{
	int a = stoi( score1.second );
	int b = stoi( score2.second );

	return a > b;
}


void HighscoreMenu::handleKeyboardInput( SDL_Keycode keyPressed )
{
	switch( keyPressed )
	{
		case( SDLK_ESCAPE ) :
		case( SDLK_RETURN ) :
			handleChoice( 0 );
			break;
	}
}

void HighscoreMenu::firstTick(bool newHighscore)
{
	loadHighScores(newHighscore);
	backgroundImageRect.w = camera->getCamera()->w;
	backgroundImageRect.h = camera->getCamera()->h;
	center();
}

void HighscoreMenu::center()
{
	combinedHeight = -200;
	int xPosition = ( camera->getCamera()->w / 2 ) - ( title->getWidth()/2 );
	title->setXPosition( xPosition );
	
	for( std::vector<int>::size_type i = menuItems->size() - 1; i != ( std::vector<int>::size_type ) - 1; i-- )
	{
		combinedHeight += menuItems->at( i )->getHeight();
		int xPosition = ( camera->getCamera()->w / 2 ) - ( menuItems->at( i )->getWidth() / 2 );
		menuItems->at( i )->setXPosition( xPosition );
	}

	

	int marginHeight = ( ( menuItems->size() - 1 ) * 40 );
	combinedHeight += marginHeight;

	for( std::vector<int>::size_type j = menuItems->size() - 1; j != ( std::vector<int>::size_type ) - 1; j-- )
	{
		int previousHeight = 0;
		for( size_t h = 0; h < j; h++ )
			previousHeight += menuItems->at( h )->getHeight();
		int yPosition = ( camera->getCamera()->h / 2 ) - ( combinedHeight / 2 ) + ( j * 40 ) + previousHeight;
		menuItems->at( j )->setYPosition( yPosition );
	}
}

void HighscoreMenu::mouseButtonClicked( int mouseX, int mouseY )
{
	if( mouseX >= backButton->getXPosition() && mouseX <= backButton->getXPosition() + backButton->getWidth() &&
		mouseY >= backButton->getYPosition() && mouseY <= backButton->getYPosition() + backButton->getHeight() )
	{
		sound->playSound( Sound_MainMenu_Click );
		handleChoice( 0 );
	}
}

void HighscoreMenu::handleChoice( int index )
{
	sound->playSoundLooping( Sound_MainMenu_Theme, 0.5f );
	world->setGameState( GameState_In_MainMenu );
}

string HighscoreMenu::getNow()
{
	time_t t = time( 0 );   // get time now
	struct tm * now = localtime( &t );
	string s = to_string( now->tm_year + 1900 ) + '/' +
	to_string( now->tm_mon + 1 ) + '/' + to_string(now->tm_mday) + "-" + 
	to_string( now->tm_hour ) + ":" + to_string( now->tm_min ) + ":" + to_string( now->tm_sec );

	return s;
}