#include <SDL/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow;
SDL_Surface* gScreenSurface;
SDL_Surface* gHelloWorld;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;

	gHelloWorld = SDL_LoadBMP("hello_world.bmp");
	if (gHelloWorld == NULL)
	{
		success = false;
	}
	return success;
}

void close()
{
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
		close();
		return 0;
	}
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
	}
	else
	{
		SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
		SDL_Delay(2000);
	}
	close();
	return 0;
}