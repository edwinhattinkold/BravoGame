#include "ChasingTurretState.h"
#include "DeadTurretState.h"
#include "MovingTurret.h"
#include "RadarQueryCallback.h"
#include "ContactWrapper.h"
#include "IdleTurretState.h"
#include "RageTurretState.h"
ChasingTurretState::ChasingTurretState(MovingTurret* turret) :TurretState(turret){

}

ChasingTurretState::~ChasingTurretState(){}

void ChasingTurretState::checkState(){
	float distance = calculateDistance();
	if (turret->isDead()){
		turret->setState(new DeadTurretState(turret));
	}
	else if (distance < turret->getRange()){
		turret->setState(new RageTurretState((MovingTurret*)turret));
	}
	else if (distance >(turret->getRange() * 3)){
		turret->setState(new IdleTurretState(turret));
	}
}

void ChasingTurretState::update(float deltaTime){
	//Set asset to green ( calm turret )
	turret->setAsset(Asset_Turret_Calm);

	//Get all bodies in range
	float radius = 20;
	float carImportant = 10;
	float collideImportant = 8;
	b2Vec2 total(0, 0);
	std::vector<b2Body*> bodies;
	RadarQueryCallback raderCallback; //see "World querying topic"
	b2AABB aabb;
	aabb.lowerBound = turret->getB2DPosition() - b2Vec2(radius, radius);
	aabb.upperBound = turret->getB2DPosition() + b2Vec2(radius, radius);
	turret->getPhysicsWorld()->QueryAABB(&raderCallback, aabb);
	for (int i = 0; i < raderCallback.foundBodies.size(); i++) {
		b2Body* body = raderCallback.foundBodies[i];
		b2Vec2 bodyCom = body->GetPosition();
		ContactType type = ((ContactWrapper*)body->GetUserData())->getContactType();
		//ignore bodies outside the blast range
		if (!(type == Contact_Collectible || type == Contact_Car || type == Contact_Bullet || (bodyCom - turret->getB2DPosition()).Length() >= radius || body == turret->getBody())){
			b2Vec2 temp = bodyCom - turret->getB2DPosition();
			float length = temp.Length();
			temp.Normalize();
			temp = 10.0f / length * -1 * temp;
			total += temp;
		}
	}
	total.Normalize();
	b2Vec2 car = (turret->getCar()->getB2DPosition() - turret->getB2DPosition());
	car.Normalize();
	total += carImportant * car + collideImportant * total;
	total.Normalize();
	total = 12.0f * total;
	if (abs(total.x) < 0.3)
		total.x = 0;
	if (abs(total.y) < 0.3)
		total.y = 0;
	turret->getBody()->SetLinearVelocity(total);
	turret->getWeapon()->update(deltaTime);
}