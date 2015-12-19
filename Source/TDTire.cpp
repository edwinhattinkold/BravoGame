#include "TDTire.h"
#include "ContactWrapper.h"
TDTire::TDTire( World* world, b2World* physicsWorld, SDL_Renderer * renderTarget)
	:B2Content( renderTarget, world, physicsWorld, Asset_Tire)
{
	objectType = Object_Tire;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	m_body = physicsWorld->CreateBody( &bodyDef );

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.25f,0.675f);
	fixture = m_body->CreateFixture(&polygonShape, 1);//shape, density
	ctfud = new CarTireFUD();
	oilMultiplier = 1;
	fixture->SetUserData(ctfud);
	w = 0.75f;
	h = 1.625f;
	m_body->SetUserData(new ContactWrapper(this));
	m_currentTraction = 1;
	multiplierSpeed = 1.0f;
	nitroMultiplier = 1.0f;
	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());
}

/*
Snelheid van de auto instellen.
de snelheid wordt * de invoer gedaan.
voorbeeld 0.5f is halve snelheid.
*/
void TDTire::setMultiplier(float newMultiplierSpeed)
{
	multiplierSpeed = newMultiplierSpeed;
}

TDTire::~TDTire()
{
	m_groundAreas.clear();
	delete ctfud; ctfud = nullptr;
}

void TDTire::update()
{
	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());
}


void TDTire::accept(DrawVisitor *dv)
{
	dv->visit(this);
}

void TDTire::updateTraction()
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
b2Vec2 TDTire::getLateralVelocity() {
	b2Vec2 currentRightNormal = m_body->GetWorldVector(b2Vec2(1, 0));
	return b2Dot(currentRightNormal, m_body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 TDTire::getForwardVelocity() {
	b2Vec2 currentForwardNormal = m_body->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentForwardNormal, m_body->GetLinearVelocity()) * currentForwardNormal;
}

void TDTire::updateFriction() {
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

void TDTire::updateDrive(int controlState, float detlatime) {

	//find desired speed
	float desiredSpeed = 0;
	switch (controlState & (TDC_UP | TDC_DOWN)) {
	case TDC_UP:   desiredSpeed = m_maxForwardSpeed;  break;
	case TDC_DOWN: desiredSpeed = m_maxBackwardSpeed; break;
	default: return;//do nothing
	}

	//find current speed in forward direction
	//parameter is een standaard vec die naar boven wijst
	b2Vec2 currentForwardNormal = m_body->GetWorldVector(b2Vec2(0, 1));
	//het dot product van forwardvelocity , current forwardnormal.
	float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

	//apply necessary force m_maxDriveForce bepaald hoe snel hij optrekt.
	float force = 0;
	if (desiredSpeed > currentSpeed)
		force = m_maxDriveForce * multiplierSpeed  * oilMultiplier * nitroMultiplier;
	else if (desiredSpeed < currentSpeed)
		force = -(m_maxDriveForce * multiplierSpeed * oilMultiplier * nitroMultiplier);
	else
		return;
	m_body->ApplyForce(m_currentTraction * force * currentForwardNormal, m_body->GetWorldCenter(), true);
}
void TDTire::updateTurn(int controlState) {
	float desiredTorque = 0;
	switch (controlState & (TDC_LEFT | TDC_RIGHT)) {
	case TDC_LEFT:  desiredTorque = 15;  break;
	case TDC_RIGHT: desiredTorque = -15; break;
	default:;//nothing
	}
	m_body->ApplyTorque(desiredTorque, true);
}