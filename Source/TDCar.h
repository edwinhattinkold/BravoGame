#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <Box2D/Box2D.h>
#include "TDTire.h"
#include<vector>
#include "Sprite.h"
#include <SDL.h>
#include "DrawContainer.h"

#include<iostream>
#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

#include "IUpdateable.h"

class TDCar : public Sprite
{
	b2Body* m_body;
	TDTire* tireLEFT;
	std::vector<TDTire*> m_tires;
	b2RevoluteJoint *flJoint, *frJoint;
	
public:
	int w, h;
	TDCar(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM)
		:Sprite(renderTarget, "Images/Car/Car.png"){
		w = widthM;
		h = heightM;
		//create car body
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		m_body = world->CreateBody(&bodyDef);
		m_body->SetAngularDamping(3);

		b2Vec2 vertices[8];
		/*
		vertices[0].Set(1.5, 0);
		vertices[1].Set(3, 2.5);
		vertices[2].Set(2.8, 5.5);
		vertices[3].Set(1, 10);
		vertices[4].Set(-1, 10);
		vertices[5].Set(-2.8, 5.5);
		vertices[6].Set(-3, 2.5);
		vertices[7].Set(-1.5, 0);
		*/
		vertices[0].Set(w/2, 0);
		vertices[1].Set(w/2, h);
		vertices[2].Set(-w/2, h);
		vertices[3].Set(-w/2, 0);
		b2PolygonShape polygonShape;
		polygonShape.Set(vertices, 4);
		b2Fixture* fixture = m_body->CreateFixture(&polygonShape, 0.1f);//shape, density

		//prepare common joint parameters
		b2RevoluteJointDef jointDef;
		jointDef.bodyA = m_body;
		jointDef.enableLimit = true;
		jointDef.lowerAngle = 0;
		jointDef.upperAngle = 0;
		jointDef.localAnchorB.SetZero();//center of tire

		// standaard 250 aanpassen zodat de wagen niet mega snel gaat
		float maxForwardSpeed = 200;
		float maxBackwardSpeed = -200;
		float backTireMaxDriveForce = 300;
		float frontTireMaxDriveForce = 500;
		float backTireMaxLateralImpulse = 8.5;
		float frontTireMaxLateralImpulse = 7.5;

		//back left tire
		TDTire* tire = new TDTire(world);
		tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
		jointDef.bodyB = tire->m_body;
		jointDef.localAnchorA.Set(-3, 0.75f);
		world->CreateJoint(&jointDef);
		m_tires.push_back(tire);

		//back right tire
		tire = new TDTire(world);
		tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
		jointDef.bodyB = tire->m_body;
		jointDef.localAnchorA.Set(3, 0.75f);
		world->CreateJoint(&jointDef);
		m_tires.push_back(tire);

		//front left tire
		tire = new TDTire(world);
		tireLEFT = tire;
		tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
		jointDef.bodyB = tire->m_body;
		jointDef.localAnchorA.Set(-3, 8.5f);
		flJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
		m_tires.push_back(tire);

		//front right tire
		tire = new TDTire(world);
		tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
		jointDef.bodyB = tire->m_body;
		jointDef.localAnchorA.Set(3, 8.5f);
		frJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
		m_tires.push_back(tire);
		
		positionRect.x = this->getPosition().x * 20;
		positionRect.y = -this->getPosition().y * 20;
		positionRect.w = w * 20;
		positionRect.h = h * 20;
		angle = int(getAngle());
	}

	~TDCar() {
		for (int i = 0; i < m_tires.size(); i++)
			delete m_tires[i];
	}

	void update(int controlState) {
		for (int i = 0; i < m_tires.size(); i++)
			m_tires[i]->updateFriction();
		for (int i = 0; i < m_tires.size(); i++)
			m_tires[i]->updateDrive(controlState);

		//control steering
		float lockAngle = 35 * DEGTORAD;
		float turnSpeedPerSec = 160 * DEGTORAD;
		//from lock to lock in 0.5 sec
		float turnPerTimeStep = turnSpeedPerSec / 60.0f;
		float desiredAngle = 0;
		switch (controlState & (TDC_LEFT | TDC_RIGHT)) {
		case TDC_LEFT:  desiredAngle = lockAngle;  break;
		case TDC_RIGHT: desiredAngle = -lockAngle; break;
		default:;//nothing
		}
		float angleNow = flJoint->GetJointAngle();
		float angleToTurn = desiredAngle - angleNow;
		angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
		float newAngle = angleNow + angleToTurn;
		flJoint->SetLimits(newAngle, newAngle);
		frJoint->SetLimits(newAngle, newAngle);

		positionRect.x = this->getPosition().x * 20;
		positionRect.y = -this->getPosition().y * 20;
		angle = int(getAngle());
	}

	//custom
	b2Vec2 getPosition(){
		
		return m_body->GetPosition();
	}

	float getAngle(){
		
		float degrees = m_body->GetAngle() * 180 / M_PI;
		int add360 = degrees + 360;

		return add360 % 360;
	}

	virtual void accept(DrawVisitor *dv);
};

