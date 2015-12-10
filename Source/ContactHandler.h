#pragma once
#include <Box2D/Box2D.h>
#include "B2Content.h"
#include "Radar.h"
class World;

class ContactHandler : public b2ContactListener
{
private:
	World* world;
	void BeginContact( b2Contact* contact );
	void EndContact( b2Contact* contact );
	void splitContacts( B2Content* object, B2Content* otherObject, ObjectTypes objectType );
	void bulletContact( Projectile* projectile, B2Content* otherObject );
	void collectibleContact(Collectible* collectible, B2Content* otherObject);
	void ContactHandler::handleContact(void* objectOne, void* objectTwo);
	void handleRadarContact(Radar* radar, B2Content* object);
	void handleRadarContactEnd(Radar* radar, B2Content* object);
public:
	ContactHandler( World* world );
	~ContactHandler();
};

