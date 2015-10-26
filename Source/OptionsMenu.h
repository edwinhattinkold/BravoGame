#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H
#include "SDL.h"
#include "Sound.h"
#include <vector>
#include "MenuItem.h"

class OptionsMenu
{
private:
	SDL_Rect backgroundImageRect;
	SDL_Rect* cameraRect;
	SDL_Texture* backgroundImage;
	std::vector<MenuItem*>* menuItems;
	Sound* sound;
	Uint32 time;
	int mouseX, mouseY, margin, combinedHeight;
	bool soundMuted;
	static enum Choices { Sound_On_Off, Back, Exit };
	void center();

public:
	OptionsMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, SDL_Rect* cameraRect, TTF_Font* font);
	~OptionsMenu();

	int getBackCode();
	int getExitCode();
	void draw(SDL_Renderer* renderTarget);
	int showMenu(SDL_Renderer* renderTarget);
	int createMenu(SDL_Renderer* renderTarget);
	void toggleSound(SDL_Renderer* renderTarget);
};

#endif


