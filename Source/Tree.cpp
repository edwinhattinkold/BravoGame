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
	fixture = m_body->CreateFixture(&polygonShape, 0.8f);//shape, density
	
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


float Tree::getCenterX()
{
	float xCenter = 0;
	float yCenter = 0;
	b2PolygonShape* polygonShape2 = (b2PolygonShape*)fixture->GetShape();
	float vertexCount = polygonShape2->GetVertexCount();
	for (int i = 0; i < vertexCount; ++i)
	{
		//get the vertex in body coordinates
		b2Vec2 bcVertex = polygonShape2->GetVertex(i);
		//get the vertex in world coordinates
		b2Vec2 wcVertex = fixture->GetBody()->GetWorldPoint(bcVertex);
		xCenter += wcVertex.x;
		yCenter += wcVertex.y;
		std::cout << wcVertex.x << " " << wcVertex.y << std::endl;
	}
	return xCenter / 4;
}

float Tree::getCenterY()
{
	float xCenter = 0;
	float yCenter = 0;
	b2PolygonShape* polygonShape2 = (b2PolygonShape*)fixture->GetShape();
	float vertexCount = polygonShape2->GetVertexCount();
	for (int i = 0; i < vertexCount; ++i)
	{
		//get the vertex in body coordinates
		b2Vec2 bcVertex = polygonShape2->GetVertex(i);
		//get the vertex in world coordinates
		b2Vec2 wcVertex = fixture->GetBody()->GetWorldPoint(bcVertex);
		xCenter += wcVertex.x;
		yCenter += wcVertex.y;
		std::cout << wcVertex.x << " " << wcVertex.y << std::endl;
	}
	return yCenter / 4;
}