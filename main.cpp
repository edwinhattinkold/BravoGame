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

int showMenu(SDL_Surface* screen, TTF_Font* font){
	Uint32 time;
	int x, y;
	const int NUMMENU = 2;
	const char* labels[NUMMENU] = { "Continue", "Exit" };
	SDL_Surface* menus[NUMMENU];
	bool selected[NUMMENU] = { 0, 0 };
	SDL_Color color[2] = { { 255, 255, 255 }, { 255, 0, 0 } };
	
	menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
	SDL_Rect pos[NUMMENU];
	pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
	pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w / 2 - menus[1]->clip_rect.w / 2;
	pos[1].y = screen->clip_rect.h / 2 - menus[1]->clip_rect.h;

	SDL_FillRect(screen, screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_Event event;
	while (1)
	{
		time = SDLGetTicks();
		while (SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					for (int c = 0; c < NUMMENU; c++)
						SDL_FreeSurface(menus[c]);
					return 1;
				case SDL_MOUSEMOTION:
					x = event.motion.x;
					y = event.motion.y;
					for (int i = 0; i < NUMMENU; i++){
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h){
							if (!selected[i]){
								selected[i] = true;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font, menus[i], color[1]);
							}
						} else {
							if (selected[i]){
								selected[i] = 0;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font, menus[i], color[0]);
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					x = event.motion.x;
					y = event.motion.y;
					for (int x = 0; x < NUMMENU; x++){
						if (x >= pos[x].x && x <= pos[x].x + pos[x].w && y >= pos[x].y && y <= pos[x].y + pos[x].h){
							return x;
						}
						break;
					}
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
						return 0;
			}
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

	//test box2d specific code
	b2World* world = new b2World(b2Vec2(0, 0));

	//Initializing and loading variables
	SDL_Window *window = nullptr;
	SDL_Renderer *renderTarget = nullptr;
	SDL_Surface* screen = nullptr;
	TTF_Font* font = TTF_OpenFont("Fonts/Apocalyse-Regular.ttf", 32);

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
	screen = SDL_SetVideoMode(windowWidth, windowHeight, 32, SDL_SWSURFACE);

	SDL_SetRenderDrawColor(renderTarget, 0, 0, 255, 255);

	Player player1(renderTarget, 0, 0, 300.0f);
	Player player2(renderTarget, 600, 400, 300.0f);

	Sprite dog(renderTarget, "Images/spritesheet_dog.png", 300, 300, 2, 1, 0.25f);

	SDL_Texture *texture = LoadTexture("Images/rect.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);

	Camera camera(levelWidth, levelHeight, windowWidth, windowHeight);

	bool isRunning = true;
	SDL_Event ev;

	int i = showmenu(screen, font);
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