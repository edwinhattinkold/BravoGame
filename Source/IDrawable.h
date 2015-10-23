#pragma once
#include <SDL.h>
#include <iostream>

class DrawVisitor;

class IDrawable
{
public:
	virtual void Accept(DrawVisitor *dv);
	virtual void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
};