#include "TDCar.h"
#include "World.h";

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


TDCar::~TDCar() {
	physicsWorld->DestroyJoint( flJoint);	flJoint = nullptr;
	physicsWorld->DestroyJoint( frJoint );	frJoint = nullptr;
	for (size_t i = 0; i < m_tires.size(); i++){
		delete m_tires[i];	m_tires[i] = nullptr;
	}
	delete weapon;		 weapon = nullptr;
}

TDCar::TDCar( World* world, b2World* physicsWorld, SDL_Renderer* renderTarget, int widthM, int heightM )
	:B2Content( renderTarget, world, physicsWorld, Asset_Car ), Hittable( 2000 )
{
	
	objectType = Object_Car;
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Throttle,		SDL_SCANCODE_W } );
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Brakes,		SDL_SCANCODE_S } );
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Steer_Left,	SDL_SCANCODE_A } );
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Steer_Right,	SDL_SCANCODE_D } );
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Horn,			SDL_SCANCODE_H } );
	keyMap.insert( std::pair<Car_Controls, SDL_Scancode>{ Car_Shoot,		SDL_SCANCODE_SPACE } );

	weapon = new MachineGun( world, this, physicsWorld, renderTarget );

	m_controlState = 0;
	w = widthM;
	h = heightM;
	score = 0;

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
	float maxForwardSpeed = 40;
	float maxBackwardSpeed = -25;
	float backTireMaxDriveForce = 300;
	float frontTireMaxDriveForce = 500;
	float backTireMaxLateralImpulse = 10.5;
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
	m_body->SetUserData(this);
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

void TDCar::update( float deltaTime, const Uint8 *keyState )
{
	weapon->update( deltaTime );

	// AUTO BESTUREN
	//W
	if (keyState[keyMap.at(Car_Throttle)])
	{
		m_controlState |= TDC_UP;
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

	updateSDLPosition( getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL() );
	updateOrigin();
	printFixtures();
	for (int c = 0; c < m_tires.size(); c++)
		m_tires[c]->update();
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