#pragma once
#include "Camera.h"
#include "SDL.h"
#include "Sprite.h"
#include <vector>
#include "Sound.h"
#include "SDL_ttf.h"

class World;
class MenuItem;

class InGameMenu
{
protected:
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
public:
	InGameMenu( World* world, SDL_Renderer* renderTarget, Camera* camera );
	~InGameMenu();
	virtual void tick( int mouseX, int mouseY );
	virtual void center();
	virtual void handleKeyboardInput( SDL_Keycode keyPressed );
	virtual void mouseButtonClicked( int mouseX, int mouseY );
	virtual void updateSelected();
	virtual void handleChoice( int index );

};

