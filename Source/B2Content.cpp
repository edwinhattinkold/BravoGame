#include "B2Content.h"


B2Content::B2Content(b2World* world, SDL_Renderer* renderTarget, std::string filePath) :Sprite(renderTarget, filePath)
{

}


B2Content::~B2Content()
{
	m_body->GetWorld()->DestroyBody(m_body);
}

b2Vec2 B2Content::getB2DPosition(){
	return m_body->GetPosition();
}

b2Vec2 B2Content::getSDLPosition(){
	float x = m_body->GetPosition().x;
	float y = m_body->GetPosition().y * -1;
	return b2Vec2(x, y);
}

float B2Content::getAngle(){
	
	float degrees = 360 - m_body->GetAngle() * RADTODEG;
	//float degrees =  m_body->GetAngle() * RADTODEG;
	return degrees;
	/*
	int add360 = degrees + 360;
	int newAngle = 0;
	int gradenBox2d = add360 % 360;
	if (gradenBox2d < 90)
	{
		int temp = 90 - gradenBox2d;
		newAngle = 90 + temp;
	}
	if (gradenBox2d < 180)
	{
		int temp = gradenBox2d - 90;
		newAngle = 90 - temp;
	}
	if (gradenBox2d < 270)
	{
		int temp = 270 - gradenBox2d;
		newAngle = 270 + temp;
	}
	else{
		int temp = gradenBox2d - 270;
		newAngle = 270 - temp;
	}
	float newNewAngle = newAngle % 360;*/
	
}

void B2Content::accept(DrawVisitor *dv)
{
	dv->visit(this);
}