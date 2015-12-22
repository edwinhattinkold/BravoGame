#pragma once
#include "InGameMenu.h"

class WinScreen : public InGameMenu
{
private:
	SDL_Texture* backgroundImage;
	SDL_Rect backgroundImageRect;

	SDL_Texture* confetti;
	SDL_Rect confettiSourceRect;
	float animationSpeed;
	int column, row, textureWidth, textureHeight, framesX, framesY, frameWidth, frameHeight, startFrameX, startFrameY, currentFrameX, currentFrameY;
	float frameCounter;
	

	enum Choices
	{
		Restart, Main_Menu
	};

	void positionMenuItems();
public:
	WinScreen( World* world, SDL_Renderer* renderTarget, Camera* camera );
	~WinScreen();
	void tick( int mouseX, int mouseY );
	void handleKeyboardInput( SDL_Keycode keyPressed );
	void mouseButtonClicked( int mouseX, int mouseY );
	void updateSelected();
	void handleChoice( int index );
	void firstTick();
	void confettiAnimation( float deltaTime );
};

