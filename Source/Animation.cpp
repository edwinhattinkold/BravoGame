#include "Animation.h"
#include <iostream>

Animation::Animation( SDL_Renderer* renderTarget, std::string filePath, int framesX, int framesY, int startFrameX, int startFrameY, float animationSpeed )
{
	SDL_Surface *surface = IMG_Load( filePath.c_str() );
	if( surface == NULL )
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface( renderTarget, surface );
		if( texture == NULL )
			std::cout << "Error" << std::endl;
	}
	SDL_FreeSurface( surface );

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
	this->animationSpeed = animationSpeed;
	this->startFrameX = startFrameX;
	this->startFrameY = startFrameY;
}


Animation::~Animation()
{
	SDL_DestroyTexture( texture );
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
				cropRect.y = 0;
		}
	}
}

int Animation::transfrom(float dgrs)
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
