#pragma once
#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif
#define _USE_MATH_DEFINES

#include<iostream>
#include <cmath>
#include <Box2D/Box2D.h>
#include "TDTire.h"
#include <vector>
#include "B2Content.h"
#include <SDL.h>
#include <map>
#include "DrawContainer.h"
#include "UpdateContainer.h"
#include "Sound.h"
#include "Weapon.h"
#include <iostream>
#include "MachineGun.h"

class World;

std::ostream& operator<<(std::ostream& os, const TDCar& obj);
std::istream& operator>>(std::istream& is, TDCar& obj);

class TDCar : public B2Content, public b2ContactListener
{
	enum Car_Controls { Car_Throttle, Car_Brakes, Car_Steer_Left, Car_Steer_Right, Car_Horn, Car_Shoot };
	bool soundWStarted;
	bool soundAStarted;
	bool soundALoopStarted;
	std::map<Car_Controls, SDL_Scancode> keyMap;
	SDL_Scancode keys[5];
	
	std::vector<TDTire*> m_tires;
	b2RevoluteJoint *flJoint, *frJoint;
	int m_controlState;
	Weapon* weapon;

public:
	
	TDCar( World* world, b2World* physicsWorld, SDL_Renderer* renderTarget, int widthM, int heightM );
	~TDCar();

	virtual void update( float deltaTime, const Uint8 *keyState );
	virtual void accept( DrawVisitor *dv );
	virtual void accept( UpdateVisitor *dv );
	void soundHorn();
	void printFixtures();
	float getAngleB2D();
	
	std::vector<TDTire*> getTires();
	void shoot();

	void write_object( std::ostream& os ) const;
	void read_object( std::istream& is );
};



