#include "SaveMenu.h"
#include "CustomCursor.h"
#include "SDL_ttf.h"
#include "MenuItem.h"
#include "World.h"

SaveMenu::SaveMenu( World* world, SDL_Renderer* renderTarget, Camera* camera, TTF_Font* font)
{
	this->world = world;
	this->renderTarget = renderTarget;
	this->camera = camera;
	this->font = font;
	this->arrow = new Sprite( renderTarget, Asset_Menu_Arrow );
	this->sound = Sound::getInstance();
	saving = false;
	menuItems = new std::vector<MenuItem*>();
	menuItems->push_back( new MenuItem( renderTarget, font, "Game One" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Game Two" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Game Three" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Back" ) );

	margin = 40;
	selected = 0;
	center();

	fileNames.push_back( "SavedGames/saveGame1.txt" );
	fileNames.push_back( "SavedGames/saveGame2.txt" );
	fileNames.push_back( "SavedGames/saveGame3.txt" );
}

SaveMenu::~SaveMenu()
{
	for( size_t c = 0; c < menuItems->size(); c++ )
		delete menuItems->at( c );
	delete menuItems;
}

void SaveMenu::tick( int mouseX, int mouseY )
{
	for( size_t i = 0; i < menuItems->size(); i++ )
		if( i != selected && menuItems->at( i )->checkHover( mouseX, mouseY ) )
		{
			sound->playSound( Sound_MainMenu_Tick );
			selected = i;
			updateSelected();
		}

	/* Draw menu items */
	for( size_t c = 0; c < menuItems->size(); c++ )
		menuItems->at( c )->draw( renderTarget );

	/* Draw arrow */
	arrow->draw( renderTarget );

	/* Draw cursor */
	CustomCursor::getInstance()->draw( mouseX, mouseY );
}

void SaveMenu::center()
{
	combinedHeight = 0;
	for( std::vector<int>::size_type i = menuItems->size() - 1; i != (std::vector<int>::size_type) - 1; i-- )
	{
		combinedHeight += menuItems->at( i )->getHeight();
		int xPosition = (camera->getCamera()->w / 2) - (menuItems->at( i )->getWidth() / 2);
		menuItems->at( i )->setXPosition( xPosition );
	}

	int marginHeight = ((menuItems->size() - 1) * margin);
	combinedHeight += marginHeight;

	for( std::vector<int>::size_type j = menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j-- )
	{
		int previousHeight = 0;
		for( size_t h = 0; h < j; h++ )
			previousHeight += menuItems->at( h )->getHeight();
		int yPosition = (camera->getCamera()->h / 2) - (combinedHeight / 2) + (j * margin) + previousHeight;
		menuItems->at( j )->setYPosition( yPosition );
	}
	updateSelected();
}

void SaveMenu::updateSelected()
{
	MenuItem* selectedItem = menuItems->at( selected );
	for( size_t c = 0; c < menuItems->size(); c++ )
		menuItems->at( c )->setColor( renderTarget, Red );
	selectedItem->setColor( renderTarget, SelectedRed );

	arrow->positionRect.x = selectedItem->getXPosition() - arrow->positionRect.w - 20;
	arrow->positionRect.y = selectedItem->getYPosition() + selectedItem->getHeight() / 2 - arrow->positionRect.h / 2 - 3;
}

void SaveMenu::handleKeyboardInput( SDL_Keycode keyPressed )
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
		case(SDLK_RETURN) :
			handleChoice( selected );
			break;
	}
	updateSelected();
}

void SaveMenu::mouseButtonClicked( int mouseX, int mouseY )
{
	for( size_t index = 0; index < menuItems->size(); index++ )
		if( mouseX >= menuItems->at( index )->getXPosition() && mouseX <= menuItems->at( index )->getXPosition() + menuItems->at( index )->getWidth() &&
			mouseY >= menuItems->at( index )->getYPosition() && mouseY <= menuItems->at( index )->getYPosition() + menuItems->at( index )->getHeight() )
		{
			sound->playSound( Sound_MainMenu_Click );
			handleChoice( index );
		}
}

void SaveMenu::handleChoice( int index )
{
	int gameNumber = 4;
	switch( index )
	{
		case(Choices::Game1) :
			gameNumber = 0;
			saving = false;
			break;
		case(Choices::Game2) :
			gameNumber = 1;
			saving = false;
			break;
		case(Choices::Game3) :
			gameNumber = 2;
			saving = false;
			break;
		case(Choices::Back) :
			saving = false;
			break;
	}
	if( gameNumber != 4 )
	{
		TDCar* car = world->getCar();
		ofstream outfile{ fileNames.at( gameNumber ) };
		outfile << (*car);
	}
}