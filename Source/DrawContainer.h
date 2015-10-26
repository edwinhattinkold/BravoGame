#pragma once
#include <SDL.h>
#include <vector>
#include "IDrawable.h"
#include "DrawVisitor.h"

class DrawContainer
{
private:
	std::vector<IDrawable*> *objects;
	DrawVisitor *dv;
public:
	DrawContainer(SDL_Renderer *renderTarget, SDL_Rect *cameraRect);
	~DrawContainer();

	void draw();
	void add(IDrawable *drawable);
	void remove(IDrawable *drawable);
};

