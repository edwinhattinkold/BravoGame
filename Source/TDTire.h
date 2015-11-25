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

class TDTire : public B2Content, public b2ContactListener
{
public:
	CarTireFUD *ctfud;
	float m_maxForwardSpeed;
	float m_maxBackwardSpeed;
	float m_maxDriveForce;
	float m_maxLateralImpulse;
	std::set<GroundAreaFUD*> m_groundAreas;
	float m_currentTraction;

	~TDTire();
	TDTire(b2World* world, SDL_Renderer * renderTarget);

	void setCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse) {
		m_maxForwardSpeed = maxForwardSpeed;
		m_maxBackwardSpeed = maxBackwardSpeed;
		m_maxDriveForce = maxDriveForce;
		m_maxLateralImpulse = maxLateralImpulse;
	}

	void addGroundArea(GroundAreaFUD* ga) { m_groundAreas.insert(ga); updateTraction(); }
	void removeGroundArea(GroundAreaFUD* ga) { m_groundAreas.erase(ga); updateTraction(); }
	
	void updateTraction()
	{
		if (m_groundAreas.empty())
			m_currentTraction = 1;
		else {
			//find area with highest traction
			m_currentTraction = 0;
			std::set<GroundAreaFUD*>::iterator it = m_groundAreas.begin();
			while (it != m_groundAreas.end()) {
				GroundAreaFUD* ga = *it;
				if (ga->frictionModifier > m_currentTraction)
					m_currentTraction = ga->frictionModifier;
				++it;
			}
		}
	}

	b2Vec2 getLateralVelocity() {
		b2Vec2 currentRightNormal = m_body->GetWorldVector(b2Vec2(1, 0));
		return b2Dot(currentRightNormal, m_body->GetLinearVelocity()) * currentRightNormal;
	}

	b2Vec2 getForwardVelocity() {
		b2Vec2 currentForwardNormal = m_body->GetWorldVector(b2Vec2(0, 1));
		return b2Dot(currentForwardNormal, m_body->GetLinearVelocity()) * currentForwardNormal;
	}

	void updateFriction() {
		//lateral linear velocity
		b2Vec2 impulse = m_body->GetMass() * -getLateralVelocity();
		if (impulse.Length() > m_maxLateralImpulse)
			impulse *= m_maxLateralImpulse / impulse.Length();
		m_body->ApplyLinearImpulse(m_currentTraction * impulse, m_body->GetWorldCenter(), true);

		//angular velocity
		m_body->ApplyAngularImpulse(m_currentTraction * 0.1f * m_body->GetInertia() * -m_body->GetAngularVelocity(), true);

		//forward linear velocity
		b2Vec2 currentForwardNormal = getForwardVelocity();
		float currentForwardSpeed = currentForwardNormal.Normalize();
		float dragForceMagnitude = -2 * currentForwardSpeed;
		m_body->ApplyForce(m_currentTraction * dragForceMagnitude * currentForwardNormal, m_body->GetWorldCenter(), true);
	}


	void updateDrive(int controlState) {

		//find desired speed
		float desiredSpeed = 0;
		switch (controlState & (TDC_UP | TDC_DOWN)) {
		case TDC_UP:   desiredSpeed = m_maxForwardSpeed;  break;
		case TDC_DOWN: desiredSpeed = m_maxBackwardSpeed; break;
		default: return;//do nothing
		}

		//find current speed in forward direction
		b2Vec2 currentForwardNormal = m_body->GetWorldVector(b2Vec2(0, 1));
		float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

		//apply necessary force
		float force = 0;
		if (desiredSpeed > currentSpeed)
			force = m_maxDriveForce;
		else if (desiredSpeed < currentSpeed)
			force = -m_maxDriveForce;
		else
			return;
		m_body->ApplyForce(m_currentTraction * force * currentForwardNormal, m_body->GetWorldCenter(), true);
	}

	void updateTurn(int controlState) {
		float desiredTorque = 0;
		switch (controlState & (TDC_LEFT | TDC_RIGHT)) {
		case TDC_LEFT:  desiredTorque = 15;  break;
		case TDC_RIGHT: desiredTorque = -15; break;
		default:;//nothing
		}
		m_body->ApplyTorque(desiredTorque, true);
	}

	void update();
	virtual void accept(DrawVisitor *dv);

	virtual void BeginContact( b2Contact* contact );
	virtual void EndContact( b2Contact* contact );
};

