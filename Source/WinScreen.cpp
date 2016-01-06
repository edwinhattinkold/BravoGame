#include "WinScreen.h"
#include "CustomCursor.h"
#include "SDL_ttf.h"
#include "MenuItem.h"
#include "World.h"


WinScreen::WinScreen( World* world, SDL_Renderer* renderTarget, Camera* camera )
	: InGameMenu( world, renderTarget, camera )
{
	confetti = Assets::getInstance()->getAsset( Asset_WinScreen_Confetti );
	menuItems->push_back( new MenuItem( renderTarget, font, "Continue" ) );

	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	this->backgroundImage = Assets::getInstance()->getAsset( Asset_WinScreen_Background );

	confettiSourceRect.x = 0;
	confettiSourceRect.y = 0;
	animationSpeed = 0.03f;

	framesX = 11;
	framesY = 10;
	startFrameX = 0;
	startFrameY = 0;
	
	currentFrameX = startFrameX;
	currentFrameY = startFrameY;

	SDL_QueryTexture( confetti, NULL, NULL, &confettiSourceRect.w, &confettiSourceRect.h );

	textureWidth = confettiSourceRect.w;
	textureHeight = confettiSourceRect.h;

	confettiSourceRect.w /= framesX;
	confettiSourceRect.h /= framesY;

	frameWidth = confettiSourceRect.w;
	frameHeight = confettiSourceRect.h;

	/* set the first frame */
	confettiSourceRect.x = frameWidth * startFrameX;
	confettiSourceRect.y = frameHeight * startFrameY;

	frameCounter = 0.0f;

	positionMenuItems();
}


WinScreen::~WinScreen()
{

}

void WinScreen::tick( int mouseX, int mouseY )
{
	SDL_ShowCursor( SDL_DISABLE );
	float deltaTime = 0.016f;
	confettiAnimation( deltaTime );

	/* Draw background image */
	SDL_RenderCopy( renderTarget, backgroundImage, NULL, &backgroundImageRect );

	/* Draw confetti */
	SDL_RenderCopy( renderTarget, confetti, &confettiSourceRect, &backgroundImageRect );

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
	sound->playSound( Sound_Game_Over_Applause );
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
	world->showHighscores(true);
}

void WinScreen::confettiAnimation( float deltaTime )
{
	frameCounter += deltaTime;

	if( frameCounter >= animationSpeed )
	{
		frameCounter = 0;
		confettiSourceRect.x += frameWidth;
		currentFrameX += 1;

		if( confettiSourceRect.x >= textureWidth )
		{
			confettiSourceRect.y += frameHeight;
			confettiSourceRect.x = 0;

			currentFrameX = 0;
			currentFrameY += 1;
		}

		if( confettiSourceRect.y >= textureHeight )
		{
			confettiSourceRect.y = 0;
			currentFrameY = 0;
		}

		if( currentFrameX == 3 && currentFrameY == framesY - 1 )
		{
			confettiSourceRect.x = 0;
			confettiSourceRect.y = 0;

			currentFrameX = 0;
			currentFrameY = 0;
		}
	}
}
