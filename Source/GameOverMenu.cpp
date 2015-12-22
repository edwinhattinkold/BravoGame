#include "GameOverMenu.h"
#include "CustomCursor.h"
#include "SDL_ttf.h"
#include "MenuItem.h"
#include "World.h"

GameOverMenu::GameOverMenu( World* world, SDL_Renderer* renderTarget, Camera* camera )
	: InGameMenu(world, renderTarget, camera)
{
	menuItems->push_back( new MenuItem( renderTarget, font, "Restart" ) );
	menuItems->push_back( new MenuItem( renderTarget, font, "Mainmenu" ) );

	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	this->backgroundImage = Assets::getInstance()->getAsset( Asset_GameOverScreen_Background );
	center();
}


GameOverMenu::~GameOverMenu()
{

}

void GameOverMenu::tick( int mouseX, int mouseY )
{
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

void GameOverMenu::firstTick()
{
	backgroundImageRect.w = camera->getCamera()->w;
	backgroundImageRect.h = camera->getCamera()->h;
	center();
	sound->playSound( Sound_Game_Over );
}

void GameOverMenu::center()
{
	combinedHeight = -100;
	for( std::vector<int>::size_type i = menuItems->size() - 1; i != ( std::vector<int>::size_type ) - 1; i-- )
	{
		combinedHeight += menuItems->at( i )->getHeight();
		int xPosition = ( camera->getCamera()->w / 2 ) - ( menuItems->at( i )->getWidth() / 2 );
		menuItems->at( i )->setXPosition( xPosition );
	}

	int marginHeight = ( ( menuItems->size() - 1 ) * margin );
	combinedHeight += marginHeight;

	for( std::vector<int>::size_type j = menuItems->size() - 1; j != ( std::vector<int>::size_type ) - 1; j-- )
	{
		int previousHeight = 0;
		for( size_t h = 0; h < j; h++ )
			previousHeight += menuItems->at( h )->getHeight();
		int yPosition = ( camera->getCamera()->h / 2 ) - ( combinedHeight / 2 ) + ( j * margin ) + previousHeight;
		menuItems->at( j )->setYPosition( yPosition );
	}
	updateSelected();
}

void GameOverMenu::handleKeyboardInput( SDL_Keycode keyPressed )
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

void GameOverMenu::mouseButtonClicked( int mouseX, int mouseY )
{
	for( size_t index = 0; index < menuItems->size(); index++ )
		if( mouseX >= menuItems->at( index )->getXPosition() && mouseX <= menuItems->at( index )->getXPosition() + menuItems->at( index )->getWidth() &&
			mouseY >= menuItems->at( index )->getYPosition() && mouseY <= menuItems->at( index )->getYPosition() + menuItems->at( index )->getHeight() )
		{
			sound->playSound( Sound_MainMenu_Click );
			handleChoice( index );
		}
}

void GameOverMenu::updateSelected()
{
	MenuItem* selectedItem = menuItems->at( selected );
	for( size_t c = 0; c < menuItems->size(); c++ )
		menuItems->at( c )->setColor( renderTarget, Red );
	selectedItem->setColor( renderTarget, SelectedRed );

	arrow->positionRect.x = selectedItem->getXPosition() - arrow->positionRect.w - 20;
	arrow->positionRect.y = selectedItem->getYPosition() + selectedItem->getHeight() / 2 - arrow->positionRect.h / 2 - 3;
}

void GameOverMenu::handleChoice( int index )
{
	switch( index )
	{
		case( Choices::Restart ) :
			world->reset();
			world->setGameState( GameState_Running );
			break;
		case( Choices::Main_Menu ) :
			world->reset();
			sound->playSoundLooping( Sound_MainMenu_Theme, 0.5f );
			world->setGameState( GameState_In_MainMenu );
			break;
	}
}