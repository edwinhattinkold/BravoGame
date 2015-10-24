#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include "wtypes.h"
#include <Box2D/Box2D.h>
#include "World.h"
#include "Sound.h"

class MainHelper {
private:
	SDL_Window *window;
	TTF_Font* font;
	int windowWidth, windowHeight, levelWidth, levelHeight;
	World* world;
	bool fullScreen;

public:
	void MainHelper::GetDesktopResolution(int& horizontal, int& vertical)
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		horizontal = desktop.right;
		vertical = desktop.bottom;
	}

	MainHelper::MainHelper(bool fullScreen){
		Uint32 flags = SDL_WINDOW_SHOWN;

		TTF_Init();
		if (!font) 
			printf("TTF_OpenFont: %s\n", TTF_GetError()); //I.p.v. printen wellicht voor dit soort dingen exception handling?

		this->window = nullptr;
		this->font = TTF_OpenFont("Fonts/Frontman.ttf", 40);

		this->windowWidth = 1024;
		this->windowHeight = 576; // waarom niet 512? -> omdat 1024 en 574 een aspect ratio hebben van 16:9, bij 512 zou dat 2:1 zijn
		this->levelWidth = 1024;
		this->levelHeight = 1024;

		if (fullScreen){
			this->GetDesktopResolution(this->windowWidth, this->windowHeight);
			flags = SDL_WINDOW_FULLSCREEN;
		}

		SDL_Init(SDL_INIT_VIDEO);

		this->window = SDL_CreateWindow("TerrorEdje!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->windowWidth, this->windowHeight, flags);
		this->world = new World(this->window, this->levelWidth, this->levelHeight, this->font);
	}

	void MainHelper::run(){
		this->world->Run();
		this->destroyMainHelper();
	}

	void MainHelper::destroyMainHelper(){
		SDL_DestroyWindow(this->window);
		this->window = nullptr;

		TTF_CloseFont(this->font);
		this->font = nullptr;

		delete this->world;
		this->world = nullptr;

		SDL_Quit();
		TTF_Quit();
		Sound_Quit();
	}
};

int main(int argc, char *argv[]){
	MainHelper* mainHelper = new MainHelper(true);
	mainHelper->run();

	delete mainHelper;
	mainHelper = nullptr;

	_CrtDumpMemoryLeaks();
	return 0;
}