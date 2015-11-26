#pragma once
#include "SDL.h"
#include "Sound.h"
#include <vector>
#include "MenuItem.h"
#include "Settings.h"
#include "wtypes.h"
#include "Camera.h"
#include "Sprite.h"
class World;

class LoadingMenu
{
private:
	SDL_Window* window;
	SDL_Renderer* renderTarget;
	SDL_Rect backgroundImageRect;
	Camera* camera;
	SDL_Texture* backgroundImage;
	Sprite* arrow;
	SDL_Event ev;
	World* world;
	std::vector<MenuItem*>* menuItems;
	Sound* sound;
	Uint32 time;
	void center();
	void updateSelected();
	int createMenu( SDL_Renderer* renderTarget );
	int mouseX, mouseY, margin, combinedHeight;
	int selected;
	static enum Choices { Game1, Game2, Game3, Back, Exit };
	std::vector<string> fileNames;
public:
	LoadingMenu( SDL_Renderer* renderTarget, SDL_Window* window, SDL_Texture* backgroundImage, Sprite* arrow, Camera* camera, TTF_Font* font, World* world );
	~LoadingMenu();
	void handleSelection( int index );
	int getBackCode();
	int getExitCode();
	void handleKeyboardInput( SDL_Keycode keyPressed );
	void drawMenuItems( SDL_Renderer* renderTarget );
	int showMenu( SDL_Renderer* renderTarget );
};

