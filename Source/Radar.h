#pragma once

#include <vector>
#include "B2Content.h"
#include "Contactable.h"

using namespace std;

class Radar{
private:
	vector<B2Content*>foundObjects;
	B2Content* host;
	b2CircleShape circleShape;
	b2FixtureDef fixtureDef;
	b2Body* body;
	b2World* world;
	b2BodyDef bodyDef;
	Contactable* contactable;
public:
	Radar(B2Content* host, float range, b2World* physics);
	~Radar();
	void update();
	void addObject(B2Content* obj);
	void removeObject(B2Content* obj);
	inline vector<B2Content*> getObjectsInRange(){
		return foundObjects;
	}
};