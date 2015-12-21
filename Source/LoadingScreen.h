#pragma once
#include "SDL.h"
#include "Camera.h"
#include "SDL_ttf.h"

class LoadingScreen
{
private:
	SDL_Renderer* renderTarget;
	Camera* camera;
	TTF_Font* font;
	static enum Choices { Continue, Exit };
	int mouseX, mouseY;
	SDL_Event ev;

	SDL_Rect adRect;
	SDL_Texture* adImage;

	SDL_Rect maxLoading;
	SDL_Rect loaded;

	//other
	int prevTime;
	int currentTime;
	float deltaTime;

	float time;
	float passedTime;
public:
	LoadingScreen( SDL_Renderer* renderTarget, Camera* camera, TTF_Font* font );
	~LoadingScreen();

	int createMenu();
	int getExitCode();
};

