#ifndef MAINMENU_H
#define MAINMENU_H
#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include "OptionsMenu.h"
#include "MenuItem.h"
#include "Sound.h"

class MainMenu
{
private:
	SDL_Rect backgroundImageRect;
	SDL_Texture* backgroundImage;
	std::vector<MenuItem*> menuItems;
	Sound* sound;
	Uint32 time;
	int mouseX, mouseY, margin, combinedHeight;
	OptionsMenu* optionsMenu;
	int optionsChoice;

	static enum Choices { Continue, Load_Game, Options, Exit };

public:
	MainMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, SDL_Rect cameraRect, TTF_Font* font);
	~MainMenu();

	int getExitCode();
	void draw(SDL_Renderer* renderTarget);
	int showMenu(SDL_Renderer* renderTarget);
	int createMenu(SDL_Renderer* renderTarget);
};

#endif

