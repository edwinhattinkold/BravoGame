#include "WinScreen.h"
#include "CustomCursor.h"
#include "SDL_ttf.h"
#include "MenuItem.h"
#include "World.h"


WinScreen::WinScreen( World* world, SDL_Renderer* renderTarget, Camera* camera )
	: InGameMenu( world, renderTarget, camera )
{
	menuItems->push_back( new MenuItem( renderTarget, font, "Restart" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Mainmenu" ) );

	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	this->backgroundImage = Assets::getInstance()->getAsset( Asset_WinScreen_Background );
	center();
}


WinScreen::~WinScreen()
{
}

void WinScreen::tick( int mouseX, int mouseY )
{
	
}

void WinScreen::firstTick()
{
	
}

void WinScreen::center()
{
	
}

void WinScreen::handleKeyboardInput( SDL_Keycode keyPressed )
{
	
}

void WinScreen::mouseButtonClicked( int mouseX, int mouseY )
{
	
}

void WinScreen::updateSelected()
{
	
}

void WinScreen::handleChoice( int index )
{
	
}
