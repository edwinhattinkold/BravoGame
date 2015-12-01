#include "LoadingMenu.h"
#include "CustomCursor.h"
#include "World.h"

LoadingMenu::LoadingMenu( SDL_Renderer* renderTarget, SDL_Window* window, SDL_Texture* backgroundImage, Sprite* arrow, Camera* camera, TTF_Font* font, World* world )
{
	this->arrow = arrow;
	this->renderTarget = renderTarget;
	this->window = window;
	this->camera = camera;
	this->world = world;
	sound = Sound::getInstance();
	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = camera->getCamera()->w;
	backgroundImageRect.h = camera->getCamera()->h;
	this->backgroundImage = backgroundImage;

	margin = 40;
	combinedHeight = 0;

	menuItems = new std::vector<MenuItem*>();
	menuItems->push_back( new MenuItem( renderTarget, font, "Game One" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Game Two" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Game Three") );
	menuItems->push_back( new MenuItem( renderTarget, font, "Back" ) );

	for( std::vector<int>::size_type i = menuItems->size() - 1; i != (std::vector<int>::size_type) - 1; i-- )
	{
		combinedHeight += menuItems->at( i )->getHeight();
		int xPosition = (camera->getCamera()->w / 2) - (menuItems->at( i )->getWidth() / 2) - camera->getCamera()->x;
		menuItems->at( i )->setXPosition( xPosition );
	}

	int marginHeight = ((menuItems->size() - 1) * margin);
	combinedHeight += marginHeight;

	selected = 0;

	fileNames.push_back( "SavedGames/saveGame1.txt" );
	fileNames.push_back( "SavedGames/saveGame2.txt" );
	fileNames.push_back( "SavedGames/saveGame3.txt" );

}


LoadingMenu::~LoadingMenu()
{
	for( size_t c = 0; c < menuItems->size(); c++ )
		delete menuItems->at( c );
	delete menuItems;
}

int LoadingMenu::showMenu( SDL_Renderer* renderTarget )
{
	SDL_GetMouseState( &mouseX, &mouseY );
	CustomCursor::getInstance()->draw( mouseX, mouseY );
	center();
	int choice = createMenu( renderTarget );
	switch( choice )
	{
		case(Choices::Back) :
			return Choices::Back;
			break;
		case(Choices::Exit) :
			return Choices::Exit;
		case(Choices::Game1) :
		case(Choices::Game2) :
		case(Choices::Game3) :
			return choice;
			break;
		default:
			return Choices::Back;
			break;
	}
	return choice;
}

int LoadingMenu::getBackCode()
{
	return Choices::Back;
}

int LoadingMenu::getExitCode()
{
	return Choices::Exit;
}

bool LoadingMenu::isGameCode( int choice )
{
	if( choice == Choices::Game1 || choice == Choices::Game2 || choice == Choices::Game3 )
	{
		return true;
	}
	return false;
}

void LoadingMenu::center()
{
	for( std::vector<int>::size_type j = menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j-- )
	{
		int xPosition = (camera->getCamera()->w / 2) - (menuItems->at( j )->getWidth() / 2);
		menuItems->at( j )->setXPosition( xPosition );

		int previousHeight = 0;
		for( size_t h = 0; h < j; h++ )
			previousHeight += menuItems->at( h )->getHeight();
		int yPosition = (camera->getCamera()->h / 2) - (combinedHeight / 2) + (j * margin) + previousHeight;
		menuItems->at( j )->setYPosition( yPosition );
	}
	updateSelected();
}

int LoadingMenu::createMenu( SDL_Renderer* renderTarget )
{
	while( 1 )
	{
		time = SDL_GetTicks();
		while( SDL_PollEvent( &ev ) )
		{
			switch( ev.type )
			{
				case SDL_QUIT:
					return Choices::Exit;
				case SDL_MOUSEMOTION:
					mouseX = ev.motion.x;
					mouseY = ev.motion.y;
					for( size_t i = 0; i < menuItems->size(); i++ )
						if( i != selected && menuItems->at( i )->checkHover( mouseX, mouseY ) )
						{
							sound->playSound( Sound_MainMenu_Tick );
							selected = i;
							updateSelected();
						}
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouseX = ev.motion.x;
					mouseY = ev.motion.y;
					for( size_t index = 0; index < menuItems->size(); index++ )
						if( mouseX >= menuItems->at( index )->getXPosition() && mouseX <= menuItems->at( index )->getXPosition() + menuItems->at( index )->getWidth() &&
							mouseY >= menuItems->at( index )->getYPosition() && mouseY <= menuItems->at( index )->getYPosition() + menuItems->at( index )->getHeight() )
						{
							sound->playSound( Sound_MainMenu_Click );

							if( index == Choices::Back )
								return index;
							else if( isGameCode( index ) )
							{
								handleSelection( index );
								return index;
							}
						}
					break;
				case SDL_KEYDOWN:
					SDL_Keycode keyPressed = ev.key.keysym.sym;
					handleKeyboardInput( keyPressed );
					if( keyPressed == SDLK_RETURN || keyPressed == SDLK_SPACE )
					{
						sound->playSound( Sound_MainMenu_Click );
						if( selected == Choices::Back )
							return selected;
						else
							handleSelection( selected );
					}
					else if( keyPressed == SDLK_ESCAPE )
						return Choices::Back;
					break;
			}
		}
		SDL_RenderClear( renderTarget );
		SDL_RenderCopy( renderTarget, backgroundImage, NULL, NULL );
		drawMenuItems( renderTarget );
		arrow->draw( renderTarget );
		CustomCursor::getInstance()->draw( mouseX, mouseY );
		SDL_RenderPresent( renderTarget );
	}
}

void LoadingMenu::updateSelected()
{
	MenuItem* selectedItem = menuItems->at( selected );
	for( size_t c = 0; c < menuItems->size(); c++ )
		menuItems->at( c )->setColor( renderTarget, Red );
	menuItems->at( selected )->setColor( renderTarget, SelectedRed );
	arrow->positionRect.x = selectedItem->getXPosition() - arrow->positionRect.w - 20;
	arrow->positionRect.y = selectedItem->getYPosition() + selectedItem->getHeight() / 2 - arrow->positionRect.h / 2 - 3;
}

void LoadingMenu::handleSelection( int index )
{
	int gameNumber;
	if( index == Choices::Game1 )
	{
		gameNumber = 0;
	}
	else if(index == Choices::Game2 )
	{
		gameNumber = 1;
	}
	else if( index == Choices::Game3 )
	{
		gameNumber = 2;
	}
	TDCar* car = world->getCar();
	ifstream infile( fileNames.at( gameNumber ) );
	if( infile >> (*car) )
	{
		cout << "LOADED";
	}
}

void LoadingMenu::handleKeyboardInput( SDL_Keycode keyPressed )
{
	switch( keyPressed )
	{
		case(SDLK_w) :
		case(SDLK_UP) :
					  if( selected != 0 )
						  selected--;
					  else
						  selected = menuItems->size() - 1;
			sound->playSound( Sound_MainMenu_Tick );
			break;
		case(SDLK_s) :
		case(SDLK_DOWN) :
						if( selected != menuItems->size() - 1 )
							selected++;
						else
							selected = 0;
			sound->playSound( Sound_MainMenu_Tick );
			break;
	}
	updateSelected();
}

void LoadingMenu::drawMenuItems( SDL_Renderer* renderTarget )
{
	for( std::vector<int>::size_type j = menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j-- )
	{
		menuItems->at( j )->draw( renderTarget );
	}
}