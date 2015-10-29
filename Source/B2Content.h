#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <Box2D/Box2D.h>
#include<vector>
#include "Sprite.h"
#include <SDL.h>
#include "DrawContainer.h"
#include <string>

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

class B2Content : public Sprite
{
	

public:
	b2Body* m_body;
	B2Content(b2World* world, SDL_Renderer* renderTarget, std::string filePath);
	~B2Content();
	//custom
	b2Vec2 getB2DPosition();
	b2Vec2 getSDLPosition();
	float getAngle();

	virtual void accept(DrawVisitor *dv);

};

