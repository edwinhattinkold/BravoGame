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
#include "Chunk.h";
#include "wtypes.h"
#include <Box2D/Box2D.h>
#include "MapDrawer.h"

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

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void run(){
	 TTF_Init();
	 SDL_Window *window = nullptr;
	 SDL_Renderer *renderTarget = nullptr;
	 TTF_Font* font = TTF_OpenFont("Fonts/Frontman.ttf", 40);

	 int currentTime = 0;
	 int prevTime = 0;
	 float deltaTime = 0.0f;
	 const Uint8 *keyState;
	 int windowWidth = 1024;
	 int windowHeight = 576;
	 int levelWidth = 1024, levelHeight = 1024;

	 SDL_Init(SDL_INIT_VIDEO);

	 window = SDL_CreateWindow("TerrorEdje!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	 renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	 MapDrawer *mapDrawer = new MapDrawer(renderTarget);
	 SDL_Texture *mainMenuBackground = LoadTexture("Images/Mainmenu/background.png", renderTarget);
	 Camera camera(levelWidth, levelHeight, windowWidth, windowHeight);

	 MainMenu menu(renderTarget, mainMenuBackground, camera.getCamera(), font);
	 bool isRunning = true;
	 
	 int i = menu.showMenu(renderTarget);
	 if (i == menu.getExitCode())
		 isRunning = false;

	 Player player1(renderTarget, 0, 0, 300.0f);
	 SDL_Event ev;
	 while (isRunning){
		 prevTime = currentTime;
		 currentTime = SDL_GetTicks();
		 deltaTime = (currentTime - prevTime) / 1000.0f;
		 while (SDL_PollEvent(&ev) != 0){
			 if (ev.type == SDL_QUIT)
				 isRunning = false;
			 if (ev.key.keysym.sym == SDLK_ESCAPE){
				 Sound::getInstance()->playSoundLooping("rock_intro.mp3");
				 int i = menu.showMenu(renderTarget);
				 if (i == menu.getExitCode())
					 isRunning = false;
				 
			 }
		 }

		 keyState = SDL_GetKeyboardState(NULL);

		 player1.Update(deltaTime, keyState);

		 camera.Update(player1.getPositionX(), player1.getPositionY());

		 SDL_RenderClear(renderTarget);		 
		 //mapDrawer->Draw(renderTarget, camera.getCamera());
		 player1.Draw(renderTarget, camera.getCamera());

		 SDL_RenderPresent(renderTarget);
	 }

	 SDL_DestroyWindow(window);
	 SDL_DestroyRenderer(renderTarget);
	 window = nullptr;
	 renderTarget = nullptr;
 }

int main(int argc, char *argv[]){
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}