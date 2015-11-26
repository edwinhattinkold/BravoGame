#include "PauseMenu.h"
#include "CustomCursor.h"
#include "SDL_ttf.h"
#include "MenuItem.h"
#include "World.h"

PauseMenu::PauseMenu(World* world, SDL_Renderer* renderTarget, Camera* camera )
{
	this->world = world;
	this->renderTarget = renderTarget;
	this->camera = camera;
	font = TTF_OpenFont( "Fonts/Frontman.ttf", 30 );
	this->arrow = new Sprite( renderTarget, Asset_Menu_Arrow );
	this->sound = Sound::getInstance();
	menuItems = new std::vector<MenuItem*>();
	menuItems->push_back( new MenuItem( renderTarget, font, "Continue" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Save game" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Mainmenu" ) );

	margin = 40;
	selected = 0;
	center();
}

PauseMenu::~PauseMenu()
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		delete menuItems->at( c );	menuItems->at( c ) = nullptr;
	}
	delete menuItems;				menuItems = nullptr;
	TTF_CloseFont( font );			font = nullptr;
	delete arrow;					arrow = nullptr;
}

void PauseMenu::tick(int mouseX, int mouseY)
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

void PauseMenu::center()
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

void PauseMenu::handleKeyboardInput( SDL_Keycode keyPressed )
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

void PauseMenu::mouseButtonClicked( int mouseX, int mouseY )
{
	for( size_t index = 0; index < menuItems->size(); index++ )
		if( mouseX >= menuItems->at( index )->getXPosition() && mouseX <= menuItems->at( index )->getXPosition() + menuItems->at( index )->getWidth() &&
			mouseY >= menuItems->at( index )->getYPosition() && mouseY <= menuItems->at( index )->getYPosition() + menuItems->at( index )->getHeight() )
		{
			sound->playSound( Sound_MainMenu_Click );
			handleChoice( index );
		}
}

void PauseMenu::updateSelected()
{
	MenuItem* selectedItem = menuItems->at( selected );
	for( size_t c = 0; c < menuItems->size(); c++ )
		menuItems->at( c )->setColor( renderTarget, Red );
	selectedItem->setColor( renderTarget, SelectedRed );

	arrow->positionRect.x = selectedItem->getXPosition() - arrow->positionRect.w - 20;
	arrow->positionRect.y = selectedItem->getYPosition() + selectedItem->getHeight() / 2 - arrow->positionRect.h / 2 - 3;
}

void PauseMenu::handleChoice( int index )
{
	switch( index )
	{
		case(Choices::Main_Menu) :
			sound->playSoundLooping( Sound_MainMenu_Theme, 0.5f );
			world->setGameState( GameState_In_MainMenu );
			break;
		case(Choices::Continue) :
			world->setGameState( GameState_Running );
	}
}