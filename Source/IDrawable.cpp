#include "IDrawable.h"
#include "DrawVisitor.h"

void IDrawable::accept( DrawVisitor *dv )
{
	dv->visit( this );
}

void IDrawable::draw( SDL_Renderer *renderTarget, SDL_Rect cameraRect )
{}