#include "DrawVisitor.h"
#include <iostream>

#include "MapDrawer.h"
#include "Sprite.h"
#include "TDTire.h"
#include "TDCar.h"
#include "Tree.h"
#include "Turret.h"
#include "B2Content.h"
#include "Rect.h"
#include "HudObject.h"
#include "Hud.h"
#include "Collectible.h"
#include "Explosion.h"

DrawVisitor::DrawVisitor( SDL_Renderer *renderTarget, SDL_Rect *cameraRect )
{
	this->renderTarget = renderTarget;
	this->cameraRect = cameraRect;
}

DrawVisitor::~DrawVisitor()
{

}

void DrawVisitor::visit(IDrawable *db)
{
	db->draw(renderTarget, *cameraRect);
}

void DrawVisitor::visit(B2Content *content)
{
	content->draw(renderTarget, *cameraRect);
}

void DrawVisitor::visit(Turret *turret){
	turret->drawWithAngle(renderTarget, *cameraRect);
	if (!turret->isDead())
		turret->drawHealthBar(renderTarget, cameraRect, turret->positionRect);
}

void DrawVisitor::visit(Tree *tree){
	tree->drawTree(renderTarget, *cameraRect);
	tree->drawHealthBar( renderTarget, cameraRect, tree->positionRect );
}

void DrawVisitor::visit(Collectible *collectible){

	collectible->drawCollectible(renderTarget, *cameraRect);
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

void DrawVisitor::visit( Hud *hud )
{
	hud->draw( renderTarget );
}

void DrawVisitor::visit( Projectile *projectile )
{
	projectile->drawProjectile( renderTarget, *cameraRect );
}

void DrawVisitor::visit(Explosion *explosion) 
{
	explosion->draw( renderTarget, *cameraRect );
}