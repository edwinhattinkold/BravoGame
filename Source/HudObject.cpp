#include "HudObject.h"


HudObject::HudObject( SDL_Renderer* renderTarget, Asset asset ) :Sprite( renderTarget, asset )
{}


HudObject::~HudObject()
{}

void HudObject::accept( DrawVisitor *dv )
{
	dv->visit( this );
}
