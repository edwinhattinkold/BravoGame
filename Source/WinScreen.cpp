#include "WinScreen.h"
#include "CustomCursor.h"
#include "SDL_ttf.h"
#include "MenuItem.h"
#include "World.h"


WinScreen::WinScreen( World* world, SDL_Renderer* renderTarget, Camera* camera )
	: InGameMenu( world, renderTarget, camera )
{
	menuItems->push_back( new MenuItem( renderTarget, font, "Continue" ) );

	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	this->backgroundImage = Assets::getInstance()->getAsset( Asset_WinScreen_Background );
	positionMenuItems();
}


WinScreen::~WinScreen()
{

}

void WinScreen::tick( int mouseX, int mouseY )
{
	SDL_ShowCursor( SDL_DISABLE );

	/* Draw background image */
	SDL_RenderCopy( renderTarget, backgroundImage, NULL, &backgroundImageRect );

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

void WinScreen::firstTick()
{
	backgroundImageRect.w = camera->getCamera()->w;
	backgroundImageRect.h = camera->getCamera()->h;
	positionMenuItems();
	sound->playSound( Sound_Game_Over_Applause, 0.5f );
	sound->playSoundLooping( Sound_Game_Over_Win );
}

void WinScreen::positionMenuItems()
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		menuItems->at( c )->setXPosition( arrow->positionRect.w + 40 );
		int yPosition = camera->windowHeight - menuItems->at( c )->getHeight() - 20;
		menuItems->at( c )->setYPosition( yPosition );
	}
	updateSelected();
}

void WinScreen::handleKeyboardInput( SDL_Keycode keyPressed )
{
	switch( keyPressed )
	{
		case( SDLK_w ) :
		case( SDLK_UP ) :
			if( selected != 0 )
				selected--;
			else
				selected = menuItems->size() - 1;
			sound->playSound( Sound_MainMenu_Tick );
			break;
		case( SDLK_s ) :
		case( SDLK_DOWN ) :
			if( selected != menuItems->size() - 1 )
				selected++;
			else
				selected = 0;
			sound->playSound( Sound_MainMenu_Tick );
			break;
		case( SDLK_RETURN ) :
			sound->playSound( Sound_MainMenu_Click );
			handleChoice( selected );
			break;
	}
	updateSelected();
}

void WinScreen::mouseButtonClicked( int mouseX, int mouseY )
{
	for( size_t index = 0; index < menuItems->size(); index++ )
		if( mouseX >= menuItems->at( index )->getXPosition() && mouseX <= menuItems->at( index )->getXPosition() + menuItems->at( index )->getWidth() &&
			mouseY >= menuItems->at( index )->getYPosition() && mouseY <= menuItems->at( index )->getYPosition() + menuItems->at( index )->getHeight() )
		{
			sound->playSound( Sound_MainMenu_Click );
			handleChoice( index );
		}
}

void WinScreen::updateSelected()
{
	MenuItem* selectedItem = menuItems->at( selected );
	for( size_t c = 0; c < menuItems->size(); c++ )
		menuItems->at( c )->setColor( renderTarget, Red );
	selectedItem->setColor( renderTarget, SelectedRed );

	arrow->positionRect.x = selectedItem->getXPosition() - arrow->positionRect.w - 20;
	arrow->positionRect.y = selectedItem->getYPosition() + selectedItem->getHeight() / 2 - arrow->positionRect.h / 2 - 3;
}

void WinScreen::handleChoice( int index )
{
	
}
