#include "Tree.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

Tree::Tree(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY)
	:B2Content(world, renderTarget, "Images/Objects/Tree.png"){
	w = widthM;
	h = heightM;
	//create car body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(posX, posY);
	m_body = world->CreateBody(&bodyDef);

	m_body->SetAngularDamping(3);
	
	b2Vec2 vertices[8];
	//het figuur van de auto.
	// W en h worden meegegeven door de user
	vertices[0].Set(w / 2, 0);
	vertices[1].Set(w / 2, h);
	vertices[2].Set(w, h);
	vertices[3].Set(-w / 2, 0);
	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 4);

	//Draaien
	m_body->SetTransform(m_body->GetPosition(), DEGTORAD * 0);
	b2Fixture* fixture = m_body->CreateFixture(&polygonShape, 0.1f);//shape, density
	
	updateSDLPosition(this->getSDLPosition().x, this->getSDLPosition().y, w, h, getAngle());

	
	updateOrigin();
}


Tree::~Tree()
{
}

b2Body * Tree::getBody()
{
	return m_body;
}

void Tree::accept(DrawVisitor *dv)
{
	dv->visit(this);
}

float Tree::getAngleB2D()
{
	return m_body->GetAngle();
}
