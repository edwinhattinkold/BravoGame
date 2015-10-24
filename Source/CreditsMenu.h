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
	TTF_Font* creditsFont;
	Uint32 time;
	int mouseX, mouseY, defaultMargin, largerMargin;
	std::vector<std::pair<MenuItem*, int>*>* lines;
	std::vector<MenuItem*>* menuItems;
	void center();
	std::pair<MenuItem*, int>* createLine(SDL_Renderer* renderTarget, std::string line, int margin);

	static enum Choices { Back, Exit };
public:
	CreditsMenu(SDL_Renderer* renderTarget, SDL_Rect* cameraRect);
	~CreditsMenu();

	int getBackCode();
	int getExitCode();
	void draw(SDL_Renderer* renderTarget);
	int showMenu(SDL_Renderer* renderTarget);
	int createMenu(SDL_Renderer* renderTarget);
};

