#ifndef MAINMENU_H
#define MAINMENU_H
#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include "OptionsMenu.h"
#include "CreditsMenu.h"
#include "LoadingMenu.h"
#include "MenuItem.h"
#include "Sound.h"
#include "Camera.h"
#include "HowToPlay.h"
#include "Sprite.h"
class World;

class MainMenu
{
private:
	SDL_Rect backgroundImageRect;
	Camera* camera;
	SDL_Renderer* renderTarget;
	SDL_Texture* backgroundImage;
	Sprite* arrow;
	std::vector<MenuItem*>* menuItems;
	Sound* sound;
	Uint32 time;

	int mouseX, mouseY, margin, combinedHeight;
	OptionsMenu* optionsMenu;
	CreditsMenu* creditsMenu;
	LoadingMenu* loadMenu;
	HowToPlay* howToPlay;
	int optionsChoice, creditsChoice, howToPlayChoise, loadChoice;
	void center();
	static enum Choices { Continue, Load_Game, How_To_Play, Options, Credits, Exit };
	int selected;
	World* world;
public:
	MainMenu( SDL_Renderer* renderTarget, SDL_Window* window, SDL_Texture* backgroundImage, Camera* camera, TTF_Font* font, World* world );
	~MainMenu();

	int getExitCode();
	void drawMenuItems( SDL_Renderer* renderTarget );
	int showMenu(SDL_Renderer* renderTarget);
	int createMenu(SDL_Renderer* renderTarget);
	void handleKeyboardInput(SDL_Keycode keyPressed);
	void updateSelected();
};

#endif

