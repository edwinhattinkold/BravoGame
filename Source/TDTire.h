#pragma once

#include <Box2D/Box2D.h>
#include "GroundAreaFud.h"
#include "CarTireFud.h"
#include "B2Content.h"
#include <set>
enum {
	TDC_LEFT = 0x1,
	TDC_RIGHT = 0x2,
	TDC_UP = 0x4,
	TDC_DOWN = 0x8
};

class TDTire : public B2Content
{
public:
	CarTireFUD *ctfud;
	float m_maxForwardSpeed;
	float m_maxBackwardSpeed;
	float m_maxDriveForce;
	float m_maxLateralImpulse;
	std::set<GroundAreaFUD*> m_groundAreas;
	float m_currentTraction;
	float multiplierSpeed;

	~TDTire();
	TDTire( World* world, b2World* physicsWorld, SDL_Renderer * renderTarget );

	void setCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse) {
		m_maxForwardSpeed = maxForwardSpeed;
		m_maxBackwardSpeed = maxBackwardSpeed;
		m_maxDriveForce = maxDriveForce;
		m_maxLateralImpulse = maxLateralImpulse;
	}


	
	void setMultiplier(float);
	//Voor het toevoegen van verschillende ondergonden.
	void addGroundArea(GroundAreaFUD* ga) { m_groundAreas.insert(ga); updateTraction(); }
	void removeGroundArea(GroundAreaFUD* ga) { m_groundAreas.erase(ga); updateTraction(); }
	//Aanpassen van de grip
	void updateTraction();
	

	b2Vec2 getLateralVelocity();
	b2Vec2 getForwardVelocity();

	void updateFriction();
	void updateDrive(int controlState, float detlatime);
	void updateTurn(int controlState);
	void update();
	virtual void accept(DrawVisitor *dv);
};

