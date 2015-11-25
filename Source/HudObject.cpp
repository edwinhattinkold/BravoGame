#include "HudObject.h"


HudObject::HudObject( SDL_Renderer* renderTarget, std::string filePath ) :Sprite( renderTarget, filePath )
{}


HudObject::~HudObject()
{}

void HudObject::accept( DrawVisitor *dv )
{
	dv->visit( this );
}
