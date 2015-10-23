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



void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void run(){
	TTF_Init(); //Error niet afgevangen
	SDL_Window *window = nullptr;
	TTF_Font* font = TTF_OpenFont("Fonts/Frontman.ttf", 40);

	//int currentTime = 0;
	//int prevTime = 0;
	//float deltaTime = 0.0f;
	//const Uint8 *keyState;
	int windowWidth = 1024;
	int windowHeight = 576; // waarom niet 512?
	int levelWidth = 1024, levelHeight = 1024;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("TerrorEdje!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	//renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	World *world = new World(window, levelWidth, levelHeight, font);
	world->Run();
	SDL_DestroyWindow(window);
	window = nullptr;
}

int main(int argc, char *argv[]){
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}