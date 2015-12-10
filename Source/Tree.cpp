#include "Tree.h"
#include "World.h"
#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

Tree::Tree(World* world, b2World* physicsWorld, SDL_Renderer* renderTarget, int widthM, int heightM, int posX, int posY)
	:B2Content(renderTarget, world, physicsWorld, Asset_Tree), Hittable(1000){
	objectType = Object_Tree;
	w = widthM;
	h = heightM;
	//create car body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	bodyDef.position.Set(posX, posY);
	m_body = physicsWorld->CreateBody( &bodyDef );

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

	contactable = new Contactable(this);
	m_body->SetUserData(contactable);
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

void Tree::accept( UpdateVisitor *uv )
{
	uv->visit( this );
}

void Tree::checkDeath()
{
	if( dead )
	{
		world->createExplosion( positionRect );
		world->getCar()->addScore( 100 );
		world->destroyObject( this );
	}
		
}