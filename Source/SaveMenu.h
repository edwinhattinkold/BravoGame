#pragma once
#include "Camera.h"
#include "SDL.h"
#include "Sprite.h"
#include <vector>
#include "Sound.h"
#include "SDL_ttf.h"
#include <string>

class World;
class MenuItem;

class SaveMenu
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
	enum Choices {
		Game1, Game2, Game3, Back
	};
	std::vector<std::string> fileNames;
public:
	SaveMenu( World* world, SDL_Renderer* renderTarget, Camera* camera, TTF_Font* font );
	~SaveMenu();
	bool saving;
	void tick( int mouseX, int mouseY );
	void center();
	void handleKeyboardInput( SDL_Keycode keyPressed );
	void mouseButtonClicked( int mouseX, int mouseY );
	void updateSelected();
	void handleChoice( int index );
};

