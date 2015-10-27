
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include "Sprite.h"

Sprite::Sprite( int xPosition, int yPosition )
{
	currentAnimaton = 0;
	angle = 0;
	positionRect.x = xPosition;
	positionRect.y = yPosition;
}

Sprite::Sprite(SDL_Renderer* renderTarget, std::string filePath){
	Animation* default_animation = new Animation(renderTarget, filePath, 1, 1, 0, 0, 0.50f);

	animations = new std::vector<Animation*>();
	animations->push_back(default_animation);

	currentAnimaton = 0;

	positionRect.w = animations->at(currentAnimaton)->getFrameWidth();
	positionRect.h = animations->at(currentAnimaton)->getFrameHeight();
}

Sprite::Sprite( SDL_Renderer *renderTarget, std::string filePath, int xPosition, int yPosition, int framesX, int framesY, float animationSpeed)
{
	Animation* default_animation = new Animation( renderTarget, filePath, framesX, framesY, 0, 0, animationSpeed );

	animations = new std::vector<Animation*>();
	animations->push_back( default_animation );

	currentAnimaton = 0;

	positionRect.x = xPosition;
	positionRect.y = yPosition;
	positionRect.w = animations->at( currentAnimaton )->getFrameWidth();
	positionRect.h = animations->at( currentAnimaton )->getFrameHeight();
}

Sprite::~Sprite()
{
	for( size_t x = 0; x < animations->size(); x++ )
		delete animations->at( x );
	delete animations;
}

void Sprite::update( float delta, const Uint8 *keyState )
{
	animations->at( currentAnimaton )->update( delta );
}

void Sprite::draw( SDL_Renderer *renderTarget, SDL_Rect camerRect )
{
	SDL_Rect drawingRect = { positionRect.x - camerRect.x, positionRect.y - camerRect.y, positionRect.w, positionRect.h };
	animations->at( currentAnimaton )->draw( renderTarget, drawingRect );
}

void Sprite::drawEx(SDL_Renderer *renderTarget, SDL_Rect camerRect)
{
	SDL_Rect drawingRect = { positionRect.x - camerRect.x, positionRect.y - camerRect.y, positionRect.w, positionRect.h };
	animations->at(currentAnimaton)->drawEx(renderTarget, drawingRect, angle);
}

int Sprite::getPositionX()
{
	return positionRect.x + this->animations->at(currentAnimaton)->getOriginX();
}
int Sprite::getPositionY()
{
	return positionRect.y + this->animations->at(currentAnimaton)->getOriginY();
}

void Sprite::setOriginX( int newOriginX )
{
	originX = newOriginX;
}
void Sprite::setOriginY( int newOriginY )
{
	originY = newOriginY;
}

void Sprite::subscribe()
{
	//TODO: sprite subscribes itself.
	throw new std::logic_error( "not yet implemented" );
}
