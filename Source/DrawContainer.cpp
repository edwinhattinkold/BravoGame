#include "DrawContainer.h"

DrawContainer::DrawContainer(SDL_Renderer *renderTarget, SDL_Rect *cameraRect)
{
	this->dv = new DrawVisitor(renderTarget, cameraRect);
	this->objects = new std::vector<IDrawable*>();
}


DrawContainer::~DrawContainer()
{
	delete dv;
	delete this->objects;
}

void DrawContainer::Draw(){
	for (size_t i = 0; i < objects->size(); i++)
		this->objects->at(i)->Accept(dv);
}

void DrawContainer::Add(IDrawable *drawable)
{
	this->objects->push_back(drawable);
}

void DrawContainer::Remove(IDrawable *drawable)
{
	//std::vector<IDrawable>::iterator it;
	//it = std::find(objects->begin(), objects->end(), drawable);

	// swap the one to be removed with the last element
	// and remove the item at the end of the container
	//std::swap(*it, objects->back());
	//delete drawable;
	//objects->pop_back();
}
