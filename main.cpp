#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include "player.h"
#include "camera.h"

#include <Box2D/Box2D.h>

SDL_Texture* createTextTexture(SDL_Renderer* renderTarget, TTF_Font* font, const char* text, SDL_Color color){
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_FreeSurface(textSurface);
	return textTexture;
}

int showMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, int windowWidth, int windowHeight, TTF_Font* font){
	SDL_Rect SrcR;

	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = windowWidth;
	SrcR.h = windowHeight;

	Uint32 time;
	int x, y;
	const int NUMMENU = 2;
	const char* labels[NUMMENU] = { "Continue", "Exit" };
	SDL_Surface *menuSurfaces[NUMMENU];
	SDL_Texture* menus[NUMMENU];
	bool selected[NUMMENU] = { 0, 0 };
	SDL_Color color[2] = { { 255, 255, 255, 255 }, { 255, 0, 0, 255 } };
	
	menus[0] = createTextTexture(renderTarget, font, labels[0], color[0]);
	menus[1] = createTextTexture(renderTarget, font, labels[1], color[0]);
	
	SDL_Rect pos[NUMMENU];
	pos[0].x = 500;
	pos[0].y = 100;
	pos[0].w = 60;
	pos[0].h = 50;
	pos[1].x = 500;
	pos[1].y = 200;
	pos[1].w = 60;
	pos[1].h = 50;

	
	SDL_Event event;
	while (1)
	{
		time = SDL_GetTicks();
		while (SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					for (int c = 0; c < NUMMENU; c++)
						SDL_DestroyTexture(menus[c]);
					return 1;
				case SDL_MOUSEMOTION:
					x = event.motion.x;
					y = event.motion.y;
					for (int i = 0; i < NUMMENU; i++){
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h){
							if (!selected[i]){
								selected[i] = true;
								SDL_DestroyTexture(menus[i]);
								menus[i] = createTextTexture(renderTarget, font, labels[i], color[1]);
							}
						} else {
							if (selected[i]){
								selected[i] = 0;
								SDL_DestroyTexture(menus[i]);
								menus[i] = createTextTexture(renderTarget, font, labels[i], color[0]);
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					x = event.motion.x;
					y = event.motion.y;
					for (int x = 0; x < NUMMENU; x++)
						if (x >= pos[x].x && x <= pos[x].x + pos[x].w && y >= pos[x].y && y <= pos[x].y + pos[x].h)
							return x;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
						return 0;
			}
			
			SDL_RenderClear(renderTarget);
			SDL_RenderCopy(renderTarget, backgroundImage, &SrcR, NULL);
			for (int c = 0; c < NUMMENU; c++)
				SDL_RenderCopy(renderTarget, menus[c], NULL, &pos[c]);
			SDL_RenderPresent(renderTarget);
		}
	}
}

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

int main(int argc, char *argv[]){
	TTF_Init();
	//test box2d specific code
	b2World* world = new b2World(b2Vec2(0, 0));

	//Initializing and loading variables
	SDL_Window *window = nullptr;
	SDL_Renderer *renderTarget = nullptr;
	TTF_Font* font = TTF_OpenFont("Fonts/Pacifico.ttf", 32);
	std::cout << TTF_GetError() << std::endl;

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

	SDL_Texture *mainMenuBackground = LoadTexture("Images/Mainmenu/background.png", renderTarget);
	SDL_QueryTexture(mainMenuBackground, NULL, NULL, &levelWidth, &levelHeight);

	Camera camera(levelWidth, levelHeight, windowWidth, windowHeight);

	bool isRunning = true;
	SDL_Event ev;

	int i = showMenu(renderTarget, mainMenuBackground, levelWidth, levelHeight, font);
	if (i == 1)
		isRunning = false;

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