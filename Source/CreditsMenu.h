#pragma once
#include <SDL.h>
#include "Sound.h"
#include "MenuItem.h"
#include <vector>
#include "Camera.h"

class CreditsMenu
{
private:
	Camera* camera;
	SDL_Renderer* renderTarget;
	Sound* sound;
	TTF_Font* creditsTitelFont;
	TTF_Font* creditsDefaultFont;
	TTF_Font* creditsMainTitelFont;

	MenuItem* backButton;

	Uint32 time;
	int mouseX, mouseY, defaultMargin, largerMargin, titelSpacing, previousTime, currentTime, speed;
	float deltaTime, pastTime;
	std::vector<std::pair<MenuItem*, int>*>* lines;
	std::vector<MenuItem*>* menuItems;
	void positionAllLines();
	void fadeIn();

	static enum LineType { MainTitel, Titel, Default };
	static enum Choices { Back, Sound_On_Off, Exit };

	std::pair<MenuItem*, int>* createLine(SDL_Renderer* renderTarget, char * line, LineType lineType, int margin);
	bool shouldMove(float deltaTime);
	bool isDone();

public:
	CreditsMenu( SDL_Renderer* renderTarget, Camera* camera );
	~CreditsMenu();

	int getBackCode();
	int getExitCode();
	void update(float deltaTime);
	void draw(SDL_Renderer* renderTarget);
	int showMenu(SDL_Renderer* renderTarget);
	int createMenu(SDL_Renderer* renderTarget);
};

