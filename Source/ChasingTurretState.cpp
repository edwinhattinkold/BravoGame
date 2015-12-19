#include "ChasingTurretState.h"
#include "DeadTurretState.h"
#include "MovingTurret.h"
#include "RadarQueryCallback.h"
#include "ContactWrapper.h"
ChasingTurretState::ChasingTurretState(MovingTurret* turret) :TurretState(turret){

}

ChasingTurretState::~ChasingTurretState(){}

void ChasingTurretState::checkState(){
	if (turret->isDead()){
		turret->setState(new DeadTurretState(turret));
	}
}

void ChasingTurretState::update(float deltaTime){
	//Set asset to green ( calm turret )
	turret->setAsset(Asset_Turret_Calm);

	//Get all bodies in range
	float radius = 15;
	float carImportant = 1;
	float collideImportant = -3;
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
		if (type == Contact_Car ||(bodyCom - turret->getB2DPosition()).Length() >= radius)
			continue;

		bodies.push_back(body);
	}
	for (size_t c = 0; c < bodies.size(); c++){
		total += collideImportant * (bodies[c]->GetPosition() - turret->getB2DPosition());
	}
	total += carImportant * (turret->getCar()->getB2DPosition() - turret->getB2DPosition());
	total.Normalize();
	
	total = 6.0f * total;
	if (abs(total.x) < 0.3)
		total.x = 0;
	if (abs(total.y) < 0.3)
		total.y = 0;
	turret->getBody()->SetLinearVelocity(total);
	turret->getWeapon()->update(deltaTime);
}