#include "IUpdateable.h"
#include "UpdateVisitor.h"

void IUpdateable::Accept(UpdateVisitor *uv, float deltaTime, const Uint8 *keyState){
	uv->Visit(this, deltaTime, keyState);
}

void IUpdateable::Update(float deltaTime, const Uint8 *keyState){
	std::cout << "Updating interface, this is not normal, should have been overriden!" << std::endl;
}