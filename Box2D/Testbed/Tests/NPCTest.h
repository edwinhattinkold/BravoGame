#pragma once

#include "C:\projects\BravoGame\Box2D\Testbed\Framework\Test.h"


class npcCar
{
	
public:
	b2BodyDef myBodyDef;
	b2Body* dynamicBody;
	npcCar(b2World* world , int x, int y)
	{
		
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position.Set(x, y); //set the starting position
		myBodyDef.angle = 0; //set the starting angle
		dynamicBody = world->CreateBody(&myBodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(1, 1);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		dynamicBody->CreateFixture(&boxFixtureDef);
	}


	void applyForce()
	{
		dynamicBody->ApplyForce(b2Vec2(0, 10), dynamicBody->GetWorldCenter(), true );
	}

	void applyForceLeft()
	{
		dynamicBody->ApplyForce(b2Vec2(0, 10), dynamicBody->GetWorldCenter(), true);
	}
	void goTo(int x, int y)
	{
		dynamicBody->SetLinearVelocity(b2Vec2(x, y));
	}

	void goToTarget(float x, float y)
	{ 
		//Snelheid van de vector instellen		
		float relativeSpeed = 10.0f;

		//X & Y van de vector instellen.
		float ownX = dynamicBody->GetWorldCenter().x;
		float ownY = dynamicBody->GetWorldCenter().y;

		//Doel vector berekenen.
		float vec1 = x - ownX;
		float vec2 = y - ownY;

		//Lengte van de vector berekenen.
		float length = sqrt(vec1 * vec1 + vec2 * vec2);

		//Vector normaliseren
		float normalizedX = vec1 /= length;
		float normalizedY = vec2 /= length;

		//De vector scalen.
		float xFinal = normalizedX *= relativeSpeed;
		float yFinal = normalizedY *= relativeSpeed;


		dynamicBody->SetLinearVelocity(b2Vec2(xFinal, yFinal));

	}

	b2Vec2 getPosition(){

		return dynamicBody->GetWorldCenter();
	}



};



class NPCTest : public Test
{
private:
	float x, y;
	float speedX, speedY;
	npcCar *m_car;
public:
	NPCTest::NPCTest()
	{
		m_world->SetGravity(b2Vec2(0, 0));
		m_world->SetDestructionListener(&m_destructionListener);
		x = 0;
		y = 0;
		speedY = 0;
		speedX = 0;
		m_car = new npcCar(m_world, 0, 0);
		

	}


	NPCTest::~NPCTest()
	{
		delete m_car;
	}

	

	void Step(Settings* settings)
	{
		Test::Step(settings);
		//show some useful info
		g_debugDraw.DrawString(5, m_textLine, "x:%.3f", m_car->getPosition().x);
		m_textLine += 15;
		g_debugDraw.DrawString(5, m_textLine, "y:%.3f", m_car->getPosition().y);
		m_textLine += 15;
		g_debugDraw.DrawString(5, m_textLine, "x:%.3f", x);
		m_textLine += 15;
		g_debugDraw.DrawString(5, m_textLine, "y:%.3f", y);
		m_textLine += 15;
		//m_car->goToTarget(x, y);
		m_car->goToTarget(m_mouseWorld.x, m_mouseWorld.y);
	}

	void Keyboard(int key)
	{
		
			switch (key) {
			case GLFW_KEY_A:
				updateX(false); break;
			case GLFW_KEY_D: 
				updateX(true); break;
			case GLFW_KEY_W: 
				updateY(true); break;
			case GLFW_KEY_S: 
				updateY(false);  break;
			case GLFW_KEY_E:
				m_car->applyForce();  break;
			case GLFW_KEY_Q:
				m_car->applyForceLeft();  break;
			default: Test::Keyboard(key);
			}
		
	}

	void updateSpeed(int iX, int iY)
	{

	}

	void updateX(bool direct)
	{

		if (direct)
			speedX += 1;
		else
			speedX -= 1;
		m_car->goTo(speedX, speedY);

	}

	void updateY(bool direct)
	{

		if (direct)
			speedY += 1;
		else
			speedY -= 1;
		m_car->goTo(speedX, speedY);
	}

	void MouseDown(const b2Vec2& p)
	{
		x = p.x;
		y = p.y;

		m_car->goToTarget(x, y);
	}



	
	static Test* Create()
	{
		return new NPCTest;
	}

};

