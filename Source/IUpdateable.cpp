#include "IUpdateable.h"
#include "UpdateVisitor.h"

void IUpdateable::accept( UpdateVisitor *uv )
{
	uv->visit( this );
}

void IUpdateable::update( float deltaTime, const Uint8 *keyState )
{
	std::cout << "Updating interface, this is not normal, should have been overriden!" << std::endl;
}