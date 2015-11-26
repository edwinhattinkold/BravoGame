#include "UpdateVisitor.h"
#include "IUpdateable.h"
#include "Turret.h"

UpdateVisitor::UpdateVisitor()
{}


UpdateVisitor::~UpdateVisitor()
{}

void UpdateVisitor::visit( IUpdateable *ip, float deltaTime, const Uint8* keyState )
{
	//TODO: Input container
	ip->update( deltaTime, keyState );
}

void UpdateVisitor::visit(Turret* turret, float deltaTime, const Uint8 *keyState){
	
	turret->getState()->checkState();
	turret->getState()->update(deltaTime);
	turret->setB2DAngle(turret->turretAngle);
	turret->updateSDLPosition(turret->getCenterXSDL(), turret->getCenterYSDL(), turret->getSDLWidth(), turret->getSDLHeight(), turret->getAngleSDL());
}

