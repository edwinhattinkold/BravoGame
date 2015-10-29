#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <Box2D/Box2D.h>
#include "TDTire.h"
#include <vector>
#include "B2Content.h"
#include <SDL.h>
#include "DrawContainer.h"

#include<iostream>
#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

#include "IUpdateable.h"
#include "Sound.h"

class TDCar : public B2Content
{

	SDL_Scancode keys[5];
	TDTire* tireLEFT;
	std::vector<TDTire*> m_tires;
	b2RevoluteJoint *flJoint, *frJoint;
	int m_controlState;
	
public:
	int w, h;
	TDCar(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM);

	~TDCar();

	void update(const Uint8 *keyState);
	void soundHorn();
	virtual void accept(DrawVisitor *dv);
	//custom
};

