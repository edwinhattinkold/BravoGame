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

class PauseMenu
{
private:
	SDL_Renderer* renderTarget;
	Camera* camera;
	TTF_Font* font;
	World* world;
	Sprite* arrow;
	Sound* sound;
	std::vector<MenuItem*>* menuItems;
	SaveMenu* saveMenu;
	int combinedHeight;
	int margin;
	int selected;
	enum Choices { Continue, Save_Game, Main_Menu };

public:
	PauseMenu(World* world, SDL_Renderer* renderTarget, Camera* camera);
	~PauseMenu();
	void tick( int mouseX, int mouseY );
	void center();
	void handleKeyboardInput( SDL_Keycode keyPressed );
	void mouseButtonClicked( int mouseX, int mouseY );
	void updateSelected();
	void handleChoice( int index );
};

