#include "DrawVisitor.h"
#include <iostream>

#include "MapDrawer.h"
#include "Sprite.h"

DrawVisitor::DrawVisitor(SDL_Renderer *renderTarget, SDL_Rect *cameraRect)
{
	this->renderTarget = renderTarget;
	this->cameraRect = cameraRect;
}

DrawVisitor::~DrawVisitor()
{

}

void DrawVisitor::Visit(IDrawable *id)
{
	id->Draw(renderTarget, *cameraRect);
}