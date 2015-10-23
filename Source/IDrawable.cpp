#include "IDrawable.h"
#include "DrawVisitor.h"

void IDrawable::Accept(DrawVisitor *dv){
	dv->Visit(this);
}

void IDrawable::Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect){
	std::cout << "Drawing interface, this is not normal!" << std::endl;
}