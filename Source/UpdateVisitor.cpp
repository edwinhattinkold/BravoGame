#include "UpdateVisitor.h"
#include "IUpdateable.h"
#include "TDCar.h"
#include "MapDrawer.h"
#include "Projectile.h"

UpdateVisitor::UpdateVisitor()
{

}


UpdateVisitor::~UpdateVisitor()
{

}

void UpdateVisitor::setDelta( float deltaTime )
{
	this->deltaTime = deltaTime;
}

void UpdateVisitor::setKeyState( const Uint8 *keyState )
{
	this->keyState = keyState;
}

/* Visit methods */
void UpdateVisitor::visit( IUpdateable *ip )
{
	ip->update( deltaTime, keyState );
}

void UpdateVisitor::visit( TDCar *car )
{
	car->update( deltaTime, keyState );
}

void UpdateVisitor::visit( MapDrawer *md )
{
	md->update( deltaTime, keyState );
}

void UpdateVisitor::visit( Projectile *projectile )
{
	projectile->update( deltaTime, keyState );
}