#include "Animation.h"
#include <iostream>

Animation::Animation( SDL_Renderer* renderTarget, Asset asset, int framesX, int framesY, int startFrameX, int startFrameY, float animationSpeed )
{
	texture = Assets::getInstance()->getAsset( asset );
	this->animationSpeed = animationSpeed;
	this->startFrameX = startFrameX;
	this->startFrameY = startFrameY;
	init(framesX, framesY);
	done = false;
}


Animation::~Animation()
{

}

void Animation::init(int framesX, int framesY)
{
	SDL_QueryTexture( texture, NULL, NULL, &cropRect.w, &cropRect.h );

	textureWidth = cropRect.w;
	textureHeight = cropRect.h;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = cropRect.w;
	frameHeight = cropRect.h;

	/* set the first frame */
	cropRect.x = frameWidth * startFrameX;
	cropRect.y = frameHeight * startFrameY;

	frameCounter = 0.0f;
}

void Animation::update( float deltaTime )
{
	frameCounter += deltaTime;

	if( frameCounter >= animationSpeed )
	{
		frameCounter = 0;
		cropRect.x += frameWidth;
		if( cropRect.x >= textureWidth )
		{
			cropRect.y += frameHeight;
			cropRect.x = 0;
			if( cropRect.y >= textureHeight )
			{
				done = true;
			}
				
		}
	}
}

void Animation::draw( SDL_Renderer* renderTarget, SDL_Rect drawingRect )
{
	SDL_RenderCopy( renderTarget, texture, &cropRect, &drawingRect );
}

void Animation::drawTree(SDL_Renderer* renderTarget, SDL_Rect drawingRect, int angle){
	SDL_RenderCopyEx(renderTarget, texture, NULL, &drawingRect, angle, NULL, SDL_FLIP_NONE);
}

void Animation::drawCar(SDL_Renderer* renderTarget, SDL_Rect drawingRect, int angle){
	SDL_RenderCopyEx(renderTarget, texture, NULL, &drawingRect, angle, NULL, SDL_FLIP_VERTICAL);
}

void Animation::DrawWithAngle(SDL_Renderer* renderTarget, SDL_Rect drawingRect, int angle){
	SDL_RenderCopyEx(renderTarget, texture, NULL, &drawingRect, angle, NULL, SDL_FLIP_VERTICAL);
}

void Animation::standStill()
{
	frameCounter = 0.0f;
	cropRect.x = frameWidth * startFrameX;
	cropRect.y = frameHeight * startFrameY;
}

int Animation::getFrameWidth()
{
	return frameWidth;
}

int Animation::getFrameHeight()
{
	return frameHeight;
}

int Animation::getOriginX(){
	return originX;
}

int Animation::getOriginY(){
	return originY;
}

void Animation::setOriginX(int newOriginX){
	originX = newOriginX;
}

void Animation::setOriginY(int newOriginY){
	originY = newOriginY;
}

void Animation::setAsset( Asset asset )
{
	this->texture = Assets::getInstance()->getAsset( asset );
	init( 1, 1 );
}
