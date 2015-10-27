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

void Animation::draw( SDL_Renderer* renderTarget, SDL_Rect drawingRect )
{
	SDL_RenderCopy( renderTarget, texture, &cropRect, &drawingRect );
}

void Animation::drawEx(SDL_Renderer* renderTarget, SDL_Rect drawingRect, int angle){
	std::cout << angle << std::endl;
	int newAngle = 0;
	if (angle< 90)
	{
		int temp = 90 - angle;
		newAngle = 90 + temp;
	}
	if (angle < 180 )
	{
		int temp =   angle - 90;
		newAngle = 90 - temp;
	}
	if (angle < 270)
	{
		int temp = 270 - angle;
		newAngle = 270 + temp;
	}
	else{
		int temp = angle - 270;
		newAngle = 270 - temp;
	}
	SDL_RenderCopyEx(renderTarget, texture, NULL, &drawingRect, newAngle, NULL, SDL_FLIP_VERTICAL);
}

void Animation::standStill()
{
	frameCounter = 0.0f;
	cropRect.x = frameWidth * startFrameX;
	cropRect.y = frameHeight * startFrameY;
}

int Animation::getOriginX()
{
	return frameWidth / 2;
}

int Animation::getOriginY()
{
	return frameHeight / 2;
}

int Animation::getFrameWidth()
{
	return frameWidth;
}

int Animation::getFrameHeight()
{
	return frameHeight;
}
