#pragma once

#include "InGameMenu.h"
class SaveMenu;

class PauseMenu : public InGameMenu
{
private:
	SaveMenu* saveMenu;
	enum Choices { Continue, Restart, Save_Game, Main_Menu };

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

