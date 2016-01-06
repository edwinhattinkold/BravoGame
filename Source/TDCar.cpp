#include "TDCar.h"
#include "World.h"
#include "Camera.h"
#include "ContactWrapper.h"
#include "BaseLevel.h"
#include "LevelFactory.h"

ostream& operator<<(ostream& os, const TDCar& obj)
{
	obj.write_object( os );
	return os;
}

istream& operator>>(istream& is, TDCar& obj)
{
	obj.read_object( is );
	return is;
}

void TDCar::write_object( ostream& os ) const
{
	os << m_body->GetPosition().x << ' ' << m_body->GetPosition().y << ' ' << m_body->GetAngle() << ' ' << score << ' ' << health << '\n';
}

void TDCar::read_object( istream& is )
{
	float x;
	float y;
	float angle;
	is >> x >> y >> angle >> score >> health;
	m_body->SetTransform( b2Vec2( x, y ), angle );
	for( size_t i = 0; i < m_tires.size(); i++ )
	{
		m_tires.at( i )->m_body->SetTransform( b2Vec2( x, y ), angle );
	}
}

void TDCar::changeLevel( BaseLevel* level )
{
	if( this->level != level )
	{
		this->level->stopSound();
		this->level = level;
		this->level->startSound();
		world->hud->changeLevel( level->getName() );
	}

}

void TDCar::continueSound()
{
	this->level->startSound();
}


TDCar::~TDCar() {
	physicsWorld->DestroyJoint( flJoint);	flJoint = nullptr;
	physicsWorld->DestroyJoint( frJoint );	frJoint = nullptr;
	for (size_t i = 0; i < m_tires.size(); i++){
		delete m_tires[i];	m_tires[i] = nullptr;
	}
	delete weapon;		 weapon = nullptr;
}

TDCar::TDCar(World* world, b2World* physicsWorld, SDL_Renderer* renderTarget, Camera* camera, int widthM, int heightM)
	:B2Content( renderTarget, world, physicsWorld, Asset_Car ), Hittable( 2000, Asset_Car )
{
	oilTime = 0;
	this->camera = camera;
	objectType = Object_Car;
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Throttle,		SDL_SCANCODE_W } );
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Brakes,		SDL_SCANCODE_S } );
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Steer_Left,	SDL_SCANCODE_A } );
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Steer_Right,	SDL_SCANCODE_D } );
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Horn,			SDL_SCANCODE_H } );
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Shoot,		SDL_SCANCODE_SPACE } );
	level = LevelFactory::getInstance()->getLevel( "desert" );
	weapon = new MachineGun( world, this, physicsWorld, renderTarget );

	m_controlState = 0;
	w = widthM;
	h = heightM;
	score = 0;

	float secondsGasoline = 120.0f;
	gasoline = secondsGasoline * 1000.0f;
	maxGasoline = gasoline;

	soundWStarted = false;
	soundAStarted = false;
	soundALoopStarted = false;
	//create car body=
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	m_body = physicsWorld->CreateBody( &bodyDef );
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
	fixture = m_body->CreateFixture(&polygonShape, 0.1f);//shape, density

	
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
	float backTireMaxDriveForce = 60;
	float frontTireMaxDriveForce = 70;


	float backTireMaxLateralImpulse = 10.5;
	//Lager zodat hij kan driften.
	float frontTireMaxLateralImpulse = 9.5;

	//back left tire
	TDTire* tire = new TDTire(world, physicsWorld, renderTarget );
	tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
	jointDef.bodyB = tire->m_body;
	jointDef.localAnchorA.Set(-1.5, 0.875f);
	physicsWorld->CreateJoint( &jointDef );
	m_tires.push_back(tire);

	//back right tire
	tire = new TDTire(world, physicsWorld, renderTarget );
	tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
	jointDef.bodyB = tire->m_body;
	jointDef.localAnchorA.Set(1.5, 0.875f);
	physicsWorld->CreateJoint( &jointDef );
	m_tires.push_back(tire);

	//front left tire
	tire = new TDTire(world, physicsWorld, renderTarget );

	tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
	jointDef.bodyB = tire->m_body;
	jointDef.localAnchorA.Set(-1.5, 5.7f);
	flJoint = (b2RevoluteJoint*) physicsWorld->CreateJoint( &jointDef );
	m_tires.push_back(tire);

	//front right tire
	tire = new TDTire(world, physicsWorld, renderTarget );
	tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
	jointDef.bodyB = tire->m_body;
	jointDef.localAnchorA.Set(1.5, 5.7f);
	frJoint = (b2RevoluteJoint*) physicsWorld->CreateJoint( &jointDef );
	m_tires.push_back(tire);

	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), float(w), float(h), getAngleSDL());
	updateOrigin();
	setContactWrapper(new ContactWrapper(this));
}
float TDCar::getAngleB2D()
{
	return m_body->GetAngle()  * RADTODEG;
}

void TDCar::printFixtures()
{
	b2PolygonShape* polygonShape2 = (b2PolygonShape*)fixture->GetShape();
	int vertexCount = polygonShape2->GetVertexCount();
	for (int i = 0; i < vertexCount; ++i)
	{
		//get the vertex in body coordinates
		b2Vec2 bcVertex = polygonShape2->GetVertex(i);
		//get the vertex in world coordinates
		b2Vec2 wcVertex = fixture->GetBody()->GetWorldPoint(bcVertex);
	}
}
std::vector<TDTire*> TDCar::getTires()
{
	return m_tires;
}

void TDCar::hitOil(float time){
	oilTime = time;
	for (int c = 0; c < m_tires.size(); c++)
		m_tires[c]->oilMultiplier = 0.5f;
}

void TDCar::hitNitro(float time)
{
	nitroTime = time;
	for (int c = 0; c < m_tires.size(); c++)
		m_tires[c]->nitroMultiplier = 1.5f;
}

void TDCar::update( float deltaTime, const Uint8 *keyState )
{
	weapon->update( deltaTime );
	
	// AUTO BESTUREN
	//W
	if (keyState[keyMap.at(Car_Throttle)])
	{
		m_controlState |= TDC_UP;
		lowerGasoline(deltaTime);
		if (!soundWStarted)
		{
			soundAStarted = false;

			//Sound::getInstance()->stopSound(Sound_Skid);
			//Sound::getInstance()->playSound(Sound_Engine_Start);

			//Sound::getInstance()->stopSound(Sound_Engine_Loop);
			//Sound::getInstance()->playSoundLooping(Sound_Engine_Loop);
			soundWStarted = true;
			soundALoopStarted = true;
		}			
			
	}		
	else{
			soundWStarted = false;
		
		m_controlState &= ~TDC_UP;
	}
		
	if( keyState[keyMap.at( Car_Brakes )] )
	{
		m_controlState |= TDC_DOWN;
		lowerGasoline(deltaTime);
		if (!soundAStarted){
			//Sound::getInstance()->playSound(Sound_Skid);
			soundAStarted = true;
		}
		if (soundALoopStarted){
			//Sound::getInstance()->stopSound(Sound_Engine_Loop);
			soundALoopStarted = false;
		}		
	}		
	else
		m_controlState &= ~TDC_DOWN;

	if( keyState[keyMap.at( Car_Steer_Left )] )
		m_controlState |= TDC_LEFT;
	else
		m_controlState &= ~TDC_LEFT;

	if( keyState[keyMap.at( Car_Steer_Right )] )
		m_controlState |= TDC_RIGHT;
	else
		m_controlState &= ~TDC_RIGHT;

	if( keyState[keyMap.at( Car_Horn )] )
		soundHorn();

	if( keyState[keyMap.at( Car_Shoot )] )
		shoot();

	for (int i = 0; i < m_tires.size(); i++)
		m_tires[i]->updateFriction();
	for (int i = 0; i < m_tires.size(); i++)
		m_tires[i]->updateDrive(m_controlState, deltaTime);
	for (int i = 0; i < m_tires.size(); i++)
		m_tires[i]->updateTurn(m_controlState);

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

	updateSDLPosition( getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL() );
	updateOrigin();
	printFixtures();
	for (int c = 0; c < m_tires.size(); c++)
		m_tires[c]->update();
}


/*
De auto heeft voor x aantal seconden bezine.
De benzine wordt verlaagd door de tijd dat,
de gebruiker gas geeft.
*/
void TDCar::lowerGasoline(float deltaTime)
{
	if (gasoline > 0)
	{
		gasoline -= deltaTime * 1000.0f;
		if (gasoline < 0)
		{
			setSpeedMultiplier(0.5f);
			gasoline = 0;
		}
		
	}	
	if (oilTime > 0)
	{

		oilTime -= deltaTime;
		if (oilTime < 0)
		{
			for (int c = 0; c < m_tires.size(); c++)
				m_tires[c]->oilMultiplier = 1.0f;
			oilTime = 0;
		}
	}
	if (nitroTime > 0)
	{

		nitroTime -= deltaTime;
		if (nitroTime < 0)
		{
			for (int c = 0; c < m_tires.size(); c++)
				m_tires[c]->nitroMultiplier = 1.0f;
			nitroTime = 0;
		}
	}
}


/*
Snelheid van de auto instellen.
de snelheid wordt * de invoer gedaan.
voorbeeld 0.5f is halve snelheid.
*/
void TDCar::setSpeedMultiplier(float newMultiplier)
{

	for (size_t i = 0; i < m_tires.size(); i++)
		m_tires[i]->setMultiplier(newMultiplier);
}

//benzine toevoegen in secondes
void TDCar::addGasoline(float gasTime)
{
	if (gasoline < 1)
	{
		setSpeedMultiplier(1.0f);
	}
	if (gasoline < maxGasoline)
		gasoline += gasTime * 1000.0f;
	if (gasoline > maxGasoline)
		gasoline = maxGasoline;
}

// Percentage penzine dat over is
int TDCar::getGasoline()
{
	float onePercent = maxGasoline / 100;
	int currentGasPercentage = gasoline / onePercent;
	return currentGasPercentage;
}

void TDCar::accept(DrawVisitor *dv)
{
	dv->visit(this);
}

void TDCar::accept( UpdateVisitor *uv )
{
	uv->visit( this );
}

void TDCar::soundHorn(){
	Sound::getInstance()->playSound(Sound_Horn);
}

void TDCar::shoot()
{
	weapon->pullTrigger();
}

void TDCar::addScore( int amount )
{
	score += amount;
}

int TDCar::getScore()
{
	return score;
}