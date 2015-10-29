#include "TDCar.h"

TDCar::~TDCar() {
	for (int i = 0; i < m_tires.size(); i++)
		delete m_tires[i];
}

TDCar::TDCar(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM)
	:B2Content(world, renderTarget, "Images/Car/buggy.png"){
	m_controlState = 0;
	w = widthM;
	h = heightM;
	//create car body=
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	

	m_body = world->CreateBody(&bodyDef);
	
	

	m_body->SetAngularDamping(3);
	
	b2Vec2 vertices[4];
	//het figuur van de auto.
	// W en h worden meegegeven door de user
	vertices[0].Set(w / 2, 0);
	vertices[1].Set(w / 2, h);
	vertices[2].Set(-w / 2, h);
	vertices[3].Set(-w / 2, 0);
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
	float maxForwardSpeed = 50;
	float maxBackwardSpeed = -30;
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

	//m_body->SetTransform(b2Vec2(60, -60), DEGTORAD * 180);

	updateSDLPosition(this->getSDLPosition().x, this->getSDLPosition().y, w, h, getAngle());
	updateOrigin();

	//toetsen instellen
	//vooruit
	keys[0] = SDL_SCANCODE_W;
	//achteruit
	keys[1] = SDL_SCANCODE_S;
	//links
	keys[2] = SDL_SCANCODE_A;
	//recht
	keys[3] = SDL_SCANCODE_D;
	//Toeter
	keys[4] = SDL_SCANCODE_H;

	std::cout << "Position: " << this->getB2DPosition().x << " - " << this->getB2DPosition().y << " Center: " << int(this->m_body->GetWorldCenter().x) << " - " << this->m_body->GetWorldCenter().y << std::endl;
}

void TDCar::update(const Uint8 *keyState) {

	// AUTO BESTUREN
	//W
	if (keyState[keys[0]])
		m_controlState |= TDC_UP;
	else
		m_controlState &= ~TDC_UP;

	//S
	if (keyState[keys[1]])
		m_controlState |= TDC_DOWN;
	else
		m_controlState &= ~TDC_DOWN;


	//A
	if (keyState[keys[2]])
		m_controlState |= TDC_LEFT;
	else
		m_controlState &= ~TDC_LEFT;

	//D
	if (keyState[keys[3]])
		m_controlState |= TDC_RIGHT;
	else
		m_controlState &= ~TDC_RIGHT;

	// !AUTO BESTUREN


	//Toeter
	if (keyState[keys[4]]){
		soundHorn();
	}
		


	for (int i = 0; i < m_tires.size(); i++)
		m_tires[i]->updateFriction();
	for (int i = 0; i < m_tires.size(); i++)
		m_tires[i]->updateDrive(m_controlState);

	//control steering
	float lockAngle = 35 * DEGTORAD;
	float turnSpeedPerSec = 160 * DEGTORAD;
	//from lock to lock in 0.5 sec
	float turnPerTimeStep = turnSpeedPerSec / 60.0f;
	float desiredAngle = 0;
	switch (m_controlState & (TDC_LEFT | TDC_RIGHT)) {
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

	float oldX = this->getSDLPosition().x;
	float newX = oldX - w/ 2;
	float oldY = this->getSDLPosition().y;
	float newY = oldY + h;
	updateSDLPosition(newX, newY);
	updateOrigin();

	std::cout << "Position: " << this->getB2DPosition().x << " - " << this->getB2DPosition().y << " Center: " << int(this->m_body->GetWorldCenter().x) << " - " << this->m_body->GetWorldCenter().y << std::endl;
	angle = int(getAngle());
}

void TDCar::accept(DrawVisitor *dv)
{
	dv->visit(this);
}


void TDCar::soundHorn(){
	Sound::getInstance()->playSound(Sound_Horn);
}
