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
	B2Content* objectOne = (B2Content*) contact->GetFixtureA()->GetBody()->GetUserData();
	B2Content* objectTwo = (B2Content*) contact->GetFixtureB()->GetBody()->GetUserData();

	if( objectOne && objectTwo )
	{
		splitContacts( objectOne, objectTwo, objectOne->getObjectType() );
		splitContacts( objectTwo, objectOne, objectTwo->getObjectType() );
	}
}

void ContactHandler::EndContact( b2Contact* contact )
{

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
		case (Object_Collide) : {
			CollideObject* collider = (CollideObject*)otherObject;
			if (!projectile->isOnDeathRow)
			{
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
	if (otherObject->getObjectType() == Object_Tire || otherObject->getObjectType() == Object_Car)
	{
		handleCollectibleContact(collectible);
	}
	
}
void ContactHandler::handleCollectibleContact(Collectible* collectible){
	
	switch (collectible->myType)
	{
		case Collectible::Collectibletypes::Nitro:	
			if (!collectible->isOnDeathRow)
			{
				world->destroyCollectible(collectible);
				collectible->isOnDeathRow = true;
				this->world->getCar()->hitNitro(5.0f);
			}			
			break;
		case Collectible::Collectibletypes::Oil:			
				this->world->getCar()->hitOil(2.0f);			
			return;
			break;
		case Collectible::Collectibletypes::Gasoline:
			if (!collectible->isOnDeathRow)
			{
				world->destroyCollectible(collectible);
				collectible->isOnDeathRow = true;
				this->world->getCar()->addGasoline(4.0f);
			}
			break;
		default:
			if (!collectible->isOnDeathRow)
			{
				world->destroyCollectible(collectible);
				collectible->isOnDeathRow = true;
			}
			break;

	}
}