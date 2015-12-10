#include "ContactHandler.h"
#include "World.h"


ContactHandler::ContactHandler(World* world)
{
	this->world = world;
}

ContactHandler::~ContactHandler()
{

}

void ContactHandler::BeginContact(b2Contact* contact)
{
	
	Contactable* objectOne = (Contactable*)contact->GetFixtureA()->GetBody()->GetUserData();
	Contactable* objectTwo = (Contactable*)contact->GetFixtureB()->GetBody()->GetUserData();
	if (objectOne->getType() == Type_Radar || objectTwo->getType() == Type_Radar)
		cout << "start radar \n";
	if (objectOne->getType() == Type_B2Content && objectTwo->getType() == Type_B2Content){
		B2Content* obj1 = (B2Content*)objectOne->getObject();
		B2Content* obj2 = (B2Content*)objectTwo->getObject();
		splitContacts(obj1, obj2, obj1->getObjectType());
		splitContacts(obj2, obj1, obj2->getObjectType());
	}
	else if (objectOne->getType() == Type_B2Content && objectTwo->getType() == Type_Radar){
		handleRadarContact((Radar*)objectTwo->getObject(), (B2Content*)objectOne->getObject());
	}
	else if (objectOne->getType() == Type_Radar && objectTwo->getType() == Type_B2Content){
		handleRadarContact((Radar*)objectOne->getObject(), (B2Content*)objectOne->getObject());
	}
}

void ContactHandler::handleRadarContact(Radar* radar, B2Content* object){
	//if (object->getObjectType() != Object_Projectile)
		radar->addObject(object);
}

void ContactHandler::handleRadarContactEnd(Radar* radar, B2Content* object){
	//if (object->getObjectType() != Object_Projectile)
		radar->removeObject(object);
}

void ContactHandler::EndContact( b2Contact* contact )
{
 	Contactable* objectOne = (Contactable*)contact->GetFixtureA()->GetBody()->GetUserData();
	Contactable* objectTwo = (Contactable*)contact->GetFixtureB()->GetBody()->GetUserData();
	if (objectOne->getType() == Type_Radar || objectTwo->getType() == Type_Radar)
		cout << "end radar \n";
	else{
		cout << "end b2content \n";
	}
	if (objectOne->getType() == Type_B2Content && objectTwo->getType() == Type_Radar){
		handleRadarContactEnd((Radar*)objectTwo->getObject(), (B2Content*)objectOne->getObject());
	}
	else if (objectOne->getType() == Type_Radar && objectTwo->getType() == Type_B2Content){
		handleRadarContactEnd((Radar*)objectOne->getObject(), (B2Content*)objectTwo->getObject());
	}
}

void ContactHandler::splitContacts( B2Content* object, B2Content* otherObject, ObjectTypes objectType )
{
	switch( objectType )
	{
		case (Object_Projectile) :
			bulletContact( (Projectile*) object, otherObject );
			break;
		case (Object_Collectible) :
			collectibleContact((Collectible*)object, otherObject);
			break;
		default:

			break;
	}
}



void ContactHandler::bulletContact( Projectile* projectile, B2Content* otherObject )
{
	switch( otherObject->getObjectType() )
	{
		case (Object_Tree):{
			Tree* tree = (Tree*)otherObject;
			if (!projectile->isOnDeathRow)
			{
				tree->takeDamage(projectile->getDamage());
				world->destroyProjectile(projectile);
				projectile->isOnDeathRow = true;

			}
			break;
		}
		case (Object_Turret):{
			Turret* turret = (Turret*)otherObject;
			if (!projectile->isOnDeathRow)
			{
				turret->takeDamage(projectile->getDamage());
				world->destroyProjectile(projectile);
				projectile->isOnDeathRow = true;
			}
			break;
		}
		case (Object_Car || Object_Tire) : {
			TDCar* car = (TDCar*)otherObject;
			if (!projectile->isOnDeathRow)
			{
				car->takeDamage( projectile->getDamage() );
				world->destroyProjectile(projectile);
				projectile->isOnDeathRow = true;
			}
			break;
		}
	}
}

void ContactHandler::collectibleContact(Collectible* collectible, B2Content* otherObject)
{
	switch (otherObject->getObjectType())
	{
	case(Object_Tire) :
		if (!collectible->isOnDeathRow)
		{
		world->destroyCollectible(collectible);
		collectible->isOnDeathRow = true;
		}
								 break;
	case(Object_Car) :
		if (!collectible->isOnDeathRow)
		{
		world->destroyCollectible(collectible);
		collectible->isOnDeathRow = true;
		}
					 break;
	}
}