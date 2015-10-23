
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include "Sprite.h"

Sprite::Sprite(int xPosition, int yPosition, DrawContainer *dc)
{
	currentAnimaton = 0;
	positionRect.x = xPosition;
	positionRect.y = yPosition;
	dc->Add(this);//Adds itself to the container (container reference needed though
}

Sprite::Sprite(SDL_Renderer *renderTarget, std::string filePath, int xPosition, int yPosition, int framesX, int framesY, float animationSpeed, DrawContainer *dc){
	Animation* default_animation = new Animation(renderTarget, filePath, framesX, framesY, 0, 0, animationSpeed);

	this->animations = new std::vector<Animation*>();
	this->animations->push_back(default_animation);

	this->currentAnimaton = 0;

	this->positionRect.x = xPosition;
	this->positionRect.y = yPosition;
	this->positionRect.w = this->animations->at(this->currentAnimaton)->getFrameWidth();
	this->positionRect.h = this->animations->at(this->currentAnimaton)->getFrameHeight();

	dc->Add(this); //Adds itself to the container (container reference needed though
}

Sprite::~Sprite()
{
	for (int x = 0; x < this->animations->size(); x++)
		delete this->animations->at(x);
}

void Sprite::Update(float delta, const Uint8 *keyState){
	this->animations->at(currentAnimaton)->Update(delta);
}

void Sprite::Draw(SDL_Renderer *renderTarget, SDL_Rect camerRect){
	SDL_Rect drawingRect = { positionRect.x - camerRect.x, positionRect.y - camerRect.y, positionRect.w, positionRect.h };
	this->animations->at(this->currentAnimaton)->Draw(renderTarget, drawingRect);
}

int Sprite::getPositionX(){
	return this->positionRect.x + this->originX;
}
int Sprite::getPositionY(){
	return this->positionRect.y + this->originY;
}

void Sprite::setOriginX(int newOriginX){
	this->originX = newOriginX;
}
void Sprite::setOriginY(int newOriginY){
	this->originY = newOriginY;
}

void Sprite::Accept(DrawVisitor &dv)
{
	dv.Visit(this);
}

void Sprite::Subscribe()
{
	//TODO: sprite subscribes itself.
	throw new std::logic_error("not yet implemented");
}
