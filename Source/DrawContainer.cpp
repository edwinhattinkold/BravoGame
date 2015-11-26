#include "DrawContainer.h"
#include <algorithm>

DrawContainer::DrawContainer( SDL_Renderer *renderTarget, SDL_Rect *cameraRect )
{
	dv = new DrawVisitor( renderTarget, cameraRect );
	objects = new std::vector<IDrawable*>();
}


DrawContainer::~DrawContainer()
{
	delete dv;
	delete objects;
}

void DrawContainer::draw()
{
	for( size_t i = 0; i < objects->size(); i++ )
		objects->at( i )->accept( dv );
}

void DrawContainer::add( IDrawable *drawable )
{
	objects->push_back( drawable );
}

void DrawContainer::remove( IDrawable *drawable )
{
	objects->erase( std::remove( objects->begin(), objects->end(), drawable ), objects->end() );
}
