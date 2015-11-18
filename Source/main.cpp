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
#include "vld.h"
#include "Car.h"
#include "PhysicsWorld.h"


//SVEN

SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget){
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);
	return texture;
}
///SVEN
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
		TTF_Init();
		SDL_Init( SDL_INIT_VIDEO );

		if( !font )
			printf( "TTF_OpenFont: %s\n", TTF_GetError() ); //I.p.v. printen wellicht voor dit soort dingen exception handling?

		window = nullptr;
		font = TTF_OpenFont( "Fonts/Frontman.ttf", 40 );

		Uint32 flags = SDL_WINDOW_SHOWN;
		windowWidth = 1280;
		windowHeight = 720;
		levelWidth = 3072;
		levelHeight = 3072;

		window = SDL_CreateWindow( "TerrorEdje!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags );

		if( Settings::getInstance()->getBoolean( Settings_fullscreen ) )
		{
			getDesktopResolution( windowWidth, windowHeight );
			flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
			SDL_SetWindowSize( window, windowWidth, windowHeight );
			SDL_SetWindowFullscreen( window, flags );
		}

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

	return 0;
}