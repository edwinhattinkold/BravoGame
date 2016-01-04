#include "InGameMenu.h"
#include "CustomCursor.h"
#include "SDL_ttf.h"
#include "MenuItem.h"
#include "World.h"

InGameMenu::InGameMenu( World* world, SDL_Renderer* renderTarget, Camera* camera )
{
	this->world = world;
	this->renderTarget = renderTarget;
	this->camera = camera;
	font = TTF_OpenFont( "Fonts/Frontman.ttf", 30 );
	this->arrow = new Sprite( renderTarget, Asset_Menu_Arrow );
	this->sound = Sound::getInstance();
	menuItems = new std::vector<MenuItem*>();

	margin = 40;
	selected = 0;
	center();
}


InGameMenu::~InGameMenu()
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		delete menuItems->at( c );	menuItems->at( c ) = nullptr;
	}
	delete menuItems;				menuItems = nullptr;
	delete arrow;					arrow = nullptr;
	TTF_CloseFont( font );			font = nullptr;
}


void InGameMenu::tick( int mouseX, int mouseY )
{

}

void InGameMenu::center()
{

}

void InGameMenu::handleKeyboardInput( SDL_Keycode keyPressed )
{

}

void InGameMenu::mouseButtonClicked( int mouseX, int mouseY )
{

}

void InGameMenu::updateSelected()
{

}

void InGameMenu::handleChoice( int index )
{

}