#include "UpdateVisitor.h"
#include "IUpdateable.h"

UpdateVisitor::UpdateVisitor()
{}


UpdateVisitor::~UpdateVisitor()
{}

void UpdateVisitor::visit( IUpdateable *ip, float deltaTime, const Uint8* keyState )
{
	ip->update( deltaTime, keyState );
}