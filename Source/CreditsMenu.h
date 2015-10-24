#pragma once
#include <SDL.h>
#include "Sound.h"
#include "MenuItem.h"
#include <vector>

class CreditsMenu
{
private:
	SDL_Rect* cameraRect;
	Sound* sound;
	TTF_Font* creditsTitelFont;
	TTF_Font* creditsDefaultFont;
	Uint32 time;
	int mouseX, mouseY, defaultMargin, largerMargin, titelSpacing, previousTime, currentTime, speed;
	float deltaTime, pastTime;
	std::vector<std::pair<MenuItem*, int>*>* lines;
	std::vector<MenuItem*>* menuItems;
	void positionAllLines();

	static enum LineType { MainTitel, Titel, Default };
	static enum Choices { Back, Sound_On_Off, Exit };

	std::pair<MenuItem*, int>* createLine(SDL_Renderer* renderTarget, char * line, LineType lineType, int margin);
	bool shouldMove(float deltaTime);
	bool isDone();

public:
	CreditsMenu(SDL_Renderer* renderTarget, SDL_Rect* cameraRect);
	~CreditsMenu();

	int getBackCode();
	int getExitCode();
	void update(float deltaTime);
	void draw(SDL_Renderer* renderTarget);
	int showMenu(SDL_Renderer* renderTarget);
	int createMenu(SDL_Renderer* renderTarget);
};

