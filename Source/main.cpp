#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include "Player.h"
#include "Camera.h"
#include "MainMenu.h"
#include "wtypes.h"
#include <Box2D/Box2D.h>
#include "World.h"
#include "Sound.h"
#include "CustomCursor.h"
#include "Settings.h"

class MainHelper
{
private:
	SDL_Window *window;
	TTF_Font* font;
	int windowWidth, windowHeight, levelWidth, levelHeight;
	World* world;
	bool fullScreen;

public:
	void MainHelper::getDesktopResolution( int& horizontal, int& vertical )
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect( hDesktop, &desktop );
		horizontal = desktop.right;
		vertical = desktop.bottom;
	}

	MainHelper::MainHelper( )
	{
		Uint32 flags = SDL_WINDOW_SHOWN;

		TTF_Init();
		if( !font )
			printf( "TTF_OpenFont: %s\n", TTF_GetError() ); //I.p.v. printen wellicht voor dit soort dingen exception handling?

		window = nullptr;
		font = TTF_OpenFont( "Fonts/Frontman.ttf", 40 );

		windowWidth = 1024;
		windowHeight = 576;
		levelWidth = 3072;
		levelHeight = 3072;

		if( Settings::getInstance()->getBoolean( Settings_fullscreen ) )
		{
			getDesktopResolution( windowWidth, windowHeight );
			flags = SDL_WINDOW_FULLSCREEN;
		}

		SDL_Init( SDL_INIT_VIDEO );

		window = SDL_CreateWindow( "TerrorEdje!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags );
		world = new World( window, levelWidth, levelHeight, font );
	}

	void MainHelper::run()
	{
		world->run();
		destroyMainHelper();
	}

	void MainHelper::destroyMainHelper()
	{
		SDL_DestroyWindow( window );
		window = nullptr;

		TTF_CloseFont( font );
		font = nullptr;

		delete world;
		world = nullptr;

		SDL_Quit();
		TTF_Quit();

		//Our own Quits
		Sound_Quit();
		CustomCursor_Quit();
		Settings_Quit();
	}
};

int main( int argc, char *argv[] )
{
	MainHelper* mainHelper = new MainHelper( );
	mainHelper->run();

	delete mainHelper;
	mainHelper = nullptr;

	_CrtDumpMemoryLeaks();
	return 0;
}