#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "player.h"
#include "camera.h"
#include "MapGenerator.h";
#include <Box2D/Box2D.h>

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
 void run(){
	 SDL_Window *window = nullptr;
	 SDL_Renderer *renderTarget = nullptr;

	 int currentTime = 0;
	 int prevTime = 0;
	 float deltaTime = 0.0f;
	 const Uint8 *keyState;
	 int windowWidth = 640;
	 int windowHeight = 480;
	 int levelWidth, levelHeight;

	 SDL_Init(SDL_INIT_VIDEO);

	 window = SDL_CreateWindow("TerrorEdje!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	 renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	 MapGenerator mg{ renderTarget };
	 std::vector<Location> *locations = mg.GenerateMap("maps/level1.tmx");
	 Tile *tile = nullptr;
	 SDL_Rect tarRect = { 0, 0, 32, 32 };
	 
	 for (int i = 0; i < locations->size(); i++){
		 Location l = locations->at(i);
		 tarRect.x = l.x*32;
		 tarRect.y = l.y*32;
		 tile = mg.getTile(l.id);
		 SDL_RenderCopy(renderTarget, tile->getTexture(), tile->getRect(), &tarRect);
	 }
	 
	 SDL_RenderPresent(renderTarget);
	 delete locations;
	 std::cout << "done";
 }
int main(int argc, char *argv[]){
	run();
	_CrtDumpMemoryLeaks();
	std::getchar();

	return 0;
}

int main2(int argc, char *argv[]){

	//test box2d specific code
	b2World* world = new b2World(b2Vec2(0, 0));


	//Initializing and loading variables
	SDL_Window *window = nullptr;
	SDL_Renderer *renderTarget = nullptr;

	int currentTime = 0;
	int prevTime = 0;
	float deltaTime = 0.0f;
	const Uint8 *keyState;
	int windowWidth = 640;
	int windowHeight = 480;
	int levelWidth, levelHeight;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("TerrorEdje!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(renderTarget, 0, 0, 255, 255);

	Player player1(renderTarget, 0, 0, 300.0f);
	Player player2(renderTarget, 600, 400, 300.0f);

	Sprite dog(renderTarget, "Images/spritesheet_dog.png", 300, 300, 2, 1, 0.25f);

	SDL_Texture *texture = LoadTexture("Images/rect.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);

	Camera camera(levelWidth, levelHeight, windowWidth, windowHeight);

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning){
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;
		while (SDL_PollEvent(&ev) != 0){
			if (ev.type == SDL_QUIT)
				isRunning = false;
		}

		keyState = SDL_GetKeyboardState(NULL);

		/* Update all the objects */
		player1.Update(deltaTime, keyState);
		player2.Update(deltaTime, keyState);
		dog.Update(deltaTime, keyState);

		camera.Update(player1.getPositionX(), player1.getPositionY());

		SDL_RenderClear(renderTarget);

		SDL_RenderCopy(renderTarget, texture, &camera.getCamera(), NULL);

		/* Render all the objects */
		player1.Draw(renderTarget, camera.getCamera());
		player2.Draw(renderTarget, camera.getCamera());
		dog.Draw(renderTarget, camera.getCamera());

		SDL_RenderPresent(renderTarget);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(texture);

	texture = nullptr;

	window = nullptr;
	renderTarget = nullptr;

	IMG_Quit();
	SDL_Quit();

	_CrtDumpMemoryLeaks();

	return 0;
}