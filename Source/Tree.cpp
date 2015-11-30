#include "Tree.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

Tree::Tree(b2World* world, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY)
	:B2Content(renderTarget, Asset_Tree), Hittable(1000){
	objectType = Object_Tree;
	w = widthM;
	h = heightM;
	//create car body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	bodyDef.position.Set(posX, posY);
	m_body = world->CreateBody(&bodyDef);

	m_body->SetAngularDamping(3);
	
	b2Vec2 vertices[8];
	//het figuur van de auto.
	// W en h worden meegegeven door de user
	vertices[0].Set(w / 2, 0);
	vertices[1].Set(w / 2, h);
	vertices[2].Set(-w / 2, h);
	vertices[3].Set(-w / 2, 0);
	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 4);

	//Draaien
	m_body->SetTransform(m_body->GetPosition(), DEGTORAD * 0);
	fixture = m_body->CreateFixture(&polygonShape, 0.8f);//shape, density
	

	updateSDLPosition(getCenterXSDL(), getCenterYSDL(), getSDLWidth(), getSDLHeight(), getAngleSDL());
	updateOrigin();

	m_body->SetUserData( this );
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