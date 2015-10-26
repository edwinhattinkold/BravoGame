#pragma once

#include <SDL.h>

class IDrawable;

class DrawVisitor
{
private:
	SDL_Renderer *renderTarget;
	SDL_Rect *cameraRect;
public:
	DrawVisitor(SDL_Renderer *renderTarget, SDL_Rect *cameraRect);
	~DrawVisitor();
	void visit(IDrawable *id);
};

