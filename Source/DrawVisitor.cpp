#include "DrawVisitor.h"
#include <iostream>

#include "MapDrawer.h"
#include "Sprite.h"
#include "TDTire.h"
#include "TDCar.h"
#include "Tree.h"
#include "B2Content.h"
#include "Rect.h"
#include "HudObject.h"

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

void DrawVisitor::visit(B2Content *content)
{
	content->draw(renderTarget, *cameraRect);
}

void DrawVisitor::visit(Tree *tree){
	tree->drawTree(renderTarget, *cameraRect);
}

void DrawVisitor::visit(TDTire *tire){
	tire->drawTire(renderTarget, *cameraRect);
}

void DrawVisitor::visit(TDCar *car){
	car->drawCar(renderTarget, *cameraRect);
}

void DrawVisitor::visit( Rect *rect )
{
	rect->draw( renderTarget );
}

void DrawVisitor::visit( HudObject *ho)
{
	ho->draw( renderTarget);
}