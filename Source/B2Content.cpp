#include "B2Content.h"


B2Content::B2Content( SDL_Renderer* renderTarget, Asset asset) :Sprite(renderTarget, asset)
{
	isOnDeathRow = false;
}


B2Content::~B2Content()
{
	if( m_body != nullptr )
		m_body->GetWorld()->DestroyBody(m_body);
}

b2Vec2 B2Content::getB2DPosition(){
	return m_body->GetPosition();
}

void B2Content::setB2DPosition(b2Vec2 position)
{
	m_body->SetTransform( position, m_body->GetAngle() );
}

b2Vec2 B2Content::getB2DDirectionalVector()
{
	b2Vec2 b2DDirectionalVector = m_body->GetLocalVector( m_body->GetLocalCenter() );
	b2DDirectionalVector.x = b2DDirectionalVector.x * -1;
	return b2DDirectionalVector;
}

b2Vec2 B2Content::getSDLPosition()
{
	float x = m_body->GetPosition().x;
	float y = m_body->GetPosition().y * -1;
	return b2Vec2(x, y);
}

void B2Content::setB2DAngle(float angle){
	angle = (360 - angle) * DEGTORAD;
	m_body->SetTransform(m_body->GetWorldCenter(), angle);
}

b2Vec2 B2Content::getSDLDirectionalVector()
{
	b2Vec2 direction = m_body->GetLocalVector(m_body->GetLocalCenter());	
	direction.x = direction.x * - 1 * sdlScale;
	direction.y = direction.y * - 1 * sdlScale;
	std::cout << direction.x << " , " << direction.y << std::endl;
	return direction;
}

float B2Content::getAngleSDL(){
	
	return transform(m_body->GetAngle() * RADTODEG);
}

float B2Content::getCenterXSDL()
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
	}
	float centerx = xCenter / 4;
	float widthx = getSDLWidth() / sdlScale;
	float sol1 = centerx - (widthx / 2);
	return sol1 *sdlScale;
}

float B2Content::getCenterYSDL()
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
	}
	float center = (yCenter / 4);
	float zheight = getSDLHeight() / sdlScale;
	float sol1 = center + (zheight / 2);
	float sol2 = sol1 * sdlScale;
	return -1 * sol2;
}

float B2Content::getSDLWidth()
{
	return w * sdlScale;
}

float B2Content::getSDLHeight()
{
	return h * sdlScale;
}

int B2Content::transform(float dgrs)
{

	int add360 = dgrs + 360;
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
	int newNewAngle = newAngle % 360;
	return newNewAngle;
}

ObjectTypes B2Content::getObjectType()
{
	return objectType;
}

void B2Content::accept(DrawVisitor* dv){}