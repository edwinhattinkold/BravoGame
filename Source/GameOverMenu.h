#pragma once
#include "Camera.h"
#include "SDL.h"
#include "Sprite.h"
#include <vector>
#include "Sound.h"
#include "SaveMenu.h"
#include "SDL_ttf.h"

class World;
class MenuItem;

class GameOverMenu
{
private:
	SDL_Renderer* renderTarget;
	Camera* camera;
	TTF_Font* font;
	World* world;
	Sprite* arrow;
	Sound* sound;
	std::vector<MenuItem*>* menuItems;
	int combinedHeight;
	int margin;
	int selected;

	SDL_Texture* backgroundImage;
	SDL_Rect backgroundImageRect;

	enum Choices
	{
		Restart, Main_Menu
	};

	void center();
public:
	GameOverMenu(World* world, SDL_Renderer* renderTarget, Camera* camera);
	~GameOverMenu();
	void tick( int mouseX, int mouseY );
	void handleKeyboardInput( SDL_Keycode keyPressed );
	void mouseButtonClicked( int mouseX, int mouseY );
	void updateSelected();
	void handleChoice( int index );
	void firstTick();
};

