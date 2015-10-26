#pragma once
#include "IDrawable.h"
#include <SDL.h>
class DrawFactory
{
private:
	DrawFactory() {}
	DrawFactory(DrawFactory const&);		// Don't Implement
	void operator=(DrawFactory const&);		// Don't implement

	SDL_Renderer *renderTarget;
	SDL_Rect *cameraRect;
public:
	~DrawFactory();
	//static DrawFactory& getInstance();
	//static IDrawable Create(std::string name);
};