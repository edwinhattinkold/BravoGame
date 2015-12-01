#include "SaveMenu.h"
#include "CustomCursor.h"
#include "SDL_ttf.h"
#include "MenuItem.h"
#include "World.h"

SaveMenu::SaveMenu( World* world, SDL_Renderer* renderTarget, Camera* camera )
{
	/*this->world = world;
	this->renderTarget = renderTarget;
	this->camera = camera;
	font = TTF_OpenFont( "Fonts/Frontman.ttf", 30 );
	this->arrow = new Sprite( renderTarget, "Images/Cursor/menuArrow.png" );
	this->sound = Sound::getInstance();
	menuItems = new std::vector<MenuItem*>();
	menuItems->push_back( new MenuItem( renderTarget, font, "Game One" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Game Two" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Game Three" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Back" ) );

	margin = 40;
	selected = 0;
	center();*/
}


SaveMenu::~SaveMenu()
{}
