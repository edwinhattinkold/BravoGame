#include "UpdateContainer.h"
#include <algorithm>

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

void UpdateContainer::add( IUpdateable *updateable )
{
	objects->push_back( updateable );
}

void UpdateContainer::remove( IUpdateable *updateable )
{
	objects->erase( std::remove( objects->begin(), objects->end(), updateable ), objects->end() );
}

void UpdateContainer::update( float deltaTime, const Uint8* keyState )
{
	uv->setDelta( deltaTime );
	uv->setKeyState( keyState );
	for( size_t c = 0; c < objects->size(); c++ )
	{
		objects->at( c )->accept( uv );
	}
}
