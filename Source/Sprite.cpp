
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include "Sprite.h"

Sprite::Sprite( int xPosition, int yPosition )
{
	currentAnimation = 0;
	angle = 0;
	positionRect.x = xPosition;
	positionRect.y = yPosition;
}

Sprite::Sprite(SDL_Renderer* renderTarget, Asset asset){
	this->asset = asset;
	Animation* default_animation = new Animation(renderTarget, this->asset, 1, 1, 0, 0, 0.50f);

	animations = new std::vector<Animation*>();
	animations->push_back(default_animation);

	currentAnimation = 0;

	positionRect.w = animations->at(currentAnimation)->getFrameWidth();
	positionRect.h = animations->at(currentAnimation)->getFrameHeight();
}

Sprite::Sprite( SDL_Renderer *renderTarget, Asset asset, int xPosition, int yPosition, int framesX, int framesY, float animationSpeed)
{
	this->asset = asset;
	Animation* default_animation = new Animation( renderTarget, this->asset, framesX, framesY, 0, 0, animationSpeed );

	animations = new std::vector<Animation*>();
	animations->push_back( default_animation );

	currentAnimation = 0;


	positionRect.x = xPosition;
	positionRect.y = yPosition;
	positionRect.w = animations->at( currentAnimation )->getFrameWidth();
	positionRect.h = animations->at( currentAnimation )->getFrameHeight();
}

Sprite::~Sprite()
{
	for (size_t x = 0; x < animations->size(); x++){
		delete animations->at(x); animations->at(x) = nullptr;
	}
	delete animations;	animations = nullptr;
}

void Sprite::updateAnimation( float delta )
{
	animations->at( currentAnimation )->update( delta );
}

void Sprite::draw( SDL_Renderer *renderTarget, SDL_Rect camerRect )
{
	SDL_Rect drawingRect = { positionRect.x - camerRect.x, positionRect.y - camerRect.y, positionRect.w, positionRect.h };
	animations->at( currentAnimation )->draw( renderTarget, drawingRect );
}

void Sprite::draw( SDL_Renderer *renderTarget)
{
	SDL_Rect drawingRect = { positionRect.x, positionRect.y, positionRect.w, positionRect.h };
	animations->at( currentAnimation )->draw( renderTarget, drawingRect );
}

void Sprite::drawTree(SDL_Renderer *renderTarget, SDL_Rect camerRect)
{
	SDL_Rect drawingRect = { positionRect.x - camerRect.x, positionRect.y - camerRect.y, positionRect.w, positionRect.h };
	animations->at(currentAnimation)->drawCar(renderTarget, drawingRect, angle);
}

void Sprite::drawCar(SDL_Renderer *renderTarget, SDL_Rect cameraRect){
	SDL_Rect drawingRect = { positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h };
	animations->at(currentAnimation)->drawCar(renderTarget, drawingRect, angle);
}

void Sprite::drawTire(SDL_Renderer *renderTarget, SDL_Rect cameraRect){
	SDL_Rect drawingRect = { positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h };
	animations->at(currentAnimation)->drawCar(renderTarget, drawingRect, angle);
}

void Sprite::drawProjectile( SDL_Renderer* renderTarget, SDL_Rect cameraRect )
{
	SDL_Rect drawingRect = { positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h };
	animations->at( currentAnimation )->drawCar( renderTarget, drawingRect, angle );
}

int Sprite::getPositionX()
{
	return positionRect.x + this->animations->at(currentAnimation)->getOriginX();
}
int Sprite::getPositionY()
{
	return positionRect.y + this->animations->at(currentAnimation)->getOriginY();
}

void Sprite::updateOrigin(){
	int newOriginX = positionRect.x + (positionRect.w / 2);
	int newOriginY = positionRect.y + (positionRect.h / 2);
	animations->at(currentAnimation)->setOriginX(newOriginX);
	animations->at(currentAnimation)->setOriginY(newOriginY);
}

int Sprite::getOriginX(){
	return animations->at(currentAnimation)->getOriginX();
}

int Sprite::getOriginY(){
	return animations->at(currentAnimation)->getOriginY();
}

void Sprite::setAsset( Asset asset )
{
	this->animations->at(currentAnimation)->setAsset( asset );
}

void Sprite::updateSDLPosition(float x, float y, float w, float h, float a){
	positionRect.x = x;
	positionRect.y = y;
	positionRect.w = w;
	positionRect.h = h;
	angle = a;
}

bool Sprite::animationDone()
{
	return animations->at( currentAnimation )->done;
}