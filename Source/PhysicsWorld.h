#pragma once
#include <Box2D\Box2D.h>
#include <cmath>
#include <iostream>
#include<SDL.h>
//VOOR DE KEYSTATE NODIG !!
#include <SDL_image.h>
#include "TDCar.h"
#include "MyDestructionListener.h"

class PhysicsWorld
{
	/*
	b2World* m_world;
	b2Body* m_groundBody;
	//blokje
	TDCar* myCar;
	SDL_Scancode keys[4];
	
	int m_controlState;
	MyDestructionListener m_destructionListener;


	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

public:
	b2Body* myBody;
	b2Body* dynamicBody;
	PhysicsWorld(){
		m_world = new b2World(b2Vec2(0, 0));
		m_world->SetGravity(b2Vec2(0, 0));
		m_world->SetDestructionListener(&m_destructionListener);


		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position.Set(-15, 15); //set the starting position
		myBodyDef.angle = 0; //set the starting angle

		dynamicBody = m_world->CreateBody(&myBodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(1, 1);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		dynamicBody->CreateFixture(&boxFixtureDef);




		//set up ground areas
		{
			b2BodyDef bodyDef;
			m_groundBody = m_world->CreateBody(&bodyDef);

			b2PolygonShape polygonShape;
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &polygonShape;
			fixtureDef.isSensor = true;

			polygonShape.SetAsBox(9, 7, b2Vec2(-10, 15), 20 * DEGTORAD);
			b2Fixture* groundAreaFixture = m_groundBody->CreateFixture(&fixtureDef);
			groundAreaFixture->SetUserData(new GroundAreaFUD(0.5f, false));

			polygonShape.SetAsBox(9, 5, b2Vec2(5, 20), -40 * DEGTORAD);
			groundAreaFixture = m_groundBody->CreateFixture(&fixtureDef);
			groundAreaFixture->SetUserData(new GroundAreaFUD(0.2f, false));
		}

		//m_tire = new TDTire(m_world);
		//m_tire->setCharacteristics(100, -20, 150);

		myCar = new TDCar(physi);

		m_controlState = 0;

		keys[0] = SDL_SCANCODE_W;
		keys[1] = SDL_SCANCODE_S;
		keys[2] = SDL_SCANCODE_A;
		keys[3] = SDL_SCANCODE_D;


	
		
	}
	~PhysicsWorld(){};

	void Run(){	
	}

	float getX(){
		//floats terug geven zodat je het kan schalen tijdens het renderen.
		return myCar->getPosition().x;

	}

	float getY(){
		//floats terug geven zodat je het kan schalen tijdens het renderen.
		return myCar->getPosition().y;
	}

	float getAngle(){
		return myCar->getAngle();
	}

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	void Update(float deltaTime, const Uint8 *keyState){
		//Auto updated
		//W
		if (keyState[keys[0]])
		{			
			m_controlState |= TDC_UP;		
		}
		else{
			m_controlState &= ~TDC_UP;
		}
		//S
		if (keyState[keys[1]])
		{
			m_controlState |= TDC_DOWN;
		}
		else{
			m_controlState &= ~TDC_DOWN;			
		}


		//A
		if (keyState[keys[2]])
		{
			m_controlState |= TDC_LEFT;
		}
		else{
			m_controlState &= ~TDC_LEFT;
		}

		//D
		if (keyState[keys[3]])
		{
			m_controlState |= TDC_RIGHT;
		}
		else{
			m_controlState &= ~TDC_RIGHT;
		}
	
		myCar->update(m_controlState);
		
		m_world->Step(deltaTime , velocityIterations, positionIterations);
		
		
		
		//std::cout << myCar->getAngle() << std::endl;
	}

	void handleContact(b2Contact* contact, bool began)
	{
		b2Fixture* a = contact->GetFixtureA();
		b2Fixture* b = contact->GetFixtureB();
		FixtureUserData* fudA = (FixtureUserData*)a->GetUserData();
		FixtureUserData* fudB = (FixtureUserData*)b->GetUserData();

		if (!fudA || !fudB)
			return;

		if (fudA->getType() == FUD_CAR_TIRE || fudB->getType() == FUD_GROUND_AREA)
			tire_vs_groundArea(a, b, began);
		else if (fudA->getType() == FUD_GROUND_AREA || fudB->getType() == FUD_CAR_TIRE)
			tire_vs_groundArea(b, a, began);
	}

	void BeginContact(b2Contact* contact) { handleContact(contact, true); }
	void EndContact(b2Contact* contact) { handleContact(contact, false); }

	void tire_vs_groundArea(b2Fixture* tireFixture, b2Fixture* groundAreaFixture, bool began)
	{
		TDTire* tire = (TDTire*)tireFixture->GetBody()->GetUserData();
		GroundAreaFUD* gaFud = (GroundAreaFUD*)groundAreaFixture->GetUserData();
		if (began)
			tire->addGroundArea(gaFud);
		else
			tire->removeGroundArea(gaFud);
	}





	

	// Hier overriden we de keyboard functie van testbed.
	//Hier kunnen we dus besturing in creëeren

	void HandleInput(int key){
		switch (key) {
		case 1: m_controlState |= TDC_LEFT; break;
		case 2: m_controlState |= TDC_RIGHT; break;
		case 3: m_controlState |= TDC_UP; break;
		case 4: m_controlState |= TDC_DOWN; break;

		case 5: m_controlState &= ~TDC_LEFT; break;
		case 6: m_controlState &= ~TDC_RIGHT; break;
		case 7: m_controlState &= ~TDC_UP; break;
		case 8: m_controlState &= ~TDC_DOWN; break;
		}

	}
	*/

};

