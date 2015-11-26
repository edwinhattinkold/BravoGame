#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <Box2D/Box2D.h>
#include<vector>
#include "Sprite.h"
#include <SDL.h>
#include "DrawContainer.h"
#include "UpdateContainer.h"
#include <string>

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif
const int sdlScale = 20;
class B2Content : public Sprite
{
	
private:
	int transform(float dgrs);
public:
	b2Body* m_body;
	float w, h;
	b2Fixture* fixture;
	B2Content( SDL_Renderer* renderTarget, std::string filePath);
	~B2Content();
	//custom
	b2Vec2 getB2DPosition();
	void setB2DPosition( b2Vec2 position );
	b2Vec2 getB2DDirectionalVector();
	b2Vec2 getSDLPosition();
	b2Vec2 getSDLDirectionalVector();
	float getAngleSDL();

	float getCenterXSDL();
	float getCenterYSDL();
	float getSDLWidth();
	float getSDLHeight();
};

