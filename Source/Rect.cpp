#include "Rect.h"
#include "DrawVisitor.h"
#include "UpdateVisitor.h"


Rect::Rect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = width;
	rect->h = height;

	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}


Rect::~Rect()
{
	delete rect;		rect = nullptr;
}

void Rect::setColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Rect::accept( DrawVisitor *dv )
{
	dv->visit( this );
}

void Rect::draw( SDL_Renderer *renderTarget)
{
	SDL_SetRenderDrawColor( renderTarget, r, g, b, a );
	SDL_RenderFillRect( renderTarget, rect );
}
