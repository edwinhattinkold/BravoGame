#include "Radar.h"

Radar::Radar(B2Content* host, float range, b2World* physics){
	this->host = host;
	this->world = physics;
	circleShape.m_radius = range;
	fixtureDef.shape = &circleShape;
	fixtureDef.isSensor = true;
	fixtureDef.density = 0;
	bodyDef.type = b2_dynamicBody;
	bodyDef.angle = 0;
	bodyDef.position = host->getB2DPosition();
	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	contactable = new Contactable(this);
	body->SetUserData(contactable);

	body->SetLinearVelocity(b2Vec2(-10, 0));
}


void Radar::update(){
	//body->SetTransform(host->getB2DPosition(), 0);
}

Radar::~Radar(){
	delete contactable;		contactable = nullptr;
}

void Radar::addObject(B2Content* obj){
	foundObjects.push_back(obj);
}

void Radar::removeObject(B2Content* obj){
	foundObjects.erase(std::remove(foundObjects.begin(), foundObjects.end(), obj), foundObjects.end());
}