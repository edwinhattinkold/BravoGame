#ifndef MAINMENU_H
#define MAINMENU_H
#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include "MenuItem.h"

class MainMenu
{
private:
	SDL_Rect backgroundImageRect;
	SDL_Texture* backgroundImage;
	std::vector<MenuItem*> menuItems;
	
	Uint32 time;
	int mouseX, mouseY, margin, combinedHeight;
	
public:
	MainMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, SDL_Rect cameraRect, TTF_Font* font);
	~MainMenu();

	void draw(SDL_Renderer* renderTarget);
	int showMenu(SDL_Renderer* renderTarget);
};

#endif

