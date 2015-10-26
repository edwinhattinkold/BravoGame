#include "DrawContainer.h"

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

void DrawContainer::Draw()
{
	for( size_t i = 0; i < objects->size(); i++ )
		objects->at( i )->Accept( dv );
}

void DrawContainer::Add( IDrawable *drawable )
{
	objects->push_back( drawable );
}

void DrawContainer::Remove( IDrawable *drawable )
{
	//std::vector<IDrawable>::iterator it;
	//it = std::find(objects->begin(), objects->end(), drawable);

	// swap the one to be removed with the last element
	// and remove the item at the end of the container
	//std::swap(*it, objects->back());
	//delete drawable;
	//objects->pop_back();
}
