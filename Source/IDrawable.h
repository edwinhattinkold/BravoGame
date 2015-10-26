#pragma once
#include <SDL.h>
#include <iostream>

class DrawVisitor;

class IDrawable
{
public:
	virtual void accept(DrawVisitor *dv);
	virtual void draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
};