#include "UpdateContainer.h"


UpdateContainer::UpdateContainer()
{
	uv = new UpdateVisitor();
	objects = new std::vector<IUpdateable*>();
}


UpdateContainer::~UpdateContainer()
{
	delete uv;
	delete objects;
}

void UpdateContainer::Add( IUpdateable *updateable )
{
	objects->push_back( updateable );
}

void UpdateContainer::Remove( IUpdateable *updateable )
{
	std::vector<IUpdateable *>::iterator it;
	it = std::find( objects->begin(), objects->end(), updateable );

	// swap the one to be removed with the last element
	// and remove the item at the end of the container
	std::swap( *it, objects->back() );
	delete updateable;
	objects->pop_back();
}

void UpdateContainer::Update( float deltaTime, const Uint8* keyState )
{
	for( size_t c = 0; c < objects->size(); c++ )
	{
		objects->at( c )->Accept( uv, deltaTime, keyState );
	}
}
