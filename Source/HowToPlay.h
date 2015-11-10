#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Camera.h"
#include <vector>
#include "Sound.h"
#include "CustomCursor.h"
#include "MenuItem.h"
class HowToPlay
{
private:
	SDL_Rect backgroundImageRect;
	Camera* camera;
	SDL_Texture* backgroundImage;
	SDL_Event ev;
	std::vector<MenuItem*>* menuItems;
	Sound* sound;
	Uint32 time;
	int mouseX, mouseY, margin, combinedHeight;
	static enum Choices { Back, Exit };
	int optionsChoice, creditsChoice;
	void center();
	SDL_Texture* loadTexture(std::string filePath, SDL_Renderer *renderTarget);
public:
	HowToPlay(SDL_Renderer* renderTarget, Camera* camera, TTF_Font* font);
	~HowToPlay();

	int getBackCode();
	int getExitCode();
	void draw(SDL_Renderer* renderTarget);
	int showMenu(SDL_Renderer* renderTarget);
	int createMenu(SDL_Renderer* renderTarget);
	void getDesktopResolution(int& horizontal, int& vertical);
};