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

	void Draw();
	void Add(IDrawable *drawable);
	void Remove(IDrawable *drawable);
};

