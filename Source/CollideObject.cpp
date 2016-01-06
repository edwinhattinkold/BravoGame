#include "CollideObject.h"
#include "World.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

CollideObject::CollideObject(World* world, b2World* physicsWorld, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY, CollideType type)
	:B2Content(renderTarget, world, physicsWorld, Asset_Tree), Hittable(1000,	Asset_Tree){
	objectType = Object_Collide;
	w = widthM;
	h = heightM;

	myType = type;
	switch (type)
	{
	case Desert_Tree:
		setAsset(Asset_Tree);
		break;
	case Desert_Piramid:
		setAsset(Asset_Pyramid);
		break;
	case Ice_Tent:
		setAsset(Asset_Tent);
		break;
	case Ice_Tree:
		setAsset(Asset_IceTree);
		break;
	default:
		setAsset(Asset_CollideDefault);
		break;

	}


	//create car body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	bodyDef.position.Set(posX, posY);
	m_body = physicsWorld->CreateBody(&bodyDef);

	m_body->SetAngularDamping(3);

	b2Vec2 vertices[8];
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

	m_body->SetUserData(this);
}


CollideObject::~CollideObject()
{

}

b2Body * CollideObject::getBody()
{
	return m_body;
}

void CollideObject::accept(DrawVisitor *dv)
{
	dv->visit(this);
}

void CollideObject::accept(UpdateVisitor *uv)
{
	uv->visit(this);

}

void CollideObject::checkDeath()
{
	if (dead)
	{
		world->createExplosion(positionRect);
		world->getCar()->addScore(100);
		world->destroyObject(this);
	}

}