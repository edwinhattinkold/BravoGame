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

class TDCar : public B2Content
{
	TDTire* tireLEFT;
	std::vector<TDTire*> m_tires;
	b2RevoluteJoint *flJoint, *frJoint;
	
public:
	int w, h;
	TDCar(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM);

	~TDCar();

	void update(int controlState);
	virtual void accept(DrawVisitor *dv);
	//custom
};

