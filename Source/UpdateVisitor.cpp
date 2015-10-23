#include "UpdateVisitor.h"


UpdateVisitor::UpdateVisitor()
{
}


UpdateVisitor::~UpdateVisitor()
{
}

void UpdateVisitor::visit(Player *p, float deltaTime)
{
	//TODO: Input container
	p->Update(deltaTime, SDL_GetKeyboardState(NULL));
}
