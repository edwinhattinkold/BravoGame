#pragma once

#include <SDL.h>
class B2Content;
class IDrawable;
class TDCar;
class Tree;
class TDTire;
class Rect;
class HudObject;
class Hud;
class Projectile;
class Collectible;

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
	void visit(TDTire *tire);
	void visit(TDCar *car);
	void visit(Tree *tree);
	void visit( Rect *rect );
	void visit( HudObject *ho );
	void visit( Hud *hud );
	void visit(Collectible *collectible);
	void visit( Projectile *projectile );
};

