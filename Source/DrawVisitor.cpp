#include "DrawVisitor.h"
#include <iostream>

#include "MapDrawer.h"
#include "Sprite.h"
#include "TDCar.h"

DrawVisitor::DrawVisitor( SDL_Renderer *renderTarget, SDL_Rect *cameraRect )
{
	this->renderTarget = renderTarget;
	this->cameraRect = cameraRect;
}


DrawVisitor::~DrawVisitor()
{}

void DrawVisitor::visit(IDrawable *db)
{
	db->draw(renderTarget, *cameraRect);
}

void DrawVisitor::visit(TDCar *car)
{
	car->drawEx(renderTarget, *cameraRect);
}