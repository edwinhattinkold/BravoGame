#pragma once
#include <SDL.h>

class Sprite;
class MapDrawer;
class IDrawable;

class DrawVisitor
{
private:
	SDL_Renderer *renderTarget;
	SDL_Rect *cameraRect;
public:
	DrawVisitor(SDL_Renderer *renderTarget, SDL_Rect *cameraRect);
	~DrawVisitor();

	void Visit(IDrawable *id);
	void Visit(MapDrawer *md);
	void Visit(Sprite *sp);

};

