#pragma once
#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif
#define _USE_MATH_DEFINES

#include <iostream>
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
#include "Hittable.h"

class World;
class Camera;

std::ostream& operator<<(std::ostream& os, const TDCar& obj);
std::istream& operator>>(std::istream& is, TDCar& obj);

class TDCar : public B2Content, public b2ContactListener, public Hittable
{
	enum Car_Controls { Car_Throttle, Car_Brakes, Car_Steer_Left, Car_Steer_Right, Car_Horn, Car_Shoot };
	bool soundWStarted;
	bool soundAStarted;
	bool soundALoopStarted;
	std::map<Car_Controls, SDL_Scancode> keyMap;

	std::vector<TDTire*> m_tires;
	b2RevoluteJoint *flJoint, *frJoint;
	int m_controlState;
	Weapon* weapon;
	Camera* camera;

	int score;
	float gasoline;
	float nitroTime;
	float maxGasoline;
	float oilTime;
	
	

public:
	
	TDCar( World* world, b2World* physicsWorld, SDL_Renderer* renderTarget, Camera* camera, int widthM, int heightM );
	~TDCar();

	virtual void update( float deltaTime, const Uint8 *keyState );
	virtual void accept( DrawVisitor *dv );
	virtual void accept( UpdateVisitor *dv );
	void soundHorn();
	void printFixtures();
	void hitOil(float);
	void hitNitro(float);
	float getAngleB2D();
	int getGasoline();
	void lowerGasoline(float deltaTime);
	std::vector<TDTire*> getTires();
	void addGasoline(float);
	void setSpeedMultiplier(float);
	void shoot();

	void write_object( std::ostream& os ) const;
	void read_object( std::istream& is );

	void addScore( int amount );
	int getScore();
	void updateKeys(char);
	void checkCheats();
};



