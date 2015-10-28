#pragma once

#include <SDL.h>
class B2Content;
class IDrawable;
class TDCar;
class Tree;

class DrawVisitor
{
private:
	SDL_Renderer *renderTarget;
	SDL_Rect *cameraRect;
public:
	DrawVisitor(SDL_Renderer *renderTarget, SDL_Rect *cameraRect);
	~DrawVisitor();
	void visit(IDrawable *db);
	void visit(B2Content *content);
	void visit(TDCar *car);
	void visit(Tree *tree);
};

