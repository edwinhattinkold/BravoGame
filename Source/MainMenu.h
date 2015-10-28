#ifndef MAINMENU_H
#define MAINMENU_H
#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include "OptionsMenu.h"
#include "CreditsMenu.h"
#include "MenuItem.h"
#include "Sound.h"
#include "Camera.h"

class MainMenu
{
private:
	SDL_Rect backgroundImageRect;
	Camera* camera;
	SDL_Texture* backgroundImage;
	std::vector<MenuItem*>* menuItems;
	Sound* sound;
	Uint32 time;
	int mouseX, mouseY, margin, combinedHeight;

	OptionsMenu* optionsMenu;
	CreditsMenu* creditsMenu;
	int optionsChoice, creditsChoice;
	void center();

	static enum Choices { Continue, Load_Game, Options, Credits, Exit };

public:
	MainMenu( SDL_Renderer* renderTarget, SDL_Window* window, SDL_Texture* backgroundImage, Camera* camera, TTF_Font* font );
	~MainMenu();

	int getExitCode();
	void draw(SDL_Renderer* renderTarget);
	int showMenu(SDL_Renderer* renderTarget);
	int createMenu(SDL_Renderer* renderTarget);
};

#endif

