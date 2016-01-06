#pragma once
#include "InGameMenu.h"

class GameOverMenu : public InGameMenu
{
private:
	SDL_Texture* backgroundImage;
	SDL_Rect backgroundImageRect;

	enum Choices
	{
		High_Score, Restart, Main_Menu
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

