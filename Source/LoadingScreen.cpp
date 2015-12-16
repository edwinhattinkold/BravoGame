#include "LoadingScreen.h"
#include "CustomCursor.h"
#include "Assets.h"
#include "Sound.h"

LoadingScreen::LoadingScreen( SDL_Renderer* renderTarget, Camera* camera, TTF_Font* font )
{
	this->renderTarget		= renderTarget;
	this->camera			= camera;
	this->font				= font;
	adImage = Assets::getInstance()->getAsset( Asset_LoadScreen_Ad );
	SDL_QueryTexture( adImage, NULL, NULL, &adRect.w, &adRect.h );
}


LoadingScreen::~LoadingScreen()
{
	
}

int LoadingScreen::createMenu( )
{
	prevTime = currentTime;
	currentTime = SDL_GetTicks();;
	deltaTime = 0.0f;
	time = 8.50f;
	passedTime = 0.00f;
	int windowWidth = camera->getCamera()->w;
	int windowHeight = camera->getCamera()->h;

	adRect.x = windowWidth / 2 - adRect.w / 2;
	adRect.y = windowHeight / 2 - adRect.h / 2;

	maxLoading.w = windowWidth / 4;
	maxLoading.x = windowWidth / 2 - maxLoading.w / 2;
	maxLoading.h = 30;
	maxLoading.y = windowHeight - maxLoading.h - 20;

	loaded.x = maxLoading.x;
	loaded.y = maxLoading.y;
	loaded.h = maxLoading.h;

	Sound::getInstance()->playSound( Sound_Ad );
	while( passedTime < time )
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = ( currentTime - prevTime ) / 1000.0f;
		passedTime += deltaTime;

		float percentagePassed = passedTime / time;
		loaded.w = maxLoading.w * percentagePassed;

		while( SDL_PollEvent( &ev ) )
		{
			switch( ev.type )
			{
				case SDL_QUIT:
					return Choices::Exit;
				case SDL_MOUSEMOTION:
					mouseX = ev.motion.x;
					mouseY = ev.motion.y;
					break;
			}
		}
		SDL_RenderClear( renderTarget );
	
		SDL_SetRenderDrawColor( renderTarget, 255, 255, 255, 255 );

		SDL_RenderFillRect( renderTarget, &loaded );
		SDL_RenderDrawRect( renderTarget, &maxLoading );

		SDL_RenderCopy( renderTarget, adImage, NULL, &adRect );
		CustomCursor::getInstance()->draw( mouseX, mouseY );

		SDL_SetRenderDrawColor( renderTarget, 0, 0, 0, 0 );
		SDL_RenderPresent( renderTarget );
	}
}

int LoadingScreen::getExitCode()
{
	return Choices::Exit;
}